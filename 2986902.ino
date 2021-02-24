#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
}

void waitMillis(int time) // custom delay
{
  long start_time = millis();
  while(millis() - start_time <= time);
}


void loop() {
  waitMillis(200);
  Wire.requestFrom(8, 17);   // request 17 bytes from slave device #8
  char send_item[17];
  int i=0;
  bool received = false;
  while (Wire.available()) { // slave may send less than requested
    received = true;
    send_item[i] = Wire.read(); // receive a byte as character
    i++;
  }
  
  if(received){
    Wire.beginTransmission(4); // transmit to device #4
  	Wire.write(send_item); 
  	Wire.endTransmission();    // stop transmitting
  }

}