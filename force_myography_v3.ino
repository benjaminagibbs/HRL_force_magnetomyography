// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MLX90393
// This code is designed to work with the MLX90393_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products
// VDD 3v3
// Gnd Gnd
// SDA SDA – 21
// SCL SCL – 22 
//I2C device found at address 0x14 !
//I2C device found at address 0x15 !
//I2C device found at address 0x16 !
//I2C device found at address 0x17 !


// ARDUINO UNO NOTES:
// Here are the pins:
//A4 (SDA)
//A5 (CLK/SCL)
//GND
//3.3V

#include <Wire.h>
#include "MLX90393.h" //From https://github.com/tedyapo/arduino-MLX90393 by Theodore Yapo

#include <TimeLib.h> 
unsigned long tt;
float Data[20];

MLX90393 mlx;
MLX90393::txyz data; //Create a structure, called data, of four floats (t, x, y, and z)

const int numReadings = 10                           ;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int original=0;
int threshold=0;
int count=0;



void setup() {

  Serial.begin(115200);


 // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }



  Wire.begin();
  mlx.begin(0, 0); // [0, 0] [0, 1] [1, 0] [1, 1] Sensor 1 Sensor 2 Sensor3 Sensor 4
  mlx.setOverSampling(0); mlx.setDigitalFiltering(0);
  
  delay(100);
  Serial.println("Ready!!! Go....");

  mlx.begin(0, 1); // [0, 0] [0, 1] [1, 0] [1, 1]  Middle
  mlx.setOverSampling(0);  // 2 previously used
  mlx.setDigitalFiltering(0);  // 10 previously used
  mlx.readData(data); //Read the values from the sensor
  Data[10]=data.x;Data[11]=data.y;Data[12]=data.z;

  mlx.begin(1, 0); // [0, 0] [0, 1] [1, 0] [1, 1]  Bottom
  mlx.setOverSampling(0);  // 2 previously used
  mlx.setDigitalFiltering(0);  // 10 previously used
  mlx.readData(data); //Read the values from the sensor
  Data[13]=data.x;Data[14]=data.y;Data[15]=data.z;

  mlx.begin(1, 1); // [0, 0] [0, 1] [1, 0] [1, 1]  Tip (fingertip)
  mlx.setOverSampling(0);
  mlx.setDigitalFiltering(0);
//  mlx.setGainSel(1);
//  mlx.setResolution(0, 0, 0);
  mlx.readData(data); //Read the values from the sensor
  Data[16]=data.x;Data[17]=data.y;Data[18]=data.z;

  
}

void loop() {


  //delay(1);
//
  mlx.begin(0, 0); // [0, 0] [0, 1] [1, 0] [1, 1]
  mlx.setOverSampling(0);
  mlx.setDigitalFiltering(0);
  mlx.readData(data); //Read the values from the sensor
  Data[3]=data.x-Data[13];Data[4]=data.y-Data[14];Data[5]=data.z-Data[15];

  mlx.begin(0, 1); // [0, 0] [0, 1] [1, 0] [1, 1]
  mlx.setOverSampling(0);
  mlx.setDigitalFiltering(0);  
  mlx.readData(data); //Read the values from the sensor
  Data[0]=data.x-Data[10];Data[1]=data.y-Data[11];Data[2]=data.z;


   if (Data[2]<5){
  Data[2]=0;
 }
 
  mlx.begin(1, 0); // [0, 0] [0, 1] [1, 0] [1, 1]
  mlx.setOverSampling(0);
  mlx.setDigitalFiltering(0);  
  mlx.readData(data); //Read the values from the sensor
  Data[9]=data.x-Data[13];Data[19]=data.y-Data[14];Data[20]=data.z-Data[15];

  if (Data[20]<5){
  Data[20]=0;
 }


   mlx.begin(1, 1); // [0, 0] [0, 1] [1, 0] [1, 1]
  mlx.setOverSampling(0);
  mlx.setDigitalFiltering(0);
  mlx.readData(data); //Read the values from the sensor
  Data[6]=data.x-Data[16];Data[7]=data.y-Data[17];Data[8]=data.z-Data[18];

 if (Data[8]<5){
  Data[8]=0;
 }
 

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = Data[2];
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  
  }
  // calculate the average:
  average = total / numReadings;
  

original=Data[2];

//if ((count<1000)&&(threshold<average)){
//threshold=average;
//count=count+1;
//}
//
//if(original<threshold){
//  original=0;
//}

//  
//  Serial.print(" ");
//  Serial.print(data.x);
//  Serial.print(" ");
//  Serial.print(data.y);
//  Serial.print(" ");
//  Serial.print(data.z);
//  Serial.println("  ");

//  Serial.print(" ");
//  Serial.print(0);  // To freeze the lower limit
//  Serial.print(" ");
//  Serial.print(600);  // To freeze the upper limit

  tt = millis();
//  Serial.println(" ");
//  Serial.print(tt);
//  Serial.print(",");
//  Serial.print(150);
//  Serial.print(",");
//  Serial.print(average);
//  Serial.println(",");
//
  Serial.print("Time: ");
  tt = millis();
  Serial.print(" ");
  Serial.print(tt);
//  Serial.print(" ");
//  
//  Serial.print(Data[0]-Data[6],0);
//  Serial.print(" ");
//  Serial.print(Data[1]-Data[7],0);
//  Serial.print(" ");
//  Serial.println(Data[2]-Data[8],0);
////
//  Serial.print(Data[6],0);
//  Serial.print(" ");
//  Serial.print(Data[7],0);
//  Serial.print(" ");
//  Serial.println(Data[8],0);
//
//  Serial.print(data.x,0);
//  Serial.print(" ");
//  Serial.print(data.y,0);
//  Serial.print(" ");
//  Serial.println(data.z,0);

////////////////////////////////////////////////////////////////////////
  Serial.print(" ");
  Serial.print(Data[2],0);
  Serial.print(" ");
  Serial.print(Data[5],0);
  Serial.print(" ");
  Serial.print(Data[8],0);
  Serial.print(" ");
  Serial.println(Data[20],0);
  

  delay(1);


 
}
