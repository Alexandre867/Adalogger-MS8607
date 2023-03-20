/*
Copyright (c) 2023 HyperBall team

Reads pressure, temperature and humidity, writes in CSV file on the SD card.
LED on Adalogger will be on during initialization and then during measurements.
Messages about the status of the program will be saved in "log" file.

filename: name of the file
dtime: time between measurements
*/

#include <SPI.h>
#include <SD.h>

#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>


const String filename = "PHT_rec.csv";    // File name (less than 8.3 char long)

const int dtime = 3000;   // Delay in ms



File dataFile;
Adafruit_MS8607 ms8607;
float old_pressure = 0, old_hum = 0, old_temp = 0;

const int chipSelect = 4;

// Method to log into "log" file on SD card
// Write time (in ms) followed by message
// Return 1 if successful
bool log(String loginfo) {
  File logfile = SD.open("log", FILE_WRITE);  // Open the "log" file
  // If "log" file successfully open, write to it
  if (logfile){
    logfile.println(String(millis()) + ": " + loginfo);
    logfile.close();
    return 1;
  }
  else {
    return 0;
  }
}

void setup() {  
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)

  /*
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  */

  // Try to initialize the SD card
  while (!SD.begin(chipSelect));

  // Make a new log entry
  log("");
  log("-- Start --");

  log("Adafruit MS8607 test.");
  // Try to initialize the sensor
  if (!ms8607.begin()) {
    log("Looking for MS8607 chip.");
    while (!ms8607.begin()) { delay(10); }
  }
  log("MS8607 found.");

  ms8607.setHumidityResolution(MS8607_HUMIDITY_RESOLUTION_OSR_8b);
  switch (ms8607.getHumidityResolution()){
    case MS8607_HUMIDITY_RESOLUTION_OSR_12b: log("Humidity resolution set to: 12-bit"); break;
    case MS8607_HUMIDITY_RESOLUTION_OSR_11b: log("Humidity resolution set to: 11-bit"); break;
    case MS8607_HUMIDITY_RESOLUTION_OSR_10b: log("Humidity resolution set to: 10-bit"); break;
    case MS8607_HUMIDITY_RESOLUTION_OSR_8b: log("Humidity resolution set to: 8-bit"); break;
  }

  // ms8607.setPressureResolution(MS8607_PRESSURE_RESOLUTION_OSR_4096);
  switch (ms8607.getPressureResolution()){
    case MS8607_PRESSURE_RESOLUTION_OSR_256: log("Pressure and Temperature resolution set to: 256"); break;
    case MS8607_PRESSURE_RESOLUTION_OSR_512: log("Pressure and Temperature resolution set to: 512"); break;
    case MS8607_PRESSURE_RESOLUTION_OSR_1024: log("Pressure and Temperature resolution set to: 1024"); break;
    case MS8607_PRESSURE_RESOLUTION_OSR_2048: log("Pressure and Temperature resolution set to: 2048"); break;
    case MS8607_PRESSURE_RESOLUTION_OSR_4096: log("Pressure and Temperature resolution set to: 4096"); break;
    case MS8607_PRESSURE_RESOLUTION_OSR_8192: log("Pressure and Temperature resolution set to: 8192"); break;
  }

  // Opening the recording file
  log("Opening " + filename);
  dataFile = SD.open(filename, FILE_WRITE);
  // if the file is available, write header
  if (dataFile) {
    log(filename + " successfully opened.");
    dataFile.println();
    dataFile.println();
    dataFile.println("time s, pressure hPa, relative humidity \%, temperature C");
    dataFile.close();
  }
  // if the file isn't open, pop up an error and stop
  else {
    log("Error opening " + filename);
    while (1);
  }

  log("PHT recording started.");

  digitalWrite(13, LOW); // turn the LED off by making the voltage LOW
}

void loop() {
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  
  // read the sensors
  sensors_event_t temp, pressure, humidity;
  ms8607.getEvent(&pressure, &temp, &humidity);

  // make a string for assembling the data to record
  String dataString = String(millis()/1000) + ", " + String(pressure.pressure) + ", " + String(humidity.relative_humidity) + ", " + String(temp.temperature);
  // String dataString =  String(millis()/1000) + ", " + String(1013.5) + ", " + String(50.4) + ", " + String(26.2);

  dataFile = SD.open(filename, FILE_WRITE);   // Open the file for recording the data

  // if the file is available, write to it
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();

    // if there is no measurement, record an error
    if (pressure.pressure == old_pressure && humidity.relative_humidity == old_hum && temp.temperature == old_temp) {
    log("Warning: no PHT measurement");
    }
    else digitalWrite(13, LOW); // turn the LED off by making the voltage LOW
  }
  // if the file isn't open, record an error
  else {
    SD.begin(chipSelect);
    log("Error opening " + filename);
  }

  old_pressure = pressure.pressure;
  old_hum = humidity.relative_humidity;
  old_temp = temp.temperature;
  
  delay((millis()/dtime+1)*dtime-millis());   // Wait until the next multiple of dtime
}