#include <Wire.h> // require for I2C communication
#include <dht.h> // require for dht11 sensor

dht DHT; // create an object of dht
char buf[5]; // this will hold the string value for distance

void setup() {
  Serial.begin(9600); // begin serial communication at 9600 baud rate
  Wire.begin(); // initialize I2C communication
  pinMode(13, OUTPUT); // set trigger pin of ultrasonic sensor as output
  pinMode(12, INPUT); // set echo pin of ultrasonic sensor as input
}

void loop() {
  DHT.read11(11); // read dht11 sensor data from 11 pin
  int temp = DHT.temperature; // get the temperature
  Serial.print("Temperature: "); // label for what we are printing
  Serial.print(temp); // printing temperature
  Serial.println(" C"); // printing unit
  
  Wire.beginTransmission(10); // begin sending data to slave 10
  Wire.write(temp); // send temperature data
  Wire.endTransmission(); // end sending data to slave 10

  digitalWrite(13, LOW); // set the triger pin on LOW for -
  delayMicroseconds(2); // 2 microseconds

  digitalWrite(13, HIGH); // set the triger pin on HIGH for -
  delayMicroseconds(10); // 10 micro
  digitalWrite(13, LOW); // again set the triger pin on LOW

  long duration = pulseIn(12, HIGH); // return the sound wave travel time in microseconds reads from echo pin
  long distance = (duration*0.034)/2; // formula to calculate distance using the fact that sounds travel at 0.034 cm/microseconds
  Serial.print("Distance: "); // label for what we are printing
  Serial.print(distance); // printing distance
  Serial.println(" cm"); // printing unit
  Serial.println(); // to make blank new line 

  sprintf (buf, "%i", distance); // converting distance into character string
  Wire.beginTransmission(15); // begin sending data to slave 15
  Wire.write(buf);// send distance data stored in buf as string
  Wire.endTransmission(); // end sending data to slave 15
  
  delay(300);
}
