
# RFID based Entry/Exit Management System

RFID is a nascent technology, deeply rooted by its early developments in using radar1 as a harbinger of adversary planes during World War II. A plethora of 
industries have leveraged the benefits of RFID technology for enhancements in sectors like military, sports, security, airline, animal farms, healthcare and other areas. 
Industry specific key applications of this technology include vehicle tracking, automated inventory management, animal monitoring, secure store checkouts, 
supply chain management, automatic payment, sport timing technologies, etc.

This project aims the distinctive components of RFID technology and focuses 
on its core competencies: scalability and security. Presently in IITK at all the entry-exit gate there is manual entry in the log which is very time consuming and 
hard to maintain. So we present an intelligent and fast RFID based entry-exit marking system which involves an RFID tag and reader to solve this problem.




## Installations
1. Install Arduino IDE.
2. Install MFRC522 library on your arduino IDE. (To install the library navigate to Sketch > Include Libraries > Manage Libraries… Wait for Library Manager to download the library index and update the list of installed libraries.)


## Getting started
//TO WRITE DATA ON A CARD

1. Open rfid_write_USER.
2. Choose Arduino UNO as our board from dropdown.
3. Upload and verify the code.
4. Open Serial Monitor from Tools.
5. Keep the RFID near the card while it writes the data on the card.
6. Enter the details ending with a "#" after every inputs.


.

//TO READ DATA ON A CARD 
1. Open rfid_read_USER
2. Choose Arduino UNO as our board from dropdown.
3. Upload and verify the code.
4. Open Serial Monitor from Tools.
5. Scan the card by taking it near the reader.
