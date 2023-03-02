# For programming for the flight
Ignore the "Testing" sections

# Set-up Arduino IDE
https://learn.adafruit.com/adafruit-feather-m0-adalogger/setup  
- Put `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json` in the Additional Boards Manager URLs option.
- On the side in Boards Manager, install Adafruit SAMD Boards
- On the side in Library Manager, install Adafruit MS8607

# Programming the Adalogger
- Plug the adalogger to the computer
- Enter/Open code to execute
- Select the adalogger as a port (COM 5 or 6)
- Click on upload button

# Testing the SD card on Adalogger
- Run `File > Examples > SD > CardInfo`
- Run `File > Examples > SD > WriteRead`

# Connecting the PHT sensor
- BLACK : GND
- RED : 3V
- BLUE : SDA
- YELLOW : SCL

**Double check the connections, or the following will not work.**

# Testing for I2C connectors
https://learn.adafruit.com/scanning-i2c-addresses/arduino  

# Testing the PHT sensor
- Run `File > Examples > Adafruit MS8607 > sensor_test`

# PHT sensor recording
- Upload `PHT_recording_prog.ino`
