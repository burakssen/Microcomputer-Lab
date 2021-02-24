#include <Servo.h> 
#include <Wire.h>

Servo servo1; //create servos
Servo servo2;
Servo servo3;
Servo servo4;

int servoPin1 = 3;  // set pins
int servoPin2 = 5;
int servoPin3 = 6;
int servoPin4 = 9;

int incomingByte = 0; // for incoming serial data

char buffer[17];    // buffer array for characters
char temp[100]; 

int size = 0;

void printValues(){
  int i = 1; //iterator starts with 1
  int temp_index=0; //keeps tamp array index
  bool expecting_hash = true; //flag for # 
  //iterates over the buffer
  while(buffer[i]!='\0'){
    //if it comes to end of first input
    if(buffer[i]=='#' && expecting_hash){
      //adds end chat to temp
      temp[temp_index] = '\0';
      //it does not expecte #
      expecting_hash = false;
      //calls print command
      printCommand();
      temp_index=0; //updates temp index
      i++; //increments iterator
      continue;
    }
    //if it is start character
    if(buffer[i]=='!' && !expecting_hash){
      //it expects #
      expecting_hash = true;
      temp_index = 0;//updates temp index
      i++; //increments iterator
      continue;
    }
    //adds char from buffer to temp //increment
	temp[temp_index]=buffer[i];
    i++; //increment iterator
    temp_index++;//increment temp index
  }
}

//function that executes string between ! and  #
void printCommand(){
  int i=0; //initialized iterator
  int semicolon_counter =0; //keeps number of semicolons
  int semicolon_index[3]; //keeps positions of semicolons
  //it iterates over the command
  while(temp[i]!='\0'){
    //if element is semicolon
    if(temp[i] ==';'){
      //keeps index of semicolon
      semicolon_index[semicolon_counter] = i;
      semicolon_counter+=1; //increments counter
    }
    i++; //increments iterator
  }
  int item = 0; 
  int pow = 1;
  //it iterates over the first input
  for(int j=semicolon_index[0]-1;j>=0;j--){
    //transforms character to integer
    item+= (int)(temp[j]-48)*pow;
    pow*=10;
  }
  //send value to servo3
  servo1.write(item);
 

  item = 0; 
  pow = 1;
  //it iterates over the second input
  for(int j=semicolon_index[1]-1;j>semicolon_index[0];j--){
    //transforms character to integer
    item+= (temp[j]-48)*pow;
    pow*=10;
  }
  //send value to servo2
  servo2.write(item);
  
  item = 0; 
  pow = 1;
  //it iterates over the third input
  for(int j=semicolon_index[2]-1;j>semicolon_index[1];j--){
    //transforms character to integer
    item+= (temp[j]-48)*pow;
    pow*=10;
  }
  //send value to servo3
  servo3.write(item);
 
  item = 0; 
  pow = 1;
  //it iterates over the fourth input
  for(int j=i-1;j>semicolon_index[2];j--){
    //transforms character to integer
    item+= (temp[j]-48)*pow;
    pow*=10;
  }
  //send value to servo4
  servo4.write(item);
 
}

void setup()
{
  Wire.begin(4);                // set address 4
  Wire.onReceive(receiveEvent); // register event
  servo1.attach(servoPin1);		// attach servos
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo1.write(0);				//write servo 0
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

void loop()
{

}

// when data receives this function executes
void receiveEvent(int howMany)
{
  int i=0;
  bool received = false;
  while(Wire.available()) // loop through all but the last
  {
    received = true;
    buffer[i] = Wire.read(); // receive a byte as character
    i++;
  }
  if(received){// if data received
	printValues();	// execute the servo operations
  }
}