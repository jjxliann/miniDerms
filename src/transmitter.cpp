#include <SPI.h>
#include <RF24.h>
#include <printf.h>
//RECIEVER

RF24 radio(9, 8); // CE=9, CSN=8
const byte address[10] = "ADDRESS01";

void setup() {
  Serial.begin(9600);
  while (!Serial) {} // wait for Serial Monitor to open
  // links the RF24 printf.h to your Serial port automatically
  printf_begin();
  // for Arduino Mega to act as SPI Master
  pinMode(53, OUTPUT);

  if (!radio.begin()) {
    Serial.println("Radio hardware NOT responding!");
    while (1);
  }

  radio.setDataRate(RF24_1MBPS);

  Serial.println("--- Mini DERMS Node Config ---");
  radio.stopListening();
  radio.openWritingPipe(address);
  //radio.printDetails();
}

void loop() {
  const char txt[] = "Hello World";
  radio.write(&txt, sizeof(txt));
  delay(1000);
}