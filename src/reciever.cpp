#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8);
const byte address[6] = "ADDR1"; // Must match Mega 

void setup() {
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("Receiver: Radio hardware not found!");
    while (1);
  }

  // ENABLING ACK ON RECEIVER
  radio.setAutoAck(true);             // Enable auto-acknowledgement
  radio.openReadingPipe(1, address);  //  Changed from Pipe 0 to Pipe 1
  
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("--- Receiver Listening ---");
}

void loop() {
  if (radio.available()) {
    char txt[32] = ""; 
    radio.read(&txt, sizeof(txt)); // Hardware sends ACK to Mega   here
    
    Serial.print("Received: ");
    Serial.println(txt);
  }
}
