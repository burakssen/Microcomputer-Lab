int comp = 31250;
int timer = 0;

byte pattern = 0;

const byte button = 3;

void changePattern();

int counter = 0;
int temp3;
byte temp0 = 0b00010000;
byte temp1 = 0b00001000;  
byte temp2 = 0b00000000;

byte twos = 0b10000000;

void setup()
{
  DDRD = 0b11110111;
  DDRB = 0b111111;
  
  PORTD = 0b00000000;
  PORTB = 0b000110;
 
  // initialize timer1 
  noInterrupts();           
  // disable all interrupts
  TCCR1A = 0;
  
  TCCR1B |= (1 << CS12);    
  // 256 prescaler
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);
    
  TCNT1  = timer;
  // interrupt number 31250 lerde xd
  OCR1A = comp;           
  // compare match register
  
  TIMSK1 |= (1 << OCIE1A);  
  // enable timer compare interrupt
  interrupts();             
  // enable all interrupts
  attachInterrupt(digitalPinToInterrupt(button), 
                  changePattern, RISING);  
}

ISR(TIMER1_COMPA_vect)
{// timer compare interrupt service routine
  
  if(pattern == 0) //first patter
  {
    temp0 = temp0 << 1;	//shift the value by 1 to left
    temp1 = temp1 >> 1; //shift the value by 1 to right
    
    temp2 = temp0 | temp1;// or the two values

    if(temp2 == 0)//if our value is 0
    {
      temp1 = 0b10000000;//jump to start
      temp0 = 0b00000001;
      
      temp2 = temp0 | temp1;//or the value
    }
    

    PORTD = temp2 << 6;//shift the value by 6
    PORTB = temp2 >> 2;//shift the value by 2
  }
  else
  {
    if(counter%2 ==0){
      //calculate if counter is even or not
      temp2 = temp0|twos;
      //or the value with 0b10000000
    }else{
      temp2 = temp0;
    }
    if((counter/7)%2 == 0){
      //calculate if our led is going left or right
    	temp0 = temp0 << 1; // shift left
    }else{
    	temp0 = temp0 >> 1;//shift right
    }
    
    
    
    PORTD = temp2 << 6;
    PORTB = temp2 >> 2;
  }
  counter++;//increment counter
  TCNT1 = timer;//reset timer
}

void loop()
{
}

void changePattern()
{
  pattern = !pattern;//change the pattern
  if(pattern == 0)//pattern 1
  {
    temp0 = 0b00010000;//set the starting values
    temp1 = 0b00001000;
    
   	PORTD = 0b00000000;
  	PORTB = 0b000110;
  }
  else 
  {
  	temp0 = 0b00000001;//set the starting values
    temp1 = 0b10000000;
    
    PORTD = 0b01000000;
  	PORTB = 0b100000;
  }
  TCNT1 = timer;//reset timer
  counter = 0;//reset counter
}