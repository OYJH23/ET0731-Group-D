

#include "a_ultrasonic.h"
#include "h_credentials.h"

bool door_is_unlock;

void setup() {

  pinMode(10,OUTPUT);  // Green Led Pin Connected To D1 Pin   
  pinMode(2,OUTPUT);

  no_LED();
   
  bool door_is_unlock = false;
  Serial.begin(115200); // Starts the serial communication
 
  ultrasonic_setup();
  lock_setup();
  lock();
  telegram_setup();
  RFID_setup();
 firebase_setup();
  
}

void loop() {
  ultrasonic_loop();

  telegram_loop();
  door_status2();
  RFID_loop();  
}

 



void  door_status2(){

  while(door_is_unlock == true){
    ultrasonic_loop();
    Serial.print("DOOR IS OPENED ")   ; 
    if(distanceCm > 10){
      delay(2000); // wait for person to enter  
      lock();
      door_is_unlock = false;
      Serial.print("DOOR IS CLOSED ");
    }

   delay(1000);
  }
}




 

  
  
