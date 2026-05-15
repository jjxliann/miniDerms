#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
//RECIEVER

RF24 radio(9, 8);
const byte address[10] = "ADDRESS01";

void setup() {
 Serial.begin(9600);
  if (!radio.begin()) {
   Serial.println("Receiver: Radio hardware not found!");
   while (1);
 }

 radio.openReadingPipe(0, address);
 radio.setPALevel(RF24_PA_MIN);
 radio.startListening();
  Serial.println("--- Receiver Listening ---");
}

void loop() {
 if (radio.available()) {
   char txt[32] = ""; // Buffer to hold incoming message
   radio.read(&txt, sizeof(txt));
   Serial.print("Received: ");
   Serial.println(txt);
 }
 else{
  Serial.println("doodoofard");
 }
}