int pot = A0; //potentiometer pin

byte sevensegment[10] = { // 7 segment number binary codes
  0b0000001,    //0
  0b1001111,    //1
  0b0010010,    //2
  0b0000110,    //3
  0b1001100,    //4
  0b0100100,    //5
  0b0100000,    //6
  0b0001111,    //7
  0b0000000,    //8
  0b0001100     //9
};


void setup()
{
  	DDRD = 0b11111111;  //we set ddrd to output
  	DDRB = 0b1; // we set ddrb to input
  	pinMode(pot, INPUT);    
  	// we set potantiometer's analog pin as an input 
  	PORTB = 0b000000000; //we se activate transistor
}

void loop()
{
  	int value = analogRead(pot);    
  	//we take the value from potentiometer
  	value = value % 10; 
  	// we find the least significant digit
	PORTD = sevensegment[value];    
	//we pass the value to 7 segment display
	//according to modified value 
	//(we use this value as an index for the array)
}