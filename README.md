# TC4-Emulator
Very small Example how to send Temperature Data from an Arduino to Artisan Roast Software using the TC4 protocol. (https://github.com/artisan-roaster-scope/artisan)
For Temperaure reading the Arduino Libary Adafruit_MAX31855 is used.

# Artisan Setup
- Goto Config 
- Goto Device 
- Select TC4 Radio Button 
- Click "OK" 
- Select the right COM Port 
- Set Baud: 115200
- Click "OK"

# Additional Information TC4 Protocol
Artisan sends commands to request settings or data. 
The values must be in a fixed order and syntax.
See "handleSerialCommand" and "Command_READ" functions.

The "0.00" in the "Command_READ" functions are unused data channels, that can be replaced by actual values.
The first channel is used for environmental temperatur and can not be used freely in Artisan.

Any serial output other than the expected "#OK.." from the settings commands 
and the output of the "Command_READ" function will cause issues in Artisan.
