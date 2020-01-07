#include "ModbusRtu.h"

uint16_t au16data[16];
uint8_t u8state;

Modbus master(0,0,5); // (0,serial,pintxen) puerto serie esp32

modbus_t telegram; //declaracion de clase

unsigned long u32wait;

void setup() {
  master.begin( 19200 ); // baud-rate 
  master.setTimeOut( 2000 ); //  roll over
  u32wait = millis() + 5000;
  u8state = 0; 
}

void loop() {
  switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // delay espera
    break;
  case 1: 
    telegram.u8id = 1; // slave address
    telegram.u8fct = 1; // function code 
    telegram.u16RegAdd = 1; // start address in slave
    telegram.u16CoilsNo = 10; // number of elements (coils or registers) to read
    telegram.au16reg = au16data; // pointer to a memory array in the Arduino

    master.query( telegram ); // send query (only once)
    u8state++;
    break;
  case 2:
    master.poll(); // check incoming messages
    if (master.getState() == COM_IDLE) {
      u8state = 0;
      u32wait = millis() + 5000; 
    }
    break;
  }
}
