
#include "Barometer.h"

#include "StandardCplusplus.h"
#include <Wire.h>

#include <vector>
//#include <template>

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))


// ******************
// * Template définition
// ******************
//    int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
//Serial.print("Nbr elements: ");
//Serial.print(ArrayLen(NumTab));
template< typename T, size_t N >
const size_t ArrayLen( T (&)[N] )
{
  return N;
}

template< typename T, size_t A, size_t N >
const size_t ArrayLen( T (&)[A][N], const char item = 0x00 )
{
  return item ? A : N;
}

template< typename T, size_t B, size_t A, size_t N >
const size_t ArrayLen( T (&)[B][A][N], const char item = 0x00 )
{
  return item ? ( item == 1 ? A : B ) : N;
}




//  Author:Frankie.Chu
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include "TM1637.h"
#define CLOCLOCK 4//pins definitions for TM1637 and can be changed to other ports       
#define FOURDIGITDIO 5


float temperature;
float pressure;
float atm;
float altitude;
Barometer myBarometer;

TM1637 tm1637(CLOCLOCK, FOURDIGITDIO);
void setup()
{
  Serial.begin(9600);
  delay(1000);

  /*
    tm1637.init();
    tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

    myBarometer.init();
  */

}
void loop()
{

  //
  int myInt = 4565;
  int digitCount = countNumberOfDigitOfAnInt(myInt);
  delay(150);



  //int8_t * Coco  = convertIntIntoArrayOfDigit(myInt);
  Serial.println();

  // int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
   std::vector<int8_t> NumTab(4) ;

for(int i=0; i<4; ++i){
    NumTab[i] = i*3;
}
  
  //int8_t NumTab[digitCount] ;

  //NumTab  = convertIntIntoArrayOfChar(myInt);


  for (int BitSelect = 0; BitSelect < digitCount; BitSelect ++)
  {

    Serial.println();
    Serial.print("NumTab : ");
    Serial.print( NumTab[BitSelect]);
    Serial.print("NumTab2 : ");
    Serial.print( NumTab[BitSelect]);
  }

  // Serial.print( typeid(NumTab).name());

  // Serial.print(ARRAY_SIZE(NumTab));

  Serial.println();

  int8_t ListDisp[4];
  unsigned char i = 0;
  unsigned char count = 0;



  //    int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
  //Serial.print("Nbr elements: ");
  //Serial.print(ArrayLen(NumTab));
  Serial.print("Nbr Digit: ");

  //std::array<int8_t,5> a2 ={0,1,2,3,4}

  Serial.println();

  while (1)
  {



    i = count;
    count ++;
    if (count == sizeof(NumTab)) count = 0;
    for (unsigned char BitSelect = 0; BitSelect < 4; BitSelect ++)
    {
      ListDisp[BitSelect] = NumTab[i];
      i ++;
      if (i == sizeof(NumTab)) i = 0;
    }

    tm1637.display(0, ListDisp[0]);
    tm1637.display(1, ListDisp[1]);
    tm1637.display(2, ListDisp[2]);
    tm1637.display(3, ListDisp[3]);

    delay(300);

    /*
         displayBarometerToSerial();

    */

  }

}



int8_t * convertIntIntoArrayOfChar(int anInt) {

  int numberOfDigit = countNumberOfDigitOfAnInt(anInt);

    double aDouble = anInt;
  char charBuffer[numberOfDigit];

  char*  arrayOfChar = dtostrf(aDouble, numberOfDigit, 0, charBuffer);
  int8_t result[numberOfDigit];

  
  for (int i = 0; i < numberOfDigit; i++) {
    result[i] = (int8_t) (int) (char) arrayOfChar[i];
  }
  return result;

  

  

  Serial.println();
  Serial.print("arrayOfChar: " );
  Serial.print(arrayOfChar );
  int8_t *arrayOfUnsignedChar = (int8_t)atoi(arrayOfChar);

  Serial.println();
  Serial.print("arrayOfUnsignedChara: " );

  for (int i = 0; i < numberOfDigit; i++) {
    Serial.print(i);
    Serial.print(": " );

    Serial.print(arrayOfUnsignedChar[i]);
    Serial.println();

  }
  int8_t NumTab[] = {0, 1, 2, 3};
  return NumTab;
  return arrayOfUnsignedChar;

  Serial.print(numberOfDigit);
  Serial.println();
  Serial.print("charBuffer: " );

  Serial.print(charBuffer);

  Serial.println();
  Serial.print("output: " );
  Serial.print(arrayOfChar[0]);



  uint8_t charArrayConvertedInInt8_t [8];
  sscanf(charBuffer, "%c", &charArrayConvertedInInt8_t[0]);
  Serial.println();
  return charArrayConvertedInInt8_t;
}



int countNumberOfDigitOfAnInt(int anInt) {

  int count = 0;
  while (anInt > 0)
  {
    anInt = anInt / 10;
    count++;

  }
  return count;
}

void displayBarometerToSerial() {



  temperature = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT()); //Get the temperature, bmp085ReadUT MUST be called first
  pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());//Get the temperature
  altitude = myBarometer.calcAltitude(pressure); //Uncompensated calculation - in Meters
  atm = pressure / 101325;
  /*
     Serial.print("Temperature: ");
     Serial.print(temperature, 2); //display 2 decimal places
     Serial.println("deg C");

     Serial.print("Pressure: ");
     Serial.print(pressure, 0); //whole number only.
     Serial.println(" Pa");

     Serial.print("Ralated Atmosphere: ");
     Serial.println(atm, 4); //display 4 decimal places

     Serial.print("Altitude: ");
     Serial.print(altitude, 2); //display 2 decimal places
     Serial.println(" m");

     Serial.println();
  */

  delay(1000); //wait a second and get values again.
}


/*
  void printACharArray(& int_8t * anArrayOfChars){
    int size_of_myArray=
    for(int i = 0; i < size_of_myArray; i++)
  {
  Serial.println(myArray[i]);
  }

    }
*/



