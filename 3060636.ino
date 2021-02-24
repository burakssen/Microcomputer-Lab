//random seed array with 10 size
int seed[10] = {2, 4, 6, 1, 3, 7, 8, 0, 5, 9};

int k = 2; //k value is given as 2
int j = 1; //0<j<k
int m = 0; //number of random number that will be generated         

int* array; //pointer for generated numbers
int freqArray[8] = {0}; //frequency distribution array

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
	Serial.begin(9600);
	//attach rising interrupt to 3rd pin of PortD
  	attachInterrupt(digitalPinToInterrupt(3), generate, RISING);
	//Print prompt message
  	Serial.print("Please enter a m value:");
}

void loop()
{
	// void loop must stay empty
}


//function that genrates m random numbers between 0-8
void randomNumberGenerator(int m)
{
	//allocates required space for numbers that will be generates
  	array = (int*) malloc(m * sizeof(int));
	
	//iterates m times
  	for(int j = 0; j < m; j++)
  	{	
		//gets jth and kth elements of array and takes modulo with 8
    	int random = (seed[j - 1] + seed[k - 1]) % 8;
		//shifts all elements of array to left
  		for(int i = 0; i < 9; i++)
  		{
      		seed[i] = seed[i + 1];
    	}
		//places our random number as last element of array
  		seed[9] = random;
		//push random number to array
    	array[j] = random;
		//increment count value 
    	freqArray[random]++;
  	}
}


void generate()
{	
	if(Serial.available() > 0){
  		String numstr = ""; //string that will be read from serial input
  		byte num; //char that will be read from serial input
  		int size = 0; //input size variable
		//until read all serial inputs
  		while (Serial.available() > 0) { 
			//reads one char from input
    		num = Serial.read();
			//if it is number
    		if ((num >= '0') && (num <= '9')) {
				//casts to int and add to numstr
    	  		numstr += num - 48;
    		}
    	  	size++; //increment size
  		}
        Serial.println(numstr);
  		int pow = 1; //it keeps powers of 10
		//iterates over the string that is read
  		while(size > 0)
  		{
    	  	m += (numstr[size - 1] - 48)*pow; //adds number to m
    	  	size--; //decrement size
    	  	pow*=10; //multiply pow with 10
  		}
	
		//call random number generator
  		randomNumberGenerator(m);
	
		//it iterates over the freqArray
  		for(int i = 0; i < 8; i++)
  		{
			//it prints frequencies of numbers
    		Serial.print(i);
    		Serial.print(" -> ");
    		Serial.println(freqArray[i]);
			//sets frequency to 0
    		freqArray[i] = 0;
  		}
		//frees space
  		delete [] array;
	}
	Serial.print("Please enter a m value:");
}