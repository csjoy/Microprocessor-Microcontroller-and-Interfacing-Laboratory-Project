#include <VirtualWire.h> // require for rf communication
#include <Wire.h> // require for I2C communication

int temp; // to hold temperature value as int
char msg[25]= {'P',' ',' ','p','u','s','h',' ','b','u','t','t','o','n',' ','i','s',' ','p','r','e','s','s','e','d'}; // message we are going to send with slight modification

void setup() {
  Serial.begin(9600); // begin serial communication at 9600 baud rate
  Serial.println("Slave 1"); // serial monitor label
  Wire.begin(10); // receives data from I2C bus for 15
  Wire.onReceive(receiveEvent); // invoke receiveEvent if any data receives
  vw_set_ptt_inverted(true); // configure the "push to talk" polarity
  vw_setup(2000); // begin using all settings and initialize the library
  vw_set_tx_pin(12); // configure the transmit pin to 12
  pinMode(8, INPUT_PULLUP); // push button setup for pin 8
  pinMode(9, INPUT_PULLUP); // push button setup for pin 9
  pinMode(10, INPUT_PULLUP); // push button setup for pin 10
}

void receiveEvent() {
  temp=0; // first set temp as 0
  if (Wire.available()) { // if data avaialbe in I2C bus
    temp = Wire.read(); // read that data and store it into temp
  }
  Serial.print("Temperature: "); // label for what we are printing
  Serial.print(temp); // printing temperature
  Serial.println(" C"); // printing unit
}

void loop() {
  int a = digitalRead(10); // read the state for pin 10 namely P1
  int b = digitalRead(9); // read the state for pin 9 namely P2
  int c = digitalRead(8); // read the state for pin 8 namely P3
  
  if (a == LOW && b == HIGH && c == HIGH) { // if P1 is active
    msg[1] = '1'; // set second character of msg to 1 so that we get a message starting with 'P1'
    vw_send((uint8_t*)msg, 25); // sending the msg through rf transmitter
  }
  if (a == HIGH && b == LOW && c == HIGH) { // if P2 is active
    msg[1] = '2'; // set second character of msg to 2 so that we get a message starting with 'P2'
    vw_send((uint8_t *)msg, 25); // sending the msg through rf transmitter
  }
  if (a == HIGH && b == HIGH && c == LOW) { // if P3 is active
    msg[1] = '3'; // set second character of msg to 3 so that we get a message starting with 'P3'
    vw_send((uint8_t*)msg, 25); // sending the msg through rf transmitter
  }
}
