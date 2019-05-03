#include <Adafruit_MAX31855.h>
#include <SPI.h>

//TC4 Emulator.ino

bool unit_F = false; //true = °F - false = °C

const int thermoACs = 28;
const int thermoBCs = 29;

const int spiClk = 21;
const int spiDo = 23;

const long BAUD = 115200;

// Use this for Software SPI
//Adafruit_MAX31855 thermoA(spiClk, thermoACs, spiDo);
//Adafruit_MAX31855 thermoB(spiClk, thermoBCs, spiDo);

// Use this for Hardware SPI
Adafruit_MAX31855 thermoA(thermoACs);
Adafruit_MAX31855 thermoB(thermoBCs);

double tempA;
double tempB;


double readThermoCouple(Adafruit_MAX31855 &thermo)
{

    double tempT;
    
    if (unit_F){
        tempT = thermo.readFarenheit(); 
    }  
    else{
        tempT = thermo.readCelsius();
    }

      
    if (isnan(tempT)){ 
        return 0;
    }
    else{
        return tempT;
    }
}

void handleSerialCommand(){   //Parsing Serial Commands

    if (Serial.available()>0){
        String msg = Serial.readStringUntil('\n');

        if (msg.indexOf("CHAN;")== 0){  //Ignore this Setting
            Serial.print("#OK");
        }
        else if (msg.indexOf("UNITS;")== 0){

            if (msg.substring(6,7)=="F"){   //Change to Farenheit
                unit_F = true;
                Serial.println("#OK Farenheit");
            }
            else if (msg.substring(6,7)=="C"){  //Change to Celsius
                unit_F = false;
                Serial.println("#OK Celsius");
            }

        }
        else if (msg.indexOf("READ")==0){   //Send Temps
           Command_READ();

       }
   }

}

void Command_READ(){    
    Serial.print("0.00,");
    Serial.print(tempA);
    Serial.print(",");
    Serial.print(tempB);
    Serial.println(",0.00,0.00");
}




void setup() {
  SPI.begin();
  Serial.begin(BAUD);
}


void loop() {
    
    tempA=readThermoCouple(thermoA);
    tempB=readThermoCouple(thermoB);
    
    handleSerialCommand();
    
}

