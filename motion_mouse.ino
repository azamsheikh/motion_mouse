  

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include "Keyboard.h"
#include "Mouse.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

MPU6050 mpu;
int weapon = 0;
int weaponchangestatus = 0;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;
int incomingByte = 0;
int data1 = 0;
void setup() {
   Mouse.begin();
Keyboard.begin();
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  

  
 
 //Serial.begin(57600);

  //mySerial.begin(9600);
  
 Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
    }
    

}

void loop() {
  
 digitalWrite(11, HIGH);
digitalWrite(10, HIGH);
 

   int xmovement = analogRead(A1);
   int ymovement = analogRead(A0);

  int shoot = digitalRead(6);  
  int aim = digitalRead(7); 
  int button3 = digitalRead(8); 
  int left;
  int right; 



 

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  vx = (gy+300)/200;  // "+300" because the x axis of gyroscope give values about -350 while it's not moving. Change this value if you get something different using the TEST code, chacking if there are values far from zero.
  vy = -(gz-100)/200; // same here about "-100"
  int aay=(ay+300)/200;

  
 if(aay > 45 ){
    
    if (weaponchangestatus == 0)
    {
      if(weapon == 6){weapon = 0;}
    
      weapon = weapon + 1;
   if(weapon == 1){Keyboard.write('1');}
   else if(weapon == 2){Keyboard.write('2');}
   else if(weapon == 3){Keyboard.write('3');}
   else if(weapon == 4){Keyboard.write('4');}
   else if(weapon == 5){Keyboard.write('5');}
   else{weapon = 0;}
     weaponchangestatus = 1;
    }
   else{ weaponchangestatus = 1;}

  }
 else if(aay < -45){
 // Keyboard.write('f');          /////////roll to press f
  }
 else{
     weaponchangestatus = 0;
 
  
 Mouse.move(vy, vx+1);        ////////mouse movement
 }
 if(shoot  == 1){
  Mouse.click(MOUSE_LEFT);        ////shoot button
  digitalWrite(5, HIGH);

 }
 else{ digitalWrite(5, LOW);}
 
if(aim == 1){
 
  Mouse.click(MOUSE_RIGHT); //aim button
}
else{}

if(button3 == 1){
 
  Keyboard.write('r'); //aim button
}
else{}





  


  if(xmovement < 330){
    Keyboard.press('d');                  //D left walk
  }
  else if(xmovement > 670){
    Keyboard.press('a');                //A right walk
  }
 else{
 Keyboard.releaseAll();
  }

 if(ymovement > 600){
    Keyboard.press('w');                    //W forward walk
  }
  else if(ymovement < 425){
   Keyboard.press('s');                    //S backward walk
  }
 else{
  Keyboard.releaseAll();
  }



//Serial.println(az);
 

    
  delay(10);
 

}
