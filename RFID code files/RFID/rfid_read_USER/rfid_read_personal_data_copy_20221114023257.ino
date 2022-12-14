

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           
#define SS_PIN          10          

MFRC522 mfrc522(SS_PIN, RST_PIN);  

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  Serial.begin(9600);                                           
  SPI.begin();                                                
  mfrc522.PCD_Init();                                              

}


void loop() {

  
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  
  byte block;
  byte len;
  MFRC522::StatusCode status;

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }


  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }


  byte buffer1[18];

  block = 4;
  len = 18;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); 
  if (status != MFRC522::STATUS_OK) {
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    return;
  }

  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(",");



  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {

    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    return;
  }
    else
  {
    for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
    }
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(3000);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);    
  }



  delay(1000);

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

