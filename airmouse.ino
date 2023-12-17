#include <MPU6050_tockn.h>                                    // Download and install this library https://github.com/tockn/MPU6050_tockn
#include <Wire.h>

#define LeftB     5                                           // Left Button Pin
#define RightB    4                                           // Right Button Pin
#define MouseB    6                                           // Mouse Enable Button Pin

MPU6050 mpu6050(Wire);
int X,Y,Z;                                                    // Data Variables for mouse co-ordinates
int OX,OY,OZ;                                                 // Angle Variables for calucating gyroscope zero error

void setup() {
   
  Serial.begin(115200);                                       // Initialise Serial communication
  Wire.begin();                                               // Initialise I2C communication
  mpu6050.begin();                                            // Initialise Gyro communication
  Serial.println("STRTM");                                    // Identifier "STARTM" for start mouse
  mpu6050.calcGyroOffsets(true);                              // Setting Gyro offsets
  mpu6050.update();                                           // Command to calculate the sensor data before using the get command
  OX = mpu6050.getAngleX();                                   // Getting angle X Y Z
  OY = mpu6050.getAngleY();
  OZ = mpu6050.getAngleZ();

  pinMode(LeftB,INPUT);                                       // Setting Pinmode for all three buttons as INPUT
  pinMode(RightB,INPUT);
  pinMode(MouseB,INPUT);

  if(OX < 0){                                                 // Inverting the sign of all the three offset values for zero error correction
    OX = OX *(-1);}
  else{
    OX = (OX-OX)-OX;}

  if(OY < 0){
    OY = (OY *(-1));}
  else{
    OY = ((OY-OY)-OY)+10;}

  if(OZ < 0){
    OZ = OZ *(-1);}
  else{
    OZ = (OZ-OZ)-OZ;}
}

void loop() {
  mpu6050.update();
  X = OX + mpu6050.getAngleX();                                     // Getting current angle for X Y Z and correcting the zero error
  Y = OY + mpu6050.getAngleY();
  Z = OZ + mpu6050.getAngleZ();

  if(digitalRead(MouseB) == HIGH){                                  // Checks if Mouse Enabled Button is pushed
    delay(5);                                                       // Mouse movement resolution delay
    Serial.println("DATAL,"+String(X)+','+String(Y)+','+String(Z)); // Sends corrected gyro data to the Serial Port with the identifier "DATAL"
  }
  if(digitalRead(LeftB) == HIGH){                                   // Checks if Left Mouse Button is pushed
    delay(100);                                                     // Debounce delay
    Serial.println("DATAB,L");                                      // Sends "L" stating the left button is pressed with the identifier "DATAB"
  }
  if(digitalRead(RightB) == HIGH){                                  // Checks if Right Enabled Button is pushed
    delay(100);                                                     // Debounce delay
    Serial.println("DATAB,R");                                      // Sends "L" stating the left button is pressed with the identifier "DATAB"
  }
}
