//Gravity Acceleration
#include "LIS3DHTR.h"
#ifdef SOFTWAREWIRE
#include <SoftwareWire.h>
SoftwareWire myWire(3, 2);
LIS3DHTR<SoftwareWire> LIS;       //Software I2C
#define WIRE myWire
#else
#include <Wire.h>
LIS3DHTR<TwoWire> LIS;           //Hardware I2C
#define WIRE Wire
#endif

float y = 0;
float yThresh = 0;
int differential = 100;
int buttonPin = 3;
int calibrate = 0; //0 not calibrated yet, 1 its been calibrated


void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  LIS.begin(WIRE, 0x19); //IIC init
  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
}
void loop() {
  y = LIS.getAccelerationY();
  Serial.print("Y is: ");
  Serial.println(y);
  //calibration mode
  if (digitalRead(3) == 1 && calibrate == 0)
  {
    calibrate = 1;
    yThresh = LIS.getAccelerationY();
    Serial.print("Thresh is: ");
    Serial.println(yThresh);
    //flash led or some jawn to let us know we saved calibration
    delay(2000);
  }
  delay(100);

  if (calibrate == 1)
  {
    Serial.print("Difference between og and current y: ");
    Serial.println(y - yThresh);
  }

}
