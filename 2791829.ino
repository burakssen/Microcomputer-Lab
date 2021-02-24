const byte interruptPin1 = 2; //2. digital pin as interrupt pin
const byte interruptPin2 = 3; //3. digital pin as interrupt pin

int finished_flag = 0; //flag to check game if finished or not
int left_right_flag=0; //flag to check which player's turn
int flag = 1; //helper flag for delay mechanism

int left_select = 0; //Keeps left player's selected number 
int right_select =0; //Keeps right player's selected number 

int counter_left_upper = 0; //keeps leftmost display content
int counter_left_lower = 0; //keeps second leftmost display content
int counter_right_upper = 0; //keeps second rightmost display content
int counter_right_lower = 0; //keeps rightmost display content

int prev = 0; //helper previous time varible for counter  
int prev1 = 0; //helper previous time varible for display mechanism

//seven segment content for analog ports
byte sevensegment0[16] = {
  0b000,
  0b100,
  0b001,
  0b000,
  0b100,
  0b010,
  0b010,
  0b000,
  0b000,
  0b000,
  0b000,
  0b110,
  0b011,
  0b100,
  0b011,
  0b011
};

//seven segment content for digital ports
byte sevensegment1[16] = {
  0b00010000,
  0b11110000,
  0b00100000,
  0b01100000,
  0b11000000,
  0b01000000,
  0b00000000,
  0b11110000,
  0b00000000,
  0b01000000,
  0b10000000,
  0b00000000,
  0b00010000,
  0b00100000,
  0b00000000,
  0b10000000
};

//interrupt function for left button
void leftplayer(){
  //if it left player's turn and game did not finished
  if(left_right_flag ==0 && finished_flag==0){
  //calculates selected number from bits
  left_select = counter_left_lower+10* counter_left_upper;
  left_right_flag =1; //turn of play passes to the second player
  }
}

void rightplayer(){
  //if it right player's turn and game did not finished
  if(left_right_flag ==1 && finished_flag==0){
  //calculates selected number from bits  
  right_select = counter_right_lower+10* counter_right_upper;
  finished_flag = 1; //game finishes
  
  //if selected numbers are equal
  if(right_select == left_select){
    //displays show 2222
    counter_left_lower=2;
    counter_left_upper=2;
    counter_right_lower=2;
    counter_right_upper=2;  
  }else{//if selected numbers are not equal
    //displays show 1111
    counter_left_lower=1;
    counter_left_upper=1;
    counter_right_lower=1;
    counter_right_upper=1;  
  }
  }
}


void setup()
{
  DDRD = 0b11110011; // sets digital 2-3 as input, others are output
  DDRB = 0b11111111; // sets digital 8-13 as output
  DDRC = 0b11111111; // sets analog 0-5 as output
  
  //interrupt functions defined for interrupt pins for signal rise behaviour
  attachInterrupt(digitalPinToInterrupt(interruptPin1), leftplayer, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), rightplayer, RISING);
}

void loop()
{
 int current = millis(); //time passed since the beginning of the circuit
 
 //if flag is 1, it means that left-most display should be shown
 //it controls 5ms passed or not
 if (current - prev1 >= 5 && flag == 1) {
  	PORTC = 0b011111; //activates left-most display 
    prev1 = current; //updates time
   	//gives output for required number
    PORTD = sevensegment1[counter_left_upper];
  	PORTB = sevensegment0[counter_left_upper];
    flag = 2; //updates flag as 2
  }
  
  //if flag is 2, it means that second left-most display should be shown
  //it controls 5ms passed or not
  if (current - prev1 >= 5 && flag == 2) {
  	PORTC = 0b101111; //activates second left-most display 
    prev1 = current; //updates time
    //gives output for required number
   	PORTD = sevensegment1[counter_left_lower];
  	PORTB = sevensegment0[counter_left_lower];
   	flag = 3; //updates flag as 2
  }

  //if flag is 3, it means that second right-most display should be shown
  //it controls 5ms passed or not  
  if (current - prev1 >= 5 && flag == 3 ) {
  	PORTC = 0b110111; //activates second right-most display 
    prev1 = current; //updates time
    //gives output for required number
    PORTD = sevensegment1[counter_right_upper];
  	PORTB = sevensegment0[counter_right_upper];
    flag=4; //updates flag as 4
  }

  //if flag is 4, it means that right-most display should be shown
  //it controls 5ms passed or not
  if (current - prev1 >= 5 && flag == 4){
  	PORTC = 0b111011; //activates right-most display 
    prev1= current; //updates time
    //gives output for required number
    PORTD = sevensegment1[counter_right_lower];
  	PORTB = sevensegment0[counter_right_lower];
    flag=1; //updates flag as 1
  }
  
  //if 200ms passed, game not finished and it is turn for left player
  if (current - prev >= 200 && finished_flag ==0 && left_right_flag ==0) {
	//increments lower bit
    counter_left_lower++;
   	//if it reaches to 10
    if(counter_left_lower == 10)
    {
      counter_left_lower = 0; //it sets lower bit as 0
      counter_left_upper++; //increments upper bit
    }
    //if it reaches 21, it must return 0
    if(counter_left_upper == 2 && counter_left_lower ==1 )
    {
      //sets counter as 00
      counter_left_lower = 0;
      counter_left_upper = 0;
    }
    prev = current; //updates time
  }
  //if 200ms passed, game not finished and it is turn for right player
  if (current - prev >= 200 && finished_flag ==0 && left_right_flag ==1) {
	//increments lower bit
    counter_right_lower++;
   	//if it reaches to 10
    if(counter_right_lower == 10)
    {
      counter_right_lower = 0; //it sets lower bit as 0
      counter_right_upper++; //increments upper bit
    } 
    //if it reaches 21, it must return 0
    if(counter_right_upper == 2 && counter_right_lower ==1 )
    {
      //sets counter as 00
      counter_right_lower = 0;
      counter_right_upper = 0;
    }
    prev = current; //updates time
  }
}


