#include <Servo.h>

Servo servo;


void lock_setup() {
  servo.attach(0);  //D4
  delay(1000);
}

void lock_loop() {

}

void lock(){
 servo.write(150);
 delay(1000);
 
  
}

void unlock(){
 servo.write(50);
 delay(1000);
 door_is_unlock = true;
 
  
}
