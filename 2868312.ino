int comp = 20000;
int timer = 0;
int prev1 =0;
const byte button_first = 2;
const byte button_second = 3;

int lap_counter = 0;
int previous_lap_time = 0;
int current_time = 0;

int start_flag =0;
int display_number=0;
int flag =1;

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

void start(){
  start_flag = 1;
}

void lap(){
  lap_counter++;
  int current_lap = current_time - previous_lap_time;
  previous_lap_time = current_lap;
  
  float printed_lap = current_lap/100.0;
  float printed_time = current_time/100.0;
  
  Serial.print("Lap Number:");
  Serial.println(lap_counter);
  Serial.print("Lap Time:");
  Serial.println(printed_lap);
  Serial.print("Total Time:");
  Serial.println(printed_time);
}

void setup()
{
  DDRD = 0b11110011;
  DDRB = 0b011111;
  DDRC = 0b111111;
  Serial.begin(9600);
  
  PORTD = 0b00000000;
  PORTB = 0b000110;
 
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  
  TCCR1B &= ~(1 << CS12);    // 8 prescaler
  TCCR1B |=  (1 << CS11);
  TCCR1B &= ~(1 << CS10);
    
  TCNT1  = timer;

  OCR1A = comp;           // compare match register
  
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
  attachInterrupt(digitalPinToInterrupt(button_first), start, RISING);
  attachInterrupt(digitalPinToInterrupt(button_second), lap, RISING);  
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  if(start_flag){
    current_time++;
    if(current_time == 10000){
      current_time=0;
    }
  }
  TCNT1=0;
}



void loop()
{
  if(PINB>>5 == 0b000001){
  	lap_counter = 0;
    previous_lap_time = 0;
    current_time = 0;
    start_flag =0;
  }
  
 int current = millis(); //take current time
  
 if (current - prev1 >= 2 && flag == 1) { //if current time - previous time is 5ms and flag is 1 (for the first delay)
    prev1 = current;	// set current time to previous time
  	display_number = current_time%10;
  	PORTC = 0b111011;
  	PORTD = sevensegment1[display_number];
  	PORTB = sevensegment0[display_number];
    flag =2; // set second if statement's flag
  }
  if (current - prev1 >= 2 && flag == 2) { //if current time - previous time is 5ms and flag is 1 (for the first delay)
    prev1 = current;	// set current time to previous time
	display_number = (current_time/10)%10;
  	PORTC = 0b110111;
  	PORTD = sevensegment1[display_number];
  	PORTB = sevensegment0[display_number];
    flag =3; // set second if statement's flag
  } 
  
   if (current - prev1 >= 2 && flag == 3) { //if current time - previous time is 5ms and flag is 1 (for the first delay)
    prev1 = current;	// set current time to previous time
  	display_number = (current_time/100)%10;
  	PORTC = 0b101111;
  	PORTD = sevensegment1[display_number];
  	PORTB = sevensegment0[display_number];
    flag =4; // set second if statement's flag
  } 
  
    if (current - prev1 >= 2 && flag == 4) { //if current time - previous time is 5ms and flag is 1 (for the first delay)
    prev1 = current;	// set current time to previous time
  	display_number = (current_time/1000)%10;
  	PORTC = 0b011111;
  	PORTD = sevensegment1[display_number];
  	PORTB = sevensegment0[display_number];
    flag =1; // set second if statement's flag
  } 
  
}

