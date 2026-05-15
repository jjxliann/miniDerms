#include <SPI.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(9, 8); // CE=9, CSN=8
const byte address[6] = "ADDR1"; // Shortened to exact 5-byte spec

void setup() {
  Serial.begin(9600); // Kept at your working 9600 baud
  while (!Serial) {} 
  printf_begin();
  pinMode(53, OUTPUT); // For Mega SPI Master mode

  if (!radio.begin()) {
    Serial.println("Radio hardware NOT responding!");
    while (1);
  }

  radio.setDataRate(RF24_1MBPS);
  
  // ENABLING ACK ON TRANSMITTER
  radio.setAutoAck(true);       // Enable auto-acknowledgement
  radio.setRetries(15, 15);     // 15 attempts, 4000us delay between retries

  Serial.println("--- Mini DERMS Node Config ---");
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  const char txt[] = "Hello World";
  
  // radio.write returns true ONLY if the receiver sends a successful ACK packet back
  bool ackReceived = radio.write(&txt, sizeof(txt));
  
  if (ackReceived) {
    Serial.println("Sent: Hello World | Status: ACK");
  } else {
    Serial.println("Sent: Hello World | Status:FAILED");
  }

}
