//random seed array with 10 size
int seed[10] = {2, 4, 6, 1, 3, 7, 8, 0, 5, 9};

int k = 2; //k value is given as 2
int j = 1; //0<j<k
int m = 16; //random number interval

// 7 segment number binary codes for PORTB
byte sevensegment0[16] = { 
  0b01111,
  0b00001,
  0b10110, 
  0b10011,
  0b11001,
  0b11011,
  0b11111,
  0b00001,
  0b11111,
  0b11011,
  0b11101,
  0b11111,
  0b01110,
  0b10111,
  0b11110,
  0b11100,
};
// 7 segment number binary codes for PORTD
byte sevensegment1[16] = {
  0b11,
  0b10,
  0b11,
  0b11,
  0b10,
  0b01,
  0b01,
  0b11,
  0b11,
  0b11,
  0b11,
  0b00,
  0b01,
  0b10,
  0b01,
  0b01,
};

//random generator function initialized
void generate();
  
void setup()
{
    DDRD = 0b11110111; //3rd pin set as input, others are output
  	DDRB = 0b111111; //all pins are set as output
    //initialize display with 0
  	PORTD = sevensegment1[0] << 6; 
    PORTB = sevensegment0[0];
    //attach rising interrupt to 3rd pin of PortD
  	attachInterrupt(digitalPinToInterrupt(3), generate, RISING);
}

void loop()
{
	// void loop must stay empty
}

//random number generator (interrupt function)
void generate()
{   
    //gets jth and kth elements of array and takes modulo with 16
    //generates number between 0-m
    int random = (seed[j - 1] + seed[k - 1]) % m;
    //shifts all elements of array to left
  	for(int i = 0; i < 9; i++)
  	{
      seed[i] = seed[i + 1];
    }
    //places our random number as last element of array
  	seed[9] = random;
    //displays random value in seven segment display
 	  PORTD = sevensegment1[random] << 6;
    PORTB = sevensegment0[random];
}


