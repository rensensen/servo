// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include "BluetoothSerial.h"
#include <ESP32Servo.h>
Servo servo;
String device_name = "ESP32EDU ";
int pinServo = 4;
char caracter[5];
int leer(int x,int y,int z);

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  servo.attach(pinServo,500,2500);
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  if (SerialBT.available()) {
      for(int i = 0; i<3; i++){
    caracter[i] = SerialBT.read();
  }
  Serial.println(caracter);
  }
  if (caracter[0]=='0'){
servo.write (0);
Serial.println("AL");
}
if ( (caracter[0]=='1')&&(caracter[1]== '2')&&(caracter[2]== '0')){
servo.write(120);
  
  Serial.println("GO");
}
  if (caracter[0]=='6'){
servo.write (60);
Serial.println("BRUJE");
}
if ( (caracter[0]=='3')&&(caracter[1]== '0')){
servo.write(30);
  
  Serial.println("JE");
}
}
void girar(char x[3]){
  int centena = 0;
  int decena = 0;
  int unidad = 0;
  int grados = 0;
  unidad = x[2];
  decena = x[1];
  centena = x[0];
  grados = unidad + (decena*10) + (centena*100);
  Serial.println(grados);
  servo.write(grados);
}
