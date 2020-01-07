#include "ModbusRtu.h"
#include "SoftwareSerial.h"

uint16_t au16data[32]; //!< data array for modbus network sharing  Array
uint8_t u8state; //!< machine state
uint8_t u8query; //!< pointer to message query

Modbus master(0,0,5); // this is master and RS-232 or USB-FTDI via software serial

modbus_t telegram[2];

unsigned long u32wait;

SoftwareSerial mySerial(5, 4);//Create a SoftwareSerial object so that we can use software serial. Search "software serial" on Arduino.cc to find out more details.

void setup() {
  Serial.begin(9600);//use the hardware serial if you want to connect to your computer via usb cable, etc.
  master.begin( 9600); // begin the ModBus object. The first parameter is the address of your SoftwareSerial address. Do not forget the "&". 9600 means baud-rate at 9600
 // telegram 0: read registers
  telegram[0].u8id = 1;                 // slave address
  telegram[0].u8fct = 3;                // function code (registers read multiple  3) 
  telegram[0].u16RegAdd = 0;            // start address in slave -  direccion de Inicio 0
  telegram[0].u16CoilsNo =4;          // number of elements (coils or registers) to read  0 - 16 
  telegram[0].au16reg = au16data;       // pointer to a memory array in the Arduino - Almacenamiento en Array de memoria de arduino

  // telegram 1: write a multiple  register = function 16
  telegram[1].u8id = 1;                 // slave address
  telegram[1].u8fct = 16;               // function code (write multiple registers 16 )
  telegram[1].u16RegAdd = 5;           // start address in slave  -  direccion de Inicio 10
  telegram[1].u16CoilsNo = 10;          // number of elements (coils or registers) to read
  telegram[1].au16reg = au16data;    // pointer to a memory array in the Arduino - Almacenamiento en Array de memoria de arduino 10 posiciones despues

   
  
  master.setTimeOut( 5000 ); // if there is no answer in 5000 ms, roll over
  u32wait = millis() + 1000;
  u8state = u8query = 0; 
}

void loop() {
  
 switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // wait state
    break;
  case 1: 
    master.query( telegram[u8query] ); // send query (only once)
    u8state++;
 u8query++;
 if (u8query > 2) u8query = 0;
    break;
  case 2:
    master.poll(); // check incoming messages
    if (master.getState() == COM_IDLE) {
      u8state = 0;
      u32wait = millis() + 1000; 
      
    }
    break;
  }

imprimirValores();
   
}

void imprimirValores(){
 Serial.print(au16data[0]);    // Read Holding Register [0]
   Serial.print(",");    
   Serial.print(au16data[1]);    // Read Holding Register [1]
   Serial.print(",");    
   Serial.print(au16data[2]);    // Read Holding Register [2]
   Serial.print(","); 
   Serial.print(au16data[3]);    // Read Holding Register [3]
   Serial.print(",");     
   Serial.print(au16data[4]);    // Read Holding Register [4]
  
   
   Serial.println();
   

   au16data[5] =32; // Write Holding Register [10]
   
   au16data[6] = 34; // Write Holding Register [11]
   
   au16data[7] = 65; // Write Holding Register [12]
   
   au16data[8] = 43; // Write Holding Register [13]

   au16data[9] = 43; // Write Holding Register [13]
   
   delay(5000); 
  
  }
