#include <deprecated.h>
#include <MFRC522.h>
#include <require_cpp11.h>

/*

   All the resources for this project: http://randomnerdtutorials.com/
   Modified by Rui Santos

   Created by FILIPEFLOP

*/

#include <SPI.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag reading :");
  String content = "";
  String rfidcards[] = {
    "04 63 3B D2 B7 49 80", "24 9C 23 D9"

  };

  //metro card TAG ID : "04 63 3B D2 B7 49 80"
  //key chain: Card UID: 24 9C 23 D9
  //CARD  Card UID: 3F C7 CD 29



  //
  int found = 0;
  int numberOfElements = sizeof(rfidcards) / sizeof(rfidcards[0]); //count of stored TAGS, needs to take this dynamicaaly once integrated with server
  //Serial.println("cards storedcount: ");
  //Serial.println(numberOfElements);



  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //Serial.println(found);
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();


  Serial.print("Card status Message : ");
  content.toUpperCase();


  for (int index = 0; index < numberOfElements ; index++)//, notfoundmsg()
  {
    // if (content.substring(1) == "3F C7 CD 29" || content.substring(1) == "24 9C 23 D9" ) //change here the UID of the card/cards that you want to give access
    //   Serial.println("chcking with card: ");
    //  Serial.println(rfidcards[index]);
    // Serial.println("substring value");
    //Serial.println(content.substring(0));
    if (content.substring(1) == rfidcards[index] ) //change here the UID of the card/cards that you want to give access
    {

      Serial.println("Authorized access");
      //Serial.println(rfidcards[index]);
      delay(100);
      found = 1;
      //Serial.println(found);

    }
  }
  //Serial.println(found);
  //notfoundmsg()


  if (found == 0)
  {
    //Serial.println(found);

    Serial.println(" Access denied");

    delay(100);
  }


}




