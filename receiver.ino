#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); 
  radio.setPALevel(RF24_PA_MIN);       
  radio.startListening(); 
}

void loop() {
  // Receiving Values
  if (radio.available())            
  {
    int val;                
    radio.read(&val, sizeof(val)); 
    Serial.println(val);

  }
}
