#include <Wire.h> // require for I2C communication

String data = ""; // this will hold the incomming data
int i, j, x, y, percentage; // some variable require in the program
bool first = true; // a flag to be set true only once in the loop

void setup() 
{
  Serial.begin(9600); // begin serial communication at 9600 baud rate
  Serial.println("Slave 2"); // serial monitor label
  Wire.begin(15);  // receives data from I2C bus for 15
  Wire.onReceive(receiveEvent); // invoke receiveEvent if any data receives
  
  pinMode(9, OUTPUT); // set BLUE pin of rgb led to output
  pinMode(10, OUTPUT); // set GREEN pin of rgb led to output
  pinMode(11, OUTPUT); // set RED pin of rgb led to output
}

void receiveEvent() {
  data = ""; // first set data as empty string
  while( Wire.available()) { // if data avaialbe in I2C bus
    data = data + (char)Wire.read(); // read one by on and construct data string
  }
  int distance = data.toInt(); // convert the distance data to int
  percentage = distance / 11; // as we are using a potentiometer ans we can change its value between 0-100, so we map the distance with 100 to get the percentage for potentiometer, only by deviding 11 we get a range between 0-100
  
  Serial.print("Distance: "); // label for what we are printing
  Serial.print(distance); // printing distance
  Serial.println(" cm"); // printing unit

  if (first) {
    first = false; // code will enter this block only once -
    x = distance; // to keep track of our distance changing
    y = round(percentage * 2.55); // as rgb value can be between 0-255, we map percentage we calculate earlier with 255 to get a value between 0-255, also we round that value to get a int
    i = y; // i will hold green value
    j = 255-y; // j will hold red value
  }
  else {
    if (distance < x) { // checking if distance decreases so that rgb can go from green to red
      y = round(percentage * 2.55); // explain as above
      i = y; // i will hold green value
      j = 255-y; // j will hold red value
    }
    else if (distance > x) { // checking if distance increases so that rgb can go from red to green
      y = round(percentage * 2.55); // explain as above
      i = y; // i will hold green value
      j = 255-y; // j will hold red value
    }
  }
  
//  Serial.print(percentage); // for debugging purposes
//  Serial.print("% ");
//  Serial.print("green: ");
//  Serial.print(i);
//  Serial.print(" red: ");
//  Serial.println(j);
  
  analogWrite(9, 0); // set BLUE led to 0, also like constant
  analogWrite(10, i); // set GREEN led to the same value i hold
  analogWrite(11, j); // set RED led to the same value i hold
}

void loop() {
}
