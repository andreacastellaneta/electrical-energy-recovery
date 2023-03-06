#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include <nRF24L01.h>
#include <RF24.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int pinRadio1 = 9;
int pinRadio2 = 10;
volatile boolean f_wdt = 1;

RF24 radio(pinRadio1, pinRadio2); 
const byte address[6] = "00001";  

void setup(){
  //setup_watchdog(8); // approximately 4 seconds sleep
  wdt_enable(WDTO_2S);

  // Setup radio transmitter
  radio.begin();                 
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); 
  radio.stopListening();
}

void loop(){
  if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
    f_wdt=0;       // reset flag

    //Read Sensor
    int val;
    val = analogRead(0);
    // Code Transmitter    
    radio.write(&val, sizeof(val));

    //pinMode(pinLed,INPUT); // set all used port to intput to save power
    system_sleep();
    //pinMode(pinLed,OUTPUT); // set all ports into state before sleep
  }
}

// set system into the sleep state 
// system wakes up when wtchdog is timed out
void system_sleep() {
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out 
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {

  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  //WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  //WDTCR = bb;
  //WDTCR |= _BV(WDIE);
}
  
// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt=1;  // set global flag
}
