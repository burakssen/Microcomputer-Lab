
int prev = 0; 
int upper = 0; //tens digit
int lower = 0; //ones digit

byte mode = 0b0; //mode 0 = inc, mode 1 = dec

const byte modePin = 2; //change mode button
const byte resetPin = 3; //reset button

void increase();
void decrease();
void changeMode();
void resetPINS();


void setup() {
	DDRD = 0b11110011; //input to register D
  	DDRB = 0b11111111; //output to register B
  	DDRC = 0b11111111; //output to register c
  	attachInterrupt(digitalPinToInterrupt(modePin), changeMode, RISING);
  	attachInterrupt(digitalPinToInterrupt(resetPin), resetPINS, RISING);
}

void loop() {
  int current = millis(); //get time
  
  PORTB = lower;//output lower digit to B
  PORTC = upper;//output upper digit to C
  
  if (current - prev >= 1000) { //1s delay

    if(mode == 0b0)
    {
      increase();
    }
    else{
      decrease();
    }
    
    prev = current;//set prev to current time
  }
}

void increase() //increment function
{
  lower++;
  if(lower == 10) //if ones digit is supposed to be 10
  {
    upper++; //increment upper digit
   	if(upper == 10) //if number becomes 99 make it zero
    {
      upper = 0;
    }
    lower = 0; //make lower digit 0
  }
}

void decrease() //same mentality with increment
{
  lower--;
  if(lower == -1)
  {
    upper--;
   	if(upper == -1)
    {
      upper = 9;
    }
    lower = 9;
  }
}

void changeMode() //change mode interrupt subroutine
{
    mode = !mode; //change mod
  
  	if(mode == 0b0)//if mode is zero
    {
      increase(); //increment
    }
    else{ //if mode is one
      decrease(); //decrement
    }
}

void resetPINS() //reset interrupt subroutine
{
  //set both digits 0
  lower = 0; 
  upper = 0;
}