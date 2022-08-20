#include "CTBot.h"
CTBot myBot;


uint8_t led = D4;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)              

void telegram_setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

  // set the pin connected to the LED to act as output pin
 // pinMode(led, OUTPUT);
 // digitalWrite(led, HIGH); // turn off the led (inverted logic!)

}

void telegram_loop() {
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("LOCK")) {              // if the received message is "LIGHT ON"...
      digitalWrite(led, HIGH);// turn on the LED (inverted logic!)
      myBot.sendMessage(msg.sender.id, "DOOR IS NOW LOCKED");  // notify the sender
      lock();
    }
    else if (msg.text.equalsIgnoreCase("UNLOCK")) {        // if the received message is "LIGHT OFF"...
      digitalWrite(led, LOW);                              // turn off the led (inverted logic!)
      myBot.sendMessage(msg.sender.id, "DOOR IS NOW UNLOCKED"); // notify the sender
      unlock();
    }
    else {                                                    // otherwise...
      // generate the message for the sender
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Message LOCK to turn on & UNLOCK to turn off the Led .";
      myBot.sendMessage(msg.sender.id, reply);             // and send it
    }
  }
  // wait 500 milliseconds
  delay(500);
}
