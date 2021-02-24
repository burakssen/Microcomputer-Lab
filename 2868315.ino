
//array that contains the label
char title[16] = {
  'C','O','U','N','T',
  'D','O','W','N',' ',
  'T','I','M','E','R',':'};

//timer comparison number
int comp = 62500;
//timer variable
int timer = 0;

//set cursor function sets cursor at an index
void setCursor(int index){//thischanges ddram address
   sendCMD((index | 0b10000000));
   waitMicros(55);
}

void triggerEnable()//Enable the lcd
{
	PORTB = 0b000001;//enable
  	PORTB = 0b000000;//disable
}

//send char function prints characters on lcd
void sendChar(int cursor, byte cmd){
  setCursor(cursor); // first sets the cursor
  PORTD = ((cmd & 0b11110000)) | 0b00000100; 
  // send upper 4 bit of the character
  triggerEnable(); // enable lcd
  // send lower 4 bit of the character
  PORTD = ((cmd & 0b00001111)<< 4) | 0b00000100;
  triggerEnable(); // enable lcd
}

//send command function sends commands
// we use this to cursor set
void sendCMD(byte cmd){
  //send upper 4 bits of the command
  PORTD = ((cmd & 0b11110000));
  triggerEnable();// execute the command
  //send lower 4 bits of the commands
  PORTD = ((cmd & 0b00001111)<< 4);
  triggerEnable();// execute the command
}



void waitMicros(int time){
  long start_time=micros();
  while(micros()-start_time < time);
}

void waitMillis(int time){
  long start_time=millis();
  while(millis()-start_time < time);
}


void initLCD(){
  PORTD= PORTD&B11110011; //Clear RS and R/W
  waitMillis(100);  //Wait 100 ms
  
  PORTD= (PORTD&B00001111)|B00110000; //Special case of 'Function Set'
  triggerEnable();		//Send Enable Signal
  waitMillis(5);   //Wait 5ms
  
  PORTD= (PORTD&B00001111)|B00110000; //Special case of 'Function Set'
  triggerEnable();		//Send Enable Signal
  waitMicros(150);
  
  PORTD= (PORTD&B00001111)|B00110000; //Function set, Interface is 8 bit longs
  triggerEnable();		//Send Enable Signal
  waitMicros(150);
  
  PORTD= (PORTD&B00001111)|B00100000; //Initial 'Function Set' to change interface
  triggerEnable();		//Send Enable Signal
  waitMicros(150);
  
  PORTD= (PORTD&B00001111)|B00100000; //'Function Set' DL=0 // Dataline 8bits
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B10000000; //'Function Set' N=1 //2 lines
 									  // F =0 5x8 dots
  triggerEnable();		//Send Enable Signal
  waitMicros(55);
  
  PORTD= (PORTD&B00001111); //Dısplay On Of control
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B10000000; 
  triggerEnable();		//Send Enable Signal
  waitMicros(55);
  
  PORTD= (PORTD&B00001111); //Clear display
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B00010000; 
  triggerEnable();		//Send Enable Signal
  waitMillis(5);
  
  PORTD= (PORTD&B00001111); //Entry mode set
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B01100000; //ID=1 Increment, S=0
  triggerEnable();		//Send Enable Signal
  waitMicros(55);
  
  PORTD= (PORTD&B00001111); //Dısplay On Of control
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B11100000; //Display =1
  								      //Cursor =1
  									  //Blink cursor=0
  triggerEnable();		//Send Enable Signal
  waitMicros(55);
}

void setup() {
  DDRD = 0b11111111; // set portd registers as output
  DDRB = 0b11111111; //set portb registers as input
  initLCD(); //initialize lcd panel
  

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);
    
  TCNT1  = timer;
  // interrupt number 31250 lerde xd
  OCR1A = comp;           // compare match register
  
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}

int hour = 0;
int minute = 1;
int second = 1;

ISR(TIMER1_COMPA_vect) 
{
  // timer compare interrupt service routine
  TCNT1 = timer; // set timer to 0

  if(second == 0){ // if seconds are 0
    if(minute == 0){ // if minutes are 0
      if(hour ==0){ // if hours are 0
        sendChar(64,hour/10+48); 
        // send first digit of the hour in ascii
        sendChar(65,hour%10+48);
        // send second digit of the hour in ascii
        sendChar(67,minute/10+48);
        // send first digit of the minute in ascii
        sendChar(68,minute%10+48);
        // send second digit of the minute in ascii
        sendChar(70,second/10+48);
        // send first digit of the second in ascii
        sendChar(71,second%10+48);
        // send second digit of the second in ascii
      }else{
        hour--; // if hour is not 0 decrease by 1
        minute = 59; //set minute to 59
        second = 59; //set second to 59
        sendChar(64,hour/10+48);
        sendChar(65,hour%10+48);
        sendChar(67,minute/10+48);
        sendChar(68,minute%10+48);
        sendChar(70,second/10+48);
        sendChar(71,second%10+48);
      }
    }else{
      minute--; //if minute is not 0 decrease by 1
      second = 59;	// set seconds to 59
      sendChar(67,minute/10+48);
      sendChar(68,minute%10+48);
      sendChar(70,second/10+48);
      sendChar(71,second%10+48);
      
    }
  }else{
    second--; // if second is not 0 decrese by 1
    sendChar(70,second/10+48);
    sendChar(71,second%10+48);
  }
}


int counter =0;
int flag = 0;
int isFirstLineFinished =0;
int prev = 0;
void loop() {
  int current = millis();
  if(current - prev >= 5) // 5ms delay
  {
    if(hour==0&&minute==0&&second ==0){
    	PORTB = 0b001000; 
      	// if time is up vibrate the piezo
  	}
  	if(!isFirstLineFinished){ 
     // if first line is not written                      
     sendChar(counter, title[counter]);	
     //send first lines chars
     counter++; // increase counter by 1
     if(counter ==16){	// if counter is 16
       counter =0;	//set counter to 0
       isFirstLineFinished = 1;	
       // and set finish first line
     } 
  	}
  	if(!flag){ // if flag is not set
    	sendChar(66,':'); 
      	// set chars to second line
    	sendChar(69,':');
   		sendChar(64,hour/10+48);
   		sendChar(65,hour%10+48);
   		sendChar(67,minute/10+48);
   		sendChar(68,minute%10+48);
   		sendChar(70,second/10+48);
   		sendChar(71,second%10+48);
   		sendChar(72,' ');
   		sendChar(73,' ');
   		sendChar(74,' ');
    	sendChar(75,' ');
   		sendChar(76,' ');
   		sendChar(77,' ');
   		sendChar(78,' ');
   		sendChar(79,' ');

   		flag = 1; // set flag to 1
  	}
    prev = current;
  }
}
