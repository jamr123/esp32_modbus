
#include <ModbusRtu.h>
#include <SoftwareSerial.h>
/*#include <WiFi.h>
 
const char* ssid = "INFINITUM0AAE";
const char* password = "JamrEjro135";
int ModbusTCP_port = 502;
 
//////// Required for Modbus TCP / IP /// Requerido para Modbus TCP/IP /////////
#define maxInputRegister 20
#define maxHoldingRegister 20
 
#define MB_FC_NONE 0
#define MB_FC_READ_REGISTERS 3 //implemented
#define MB_FC_WRITE_REGISTER 6 //implemented
#define MB_FC_WRITE_MULTIPLE_REGISTERS 16 //implemented
//
// MODBUS Error Codes
//
#define MB_EC_NONE 0
#define MB_EC_ILLEGAL_FUNCTION 1
#define MB_EC_ILLEGAL_DATA_ADDRESS 2
#define MB_EC_ILLEGAL_DATA_VALUE 3
#define MB_EC_SLAVE_DEVICE_FAILURE 4
//
// MODBUS MBAP offsets
//
#define MB_TCP_TID 0
#define MB_TCP_PID 2
#define MB_TCP_LEN 4
#define MB_TCP_UID 6
#define MB_TCP_FUNC 7
#define MB_TCP_REGISTER_START 8
#define MB_TCP_REGISTER_NUMBER 10
 
byte ByteArray[260];
unsigned int MBHoldingRegister[maxHoldingRegister];
 
//////////////////////////////////////////////////////////////////////////
 
WiFiServer MBServer(ModbusTCP_port);
*/

Modbus master(0); // this is master and RS-232 or USB-FTDI via software serial
modbus_t telegram[2];
uint16_t au16data[20]; //vARIABLE ALMAACEN
uint8_t u8state; //ESTADO
uint8_t u8query; //PUNTERO QUERY
unsigned long u32wait;

SoftwareSerial mySerial(17, 16);// PINES SERIAL

void setup() {
  Serial.begin(9600);
  master.begin( &mySerial, 9600,5 ); 


 //////////////////////////////////////////CONFIGURACION QUERY////////////////

  telegram[0].u8id = 1; // DIRECCION ESCLAVO
  telegram[0].u8fct = 3; //FUNCION
  telegram[0].u16RegAdd = 0; // INICIO DE REGISTRO
  telegram[0].u16CoilsNo = 9; // NUMERO DE ELEMENTOS A LEER
  telegram[0].au16reg = au16data; // VRAIBLE DONDE ALMACENA LAS LECTURAS Y ESCRITURAS

  
  telegram[1].u8id = 1; //  DIRECCION ESCLAVO
  telegram[1].u8fct = 6; //FUNCION
  telegram[1].u16RegAdd = 10; // INICIO DE rEGISTRO
  telegram[1].u16CoilsNo = 19; // NUMERO DE ELEMENTOS A ESCRIBIR
  telegram[1].au16reg = au16data; //  VRAIBLE DONDE ALMACENA LAS LECTURAS Y ESCRITURAS

////////////////////////////////////////////////////////////////////////////////////////////////



  
  
  master.setTimeOut( 5000 ); 
  u32wait = millis() + 1000;
  u8state = u8query = 0; 

/*
 delay(100) ;
 WiFi.begin(ssid, password);
 delay(100) ;
 Serial.println(".");
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 MBServer.begin();
 Serial.println("Connected ");
 Serial.print("ESP8266 Slave Modbus TCP/IP ");
 Serial.print(WiFi.localIP());
 Serial.print(":");
 Serial.println(String(ModbusTCP_port));
 Serial.println("Modbus TCP/IP Online");
*/
  
}

void loop() {
   
 rtuMaster();  
   
}


void rtuMaster(){
  
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
      u32wait = millis() + 200; 
    }
    break;
  }

au16data[10]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[11]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[12]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[13]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[14]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[15]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[16]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[17]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[18]=1234; //apartir del registro 10 en adelate haste el 19 son escritura
au16data[19]=1234; //apartir del registro 10 en adelate haste el 19 son escritura


Serial.println(au16data[0]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[1]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[2]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[3]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[4]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[5]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[6]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[7]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[8]);//apartir del registro 0 en adelate haste el 9 son lectura
Serial.println(au16data[9]);//apartir del registro 0 en adelate haste el 9 son lectura

 
  }

/*


void tcpServer(){
   
 
 // Check if a client has connected // Modbus TCP/IP
 WiFiClient client = MBServer.available();
 if (!client) {
 return;
 }
 
 
 boolean flagClientConnected = 0;
 byte byteFN = MB_FC_NONE;
 int Start;
 int WordDataLength;
 int ByteDataLength;
 int MessageLength;
 
 // Modbus TCP/IP
 while (client.connected()) {

   
 
 if(client.available())
 {
 flagClientConnected = 1;
 int i = 0;
 while(client.available())
 {
 ByteArray[i] = client.read();
 i++;
 }
 
 client.flush();
 
 ///////// Holding Register [0] A [9] = 10 Holding Registers Escritura
 ///////// Holding Register [0] A [9] = 10 Holding Registers Writing
 
 MBHoldingRegister[0] = au16data[0];
 MBHoldingRegister[1] = au16data[1];
 MBHoldingRegister[2] = au16data[2];
 MBHoldingRegister[3] = au16data[3];
 MBHoldingRegister[4] = au16data[4];
 MBHoldingRegister[5] = au16data[5];
 MBHoldingRegister[6] = au16data[6];
 MBHoldingRegister[7] = au16data[7];
 MBHoldingRegister[8] = au16data[8];
 MBHoldingRegister[9] = au16data[9];
 
 
 
 
 ///////// Holding Register [10] A [19] = 10 Holding Registers Lectura
 ///// Holding Register [10] A [19] = 10 Holding Registers Reading

 
au16data[10]=MBHoldingRegister[10];
au16data[11]=MBHoldingRegister[11];
au16data[12]=MBHoldingRegister[12];
au16data[13]=MBHoldingRegister[13];
au16data[14]=MBHoldingRegister[14];
au16data[15]=MBHoldingRegister[15];
au16data[16]=MBHoldingRegister[16];
au16data[17]=MBHoldingRegister[17];
au16data[18]=MBHoldingRegister[18];
au16data[19]=MBHoldingRegister[19];

 
 
 
 //// rutine Modbus TCP
 byteFN = ByteArray[MB_TCP_FUNC];
 Start = word(ByteArray[MB_TCP_REGISTER_START],ByteArray[MB_TCP_REGISTER_START+1]);
 WordDataLength = word(ByteArray[MB_TCP_REGISTER_NUMBER],ByteArray[MB_TCP_REGISTER_NUMBER+1]);
 }
 
 // Handle request
 
 switch(byteFN) {
 case MB_FC_NONE:
 break;
 
 case MB_FC_READ_REGISTERS: // 03 Read Holding Registers
 ByteDataLength = WordDataLength * 2;
 ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
 ByteArray[8] = ByteDataLength; //Number of bytes after this one (or number of bytes of data).
 for(int i = 0; i < WordDataLength; i++)
 {
 ByteArray[ 9 + i * 2] = highByte(MBHoldingRegister[Start + i]);
 ByteArray[10 + i * 2] = lowByte(MBHoldingRegister[Start + i]);
 }
 MessageLength = ByteDataLength + 9;
 client.write((const uint8_t *)ByteArray,MessageLength);
 
 byteFN = MB_FC_NONE;
 
 break;
 
 
 case MB_FC_WRITE_REGISTER: // 06 Write Holding Register
 MBHoldingRegister[Start] = word(ByteArray[MB_TCP_REGISTER_NUMBER],ByteArray[MB_TCP_REGISTER_NUMBER+1]);
 ByteArray[5] = 6; //Number of bytes after this one.
 MessageLength = 12;
 client.write((const uint8_t *)ByteArray,MessageLength);
 byteFN = MB_FC_NONE;
 break;
 
 case MB_FC_WRITE_MULTIPLE_REGISTERS: //16 Write Holding Registers
 ByteDataLength = WordDataLength * 2;
 ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
 for(int i = 0; i < WordDataLength; i++)
 {
 MBHoldingRegister[Start + i] = word(ByteArray[ 13 + i * 2],ByteArray[14 + i * 2]);
 }
 MessageLength = 12;
 client.write((const uint8_t *)ByteArray,MessageLength); 
 byteFN = MB_FC_NONE;
 
 break;
 }

 }

  
}

*/
