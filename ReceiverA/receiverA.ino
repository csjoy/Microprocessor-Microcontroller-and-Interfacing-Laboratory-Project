#include <VirtualWire.h> // require for rf communication
 
void setup() {
  Serial.begin(9600); // begin serial communication at 9600 baud rate
  Serial.println("Press any push button..."); // to tell what this serial monitor will print
  vw_set_ptt_inverted(true); // configure the "push to talk" polarity
  vw_setup(2000); // begin using all settings and initialize the library
  vw_set_rx_pin(11); // configure the receive pin to 11
  vw_rx_start(); // activate receiver process
}
 
void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // create a variable with proper size to hold incoming message
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // store proper size to hold incoming message into variable buflen
  
  if (vw_get_message(buf, &buflen)) { // read the las received message
    for (int i = 0; i < buflen; i++) { // read one by one from buffer
      char ch = buf[i]; // storing the character to print
      Serial.print(ch); // printing the character
    }
    Serial.println(); // finaly create a blank new line
  }
  delay(300); // to make a suitable delay
}
