#include <Wire.h>
int flexs[4] = {A0,A1,A2,A3}; // flex pins

void setup() {
  Wire.begin(8);                // set address #8
  Wire.onRequest(requestEvent); // register event
  pinMode(flexs[0], INPUT); // set flex pinmode 1
  pinMode(flexs[1], INPUT);
  pinMode(flexs[2], INPUT);
  pinMode(flexs[3], INPUT);
}


void loop() {

}

void requestEvent() {   //requestEvent function
  char send_item[17];   // local char array
  send_item[0] = '!';   // first character
  for(int i=0; i<4;i++){    
  // for four numbers there must be 4 iteration 
  	double data = analogRead(flexs[i]); // take the value from flex
    double readVoltage = (data/1023.0)*5.0; //calculate the voltage
    double current = (5.0 - readVoltage)/100.0; //calculate the current
    double resistance = readVoltage/current;    //calculate the resistance
    //calculate angle from the resistance
    int angle = (int)abs(((resistance-29.99)/132.99)*180.0);
    int val = angle%10;//angle's one's place
    send_item[4*(i+1)-1]= 48+val;//set ones place
    angle/=10;  
    val = angle%10; // angle's ten's place
    send_item[4*(i+1)-2]= 48+val;   // set tens place
    angle/=10;  
    val = angle%10; //angle's hundred's place
    send_item[4*(i+1)-3]= 48+val;   //set hundreds place
  }
  send_item[4]= ';'; //place divider chars
  send_item[8]= ';';
  send_item[12]= ';';
  send_item[16] ='#'; // place end char
  Wire.write(send_item);    // send data to master
}