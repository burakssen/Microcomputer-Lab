int counter = 0; //time counter

int flag = 1;	// a flag for controlling delays for each of the if statement
const byte interruptPin = 2;// set interruptpin 2

int finished_flag = 0;	//a flag to check if game is finished or not

int prev = 0;	// previous time for the counter
int prev1 = 0;	//previous time for the other delays

int target = 321;	//game target

int array[3] = { 0, 0, 0 };	//for storing values of 3 seven degment display

byte sevensegment0[16] = {	//first three bits of the seven segment display codes
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

byte sevensegment1[16] = {//last four bits of the seven segment display codes
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

void shiftCounter();

void setup()
{
  DDRD = 0b11111011;//set second bit as an input and other pins as an output
  DDRB = 0b11111111;
  DDRC = 0b11111111;
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), 
                  shiftCounter, RISING); //set pin 2 as an interrupt pin, option and interrupt function
}

void loop()
{
  
 int current = millis(); //take current time
  
 if (current - prev1 >= 5 && flag == 1) { //if current time - previous time is 5ms and flag is 1 (for the first delay)
  	PORTC = 0b011111; // activate first seven segment
    prev1 = current;	// set current time to previous time
    PORTD = sevensegment1[counter];	// show the value of the counter
  	PORTB = sevensegment0[counter];
    flag =2; // set second if statement's flag
  }
  
  
  if (current - prev1 >= 5 && flag == 2) {//if current time - previous time is 5ms and flag is 2 (for the second delay)
  	PORTC = 0b101111;// activate second seven segment
    prev1 = current;// set current time to previous time
   	PORTD = sevensegment1[array[0]];// show the value of the second seven-segment
  	PORTB = sevensegment0[array[0]];
   	flag =3;//set third if statement's flag
  }

    
  if (current - prev1 >= 5 && flag == 3 ) {//if current time - previous time is 5ms and flag is 3 (for the third delay)
  	PORTC = 0b110111;// activate third seven segment
    prev1 = current;// set current time to previous time
    PORTD = sevensegment1[array[1]];// show the value of the third seven-segment
  	PORTB = sevensegment0[array[1]];
    flag=4;//set fourth if statement's flag
  }


  if (current - prev1 >= 5 && flag == 4){//if current time - previous time is 5ms and flag is 4 (for the fourth delay)
  	PORTC = 0b111011;// activate fourth seven segment
    prev1= current;// set current time to previous time
    PORTD = sevensegment1[array[2]];// show the value of the fourth seven-segment
  	PORTB = sevensegment0[array[2]];
    flag=1;//set first if statement's flag
  }
  
  if (current - prev >= 1000 && finished_flag ==0) {// if current time - previous time is 1000ms and if our game is not finished
	counter++; // increase the counter
    
    if(counter == 16) // if counter is 16 which is if seven-segment is F+1
    {
      counter = 0; // set counter to 0
    }
    prev = current;// set current time to previous time
  }
  
  if(array[0]*100+array[1]*10+array[2]==target){ // we our array is the target value
    array[0]=0; // set all of the values to 0
    array[1]=0;
    array[2]=0;
    counter =0;
    finished_flag =1; // and set finished flag to finish the game
  }
}

void shiftCounter() // interrupt function
{
  if(finished_flag == 0){ // if game is not finished
    array[2] = array[1]; // shift second value to third value
  
  	array[1] = array[0]; // shift first value to the second value
  
  	array[0] = counter; // shift counters value to the first value
  }
}

 
