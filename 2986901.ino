//includes servo library
#include <Servo.h> 

//Defined servo motors as servo1,2,3,4
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//Defines corresponding pins
int servoPin1 = 3;
int servoPin2 = 5;
int servoPin3 = 6;
int servoPin4 = 9;

char buffer[100]; //buffer for input stream
char temp[100]; //helper for string checking operations

int size = 0; //input size variable

void setup() {
  Serial.begin(9600); // opens serial port
  //associates pins and servos 
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  //initialized servos with 0
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

//function that parses commands
void execute(){
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
  Serial.print("S0:");
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
  Serial.print(item);
  Serial.print("; ");
  Serial.print("S1:");

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
  Serial.print(item);
  Serial.print("; ");
  Serial.print("S2:");
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
  Serial.print(item);
  Serial.print("; ");
  Serial.print("S3:");
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
  Serial.println(item);
}

//function that checks input structure
bool checker(){
  //if its first character is not !
  if(buffer[0] != '!'){
    //prints error message
    Serial.println("Error! There is no start char.");
    return false;
  }
  //if its first character is not #
  if(buffer[size-1] != '#'){
    //prints error message
    Serial.println("Error! There is no end char.");
    return false;
  }
  int i = 1; //iterator starts with 1
  int temp_index=0; //temp array index
  bool expecting_hash = true; //hash is needed or not 
  //starts iteration until the end of input
  while(buffer[i]!='\0'){
    //if # comes, when we do not expect
    if(buffer[i]=='#' && !expecting_hash){
      //prints error message
        Serial.println("Error! There is no start char.");
    	return false;
    }
    //if ! comes, when we expect #
    if(buffer[i]=='!' && expecting_hash){
      //prints error message
        Serial.println("Error! There is no end char.");
    	return false;
    }
    //if end char arrives
    if(buffer[i]=='#' && expecting_hash){
      //adds end char to temp
      temp[temp_index] = '\0';
      //updates expect bool
      expecting_hash = false;
      //calls check command
      bool valid = checkCommand();
      //updates temp index
      temp_index=0;
      //if command is not valid
      if(!valid){
        //directly returns false
        return false;
      }
      i++; //increments iterator
      continue;
    }
    //when start char arrives
    if(buffer[i]=='!' && !expecting_hash){
      //it expects for #
      expecting_hash = true;
      //initialized tamp index
      temp_index = 0;
      i++;//increments iterator
      continue;
    }
    //adds char from buffer to temp
	temp[temp_index]=buffer[i];
    i++;//increments iterator
    temp_index++;//increments temp iterator
  }
  return true;
}

//function that checks string between ! and  #
bool checkCommand(){
  int i=0; //initialized iterator
  int semicolon_counter =0; //keeps number of semicolons
  int semicolon_index[3]; //keeps positions of semicolons
  //if directly starts with semicolon
  if (temp[0] == ';'){
    //prints error message
     Serial.println("Error! All parameters must be filled.");
     return false;
  }
  //it starts iteration through the temp
  while(temp[i]!='\0'){
    //if last element or two consecutive elements are semicolon
    if((temp[i] ==';' && temp[i+1] =='\0') || (temp[i]==';' && temp[i+1]==';') ){
      	//prints error message
    	Serial.println("Error! All parameters must be filled.");
    	return false;
    }
    //if element is semicolon
    if(temp[i] ==';'){
      	//increments counter
		semicolon_counter++;
      	//if semicolon numbers are higher than 3
        if(semicolon_counter>3){
          	//prints error message
    		Serial.println("Error! There is extra input.");
    		return false;
  		}
      	//takes index of semicolon to array
    	semicolon_index[semicolon_counter-1] = i;
    }
    i++; //increments iterator
  }
  //if number of semicolons is less than 3
  if(semicolon_counter<3){
    //prints error message
    Serial.println("Error! There is not enough input.");
    return false;
  }

  int item = 0; 
  int pow = 1;
  //it iterates over the first input
  for(int j=semicolon_index[0]-1;j>=0;j--){
    //transforms character to integer
    item+= (temp[j]-48)*pow;
    pow*=10;
  }
  //if it is bigger than 180
  if(item>180){
    //prints error message
    Serial.println("Error! Angle value must be less than 180.");
    return false;
  }
  item = 0; 
  pow = 1;
  //it iterates over the second input
  for(int j=semicolon_index[1]-1;j>semicolon_index[0];j--){
    //transforms character to integer
    item+= (temp[j]-48)*pow;
    pow*=10;
  }
  //if it is bigger than 180
  if(item>180){
    //prints error message
    Serial.println("Error! Angle value must be less than 180.");
    return false;
  }
  item = 0; 
  pow = 1;
  //it iterates over the third input
  for(int j=semicolon_index[2]-1;j>semicolon_index[1];j--){
    //transforms character to integer
    item+= (temp[j]-48)*pow;
    pow*=10;
  }
  //if it is bigger than 180
  if(item>180){
    //prints error message
    Serial.println("Error! Angle value must be less than 180.");
    return false;
  }
  item = 0; 
  pow = 1;
  //it iterates over the fourth input
  for(int j=i-1;j>semicolon_index[2];j--){
    //transforms character to integer
    item+= (temp[j]-48)*pow;
    pow*=10;
  }
  //if it is bigger than 180
  if(item>180){
    //prints error message
    Serial.println("Error! Angle value must be less than 180.");
    return false;
  }
  return true;
}

void waitMillis(int time)
{
  long start_time = millis();
  while(millis() - start_time <= time);
}


void loop() {
  size = 0; //keeps size of input
  bool isRead = false; //input reading finish or not flag
  bool invalid = false; //input validation flag
  //until input stream finishes
  while (Serial.available()) {
    isRead =true; //read flag changes
    waitMillis(2); //2ms delay
    char value = Serial.read(); //reads first char
    if(!invalid){ //if previous part was not invalid
      	//checks character types	
    	if(!((value<=57 && value>=48) || value=='#' || value==';'|| value=='!')){
          	//if it is not valid
       		Serial.println("Error! Invalid Input."); //prints error message
       		invalid =true; //assigns true to invalid flag
    		}
     	buffer[size] = value; //takes character into buffer
    }
    size++; //increments size
 }
  buffer[size]='\0'; //end character
  //if input is read and characters are valid
  if(isRead && !invalid){
    //calls structure checker
    bool valid = checker();
  	if(valid){
      	//if it is valid, prints and runs command
  		execute();
  	}
  }

  
  
}