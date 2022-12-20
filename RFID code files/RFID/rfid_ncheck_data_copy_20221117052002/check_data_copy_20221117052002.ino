#include <Ethernet.h>
#include <avr/pgmspace.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           
#define SS_PIN          10          
char inString[32];
int stringPos = 0;
boolean startRead = false;

MFRC522 mfrc522(SS_PIN, RST_PIN);  
byte mac[] = { 0x84, 0x42, 0x8B, 0xBA, 0xB2, 0x31 };
IPAddress server(192,168,15,11);
IPAddress ip(192, 168, 5, 92);
IPAddress gateway(192,168,5,1);
IPAddress DNSserver(192,168,5,1);
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(9600);
  init_ethernet();
  delay(1000);
  Ethernet.begin(mac, ip, gateway, DNSserver, subnet);
  pinMode(2, OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  Serial.begin(9600);                                           
  SPI.begin();                                                
  mfrc522.PCD_Init(); 
}

EthernetClient client;

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

String readPage(){

  stringPos = 0;

  memset( &inString, 0, 32 );

  while (true)  {

    if (client.available()) {
      while (client.connected())  {
        char c = client.read();
        if (c == '<' ) {
          startRead = true;
        } 
        else if (startRead)  {
          if (c != '>') {
            inString[stringPos] = c;
            stringPos ++;
          }
          else {
            // We found
            startRead = false;
  
            client.flush();
            return inString;
          }
        }
      }
    }
  }
}



void sendData(String  thisData,  String InOut) { 
  if (client.connect(server, 3000)) {
    client.print("GET /verify/in/");
    delay(100);
    client.print(thisData);                 

    delay(1000);
    readPage();



    if(inString[0] == '1') {
    //Need to transfer this back to local host

    client.flush();
    client.stop();
  }


  else {
    client.stop();
    init_ethernet();
  }

}

void sendData(String  thisData,  String InOut) { 
  if (client.connect(server, 3000)) {
    client.print("GET /verify/in/");
    delay(100);
    client.print(thisData);
    client.println();                      

    delay(1000);
    readPage();

    if(inString[0] == '1') {
      digitalWrite(8,LOW);
    }
    client.flush();
    client.stop();
  }
}

