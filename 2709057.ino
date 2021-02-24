int potentiometer = A0; //keeps address of analog 0 in variable

//keeps binary configuration of numbers 
//for seven segment display
byte sevensegment[10] = { 
  0b00000001, //0 
  0b01001111, //1 
  0b00010010, //2 
  0b00000110, //3 
  0b01001100, //4 
  0b00100100, //5 
  0b00100000, //6 
  0b00001111, //7 
  0b00000000, //8 
  0b00001100  //9 
};

void setup()
{
  	DDRD = 0b11111111; //define digital pins 0 to 7 as output
  	DDRB = 0b1111; //define digital pins 8 to 11 as output
  	pinMode(potentiometer, INPUT); //defines analog 0 as input
}

void loop()
{
  	int value = analogRead(potentiometer); 
  	//reads the value of potentiometer	
  	
  	int digit = value % 10; 
  	//takes last digit of number by modulo 10.
  
  	PORTB = 0b1110;//activates most-right display
	PORTD = sevensegment[digit]; 
	// gives required configuration of digit to PORTD  
  	delay(5); //displays in seven segment display for 5ms
  	
  	value = (int)(value / 10); //integer divison with 10
  	digit = value % 10;  
  	//takes second right-most digit of number by modulo 10.
  	
  	PORTB = 0b1101; //activates second most-right display
	PORTD = sevensegment[digit];
	// gives required configuration of digit to PORTD  
  	delay(5); //displays in seven segment display for 5ms 
  
  	value = (int)(value / 10); //integer divison with 10
  	digit = value % 10; 
  	//takes second left-most digit of number by modulo 10.
  	
  	PORTB = 0b1011;//activates second most-left display
	PORTD = sevensegment[digit];
	// gives required configuration of digit to PORTD  
  	delay(5); //displays in seven segment display for 5ms 
  
  	digit = (int)(value / 10);
  	//takes left-most digit of number by dividing with 10

  	PORTB = 0b0111;//activates most-left display
	PORTD = sevensegment[digit]; 
	// gives required configuration of digit to PORTD  
  	delay(5); //displays in seven segment display for 5ms	 
}
