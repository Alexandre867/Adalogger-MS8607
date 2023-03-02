### For programming for the flight
Ignore the "Testing" sections

### Set-up Arduino IDE
https://learn.adafruit.com/adafruit-feather-m0-adalogger/setup  
- Put `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json` in the Additional Boards Manager URLs option.
- On the side in Boards Manager, install Adafruit SAMD Boards
- On the side in Library Manager, install Adafruit MS8607

### Programming the Adalogger
- Plug the adalogger to the computer
- Enter/Open code to execute
- Select the adalogger as a port (COM 5 or 6)
- Click on upload button

### Testing the SD card on Adalogger
- Run `File > Examples > SD > CardInfo`
- Run `File > Examples > SD > WriteRead`

### Connecting the PHT sensor
- BLACK : GND
- RED : 3V
- BLUE : SDA
- YELLOW : SCL

**Double check the connections, or the following will not work.**

### Testing for I2C connectors
https://learn.adafruit.com/scanning-i2c-addresses/arduino  

### Testing the PHT sensor
- Run `File > Examples > Adafruit MS8607 > sensor_test`

### PHT sensor recording
- Upload `PHT_recording_prog.ino`

`PHT_recording_prog`:
```
#include <SPI.h>
#include <SD.h>

#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>


const String filename = "PHT_rec.csv";    // Filename (less than 8.3 char long)

const int dtime = 3000;   // Delay in ms



File dataFile;
Adafruit_MS8607 ms8607;

const int chipSelect = 4;

// Method to log into "log" file on SD card
bool log(String loginfo) {
  File logfile = SD.open("log", FILE_WRITE);
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

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    // log("Card failed, or not present");
    // don't do anything more:
    while (1);
  }

  log("Adafruit MS8607 test.");
  // Try to initialize!
  if (!ms8607.begin()) {
    log("Looking for MS8607 chip.");
    while (!ms8607.getHumidityResolution()) { delay(10); }
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
    dataFile.println("time s, pressure hPa, humidity rH, temperature C");
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
  
  // read three sensors
  sensors_event_t temp, pressure, humidity;
  ms8607.getEvent(&pressure, &temp, &humidity);

  // make a string for assembling the data to record
  String dataString = String(millis()/1000) + ", " + String(pressure.pressure) + ", " + String(humidity.relative_humidity) + ", " + String(temp.temperature);
  // String dataString =  String(millis()/1000) + ", " + String(1013.5) + ", " + String(50.4) + ", " + String(26.2);

  dataFile = SD.open(filename, FILE_WRITE);

  // if the file is available, write to it
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();

    digitalWrite(13, LOW); // turn the LED off by making the voltage LOW
  }
  // if the file isn't open, record an error
  else {
    log("error opening " + filename);
  }

  delay(dtime);   // Wait for given time
}
```
