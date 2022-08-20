#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D8
#define RST_PIN D0

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 
MFRC522 mfrc522(SS_PIN, RST_PIN);


char str[32];

//String FBaddress;
//String FBaddress2;



void RFID_setup(){

  SPI.begin();      // Initiate  SPI bus
   mfrc522.PCD_Init();   // Initiate MFRC522
   Serial.println("Approximate your card to the reader...");
  
}

void RFID_loop(){

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
   }

   // Select one of the cards
   if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
   }

  
   array_to_string(mfrc522.uid.uidByte, 4, str); //Insert (byte array, length, char array for output)
   //Print the output uid string
   delay(1000);
   mfrc522.PICC_HaltA();  
}

void array_to_string(byte array[], unsigned int len, char buffer[])
{
   for (unsigned int i = 0; i < len; i++)
   {
      byte nib1 = (array[i] >> 4) & 0x0F;
      byte nib2 = (array[i] >> 0) & 0x0F;
      buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
      buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
   }
   buffer[len*2] = '\0';

    Serial.println(str);
    storeUID();
}

void storeUID(){

String code= String(str);

FBaddress= "/" + code + "/Email"; //email
FBaddress2= "/" + code + "/Name"; //number


Serial.println(FBaddress);
getdata();
  
}
