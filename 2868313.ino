//char arrays to be displayed
char names[16] = {'b','u','r','a','k',' ','b','a','s','a','r',' ','o','b','e','n'};
char surnames[16] = {'s','e','n',' ','d','e','m','i','r',' ','o','z','g','u','r', ' '};

//function to write on LCD
void sendChar(byte letter, int index){
  sendCMD((index | 0b10000000)); //set the index at corresponding location
  PORTD = ((letter & 0b11110000)) | 0b00000100; //upper part of the letter and write command
  triggerEnable();
  PORTD = ((letter & 0b00001111)<< 4) | 0b00000100; //lower part of the letter and write command
  triggerEnable();
  waitMicros(55); //wait
}

//function to send command
void sendCMD(byte cmd){
  PORTD = ((cmd & 0b11110000)); //send upper part of the command
  triggerEnable();
  PORTD = ((cmd & 0b00001111)<< 4); //send lower part of the command
  triggerEnable();
  waitMicros(55); // wait
}

void triggerEnable()
{
	PORTB = 0b000001;
  	PORTB = 0b000000;
}

void waitMicros(int time)
{
  long start_time = micros();
  while(micros() - start_time >= time);
}

void waitMillis(int time)
{
  long start_time = millis();
  while(millis() - start_time >= time);
}

void initLCD(){

  PORTD = PORTD & B11110011;
  waitMillis(100);

  PORTD = (PORTD & B00001111) | B00110000;
  triggerEnable();
  waitMillis(5);

  PORTD = (PORTD & B00001111) | B00110000;
  triggerEnable();
  waitMicros(150);

  PORTD = (PORTD & B00001111) | B00110000;
  triggerEnable();
  waitMicros(150);

  PORTD = (PORTD & B00001111) | B00100000;
  triggerEnable();
  waitMicros(150);

  PORTD = (PORTD & B00001111)|B00100000;
  triggerEnable();
  PORTD = (PORTD & B00001111)|B10000000;

  triggerEnable();
  waitMicros(55);

  PORTD = (PORTD & B00001111);
  triggerEnable();
  PORTD = (PORTD & B00001111)|B10000000;
  triggerEnable();
  waitMicros(55);

  PORTD = (PORTD & B00001111);
  triggerEnable();
  PORTD = (PORTD & B00001111)|B00100000;
  triggerEnable();
  waitMillis(5);


  PORTD = (PORTD & B00001111);
  triggerEnable();
  PORTD = (PORTD & B00001111)|B01100000;
  triggerEnable();
  waitMicros(55);

  PORTD = (PORTD & B00001111);
  triggerEnable();
  PORTD = (PORTD & B00001111)|B11100000;

  triggerEnable();
  waitMicros(55);
}


void setup() {
  DDRD = 0b11111111; //output
  DDRB = 0b11111111; //output
  initLCD(); //start lcd
}

int counter =0;
int flag =0;
int isFinished =0;
void loop() {
  if(!isFinished){                         
    if(flag ==0 ){ //go until names are written
      sendChar(names[counter], counter); //send names to write
      counter++; 
      if(counter ==16){ //when name writing is done
        flag =1; //set flag to 1
        counter =0; //decrease counter
      } 
  	}
    if(flag ==1 ){
      sendChar(surnames[counter], counter+64); //send surnames
      //64 is going to line below
      counter++;
      if(counter ==16){ //when surname writing is done
        flag =0;
        counter =0;
        isFinished=1; //set finished flag to one
      } 
  	}
  }
}