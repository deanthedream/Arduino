#include <SPI.h>
#include <Ethernet.h>

/**** DEFINITION DES VARIABLES ****/
// Adresse MAC de la carte Ethernet
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x9E, 0x16 };
// Adresse IP de la carte Ethernet si pas DHCP
byte ip[] = { 192,168,1,222 };
// Adresse du chassis SNELL
byte rollcall[] = { 192,168,1,221 };
// Client Ethernet
EthernetClient clientRollCall;
// Varible réception série
String code;


/**** SETUP DU SYSTEME ****/
void setup() {
// Ouvre la connexion série pour la console
    Serial.begin(9600);
    Serial.println("Serial Connection Established");
  delay(500);
    Serial.println("Something port 9600 bps");
  delay(500);
// Connection Ethernet
  Ethernet.begin(mac,ip);
  delay(500);
    Serial.println("Connection IP en cours ...");
  delay(1000);
     if(clientRollCall.connect(rollcall, 2050)) {
       Serial.println("Connection established");
     }
     else {
       Serial.println("The connection is not established?");
     }
}

/**** CONVERSION RS232 > IP ****/
void loop(){
  // Lecture des données entrantes sur le port série (Arduino Uno).
  // Changer numéro de port si Board différente du UNO.
  // Nécessite une interface TLL vers RS232.
  if(Serial.available()){
    char incomingString = Serial.read();

       if (code.equals("none")){
          Serial.println("Incoming Command");
       } else {
          Serial.println("Commande rescue :"+incomingString);
          clientRollCall.connect(rollcall, 2050);
          delay(100);
          clientRollCall.println("000C0018000011010000000000000000000A100008CB000100000000");
          delay(100);
          clientRollCall.println();
          delay(100);
          //clientRollCall.stop();
      }
    delay(100);
  }

  if(clientRollCall.available()){
    char c = clientRollCall.read();
    Serial.print(c);
  }

  while (Serial.available() > 0) {
    char inChar = Serial.read();
    if (clientRollCall.connected()) {
      clientRollCall.print(inChar);
    }
  }

}


// void setup() {
//   // put your setup code here, to run once:

// }

// void loop() {
//   // put your main code here, to run repeatedly:

// }

