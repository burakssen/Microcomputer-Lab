int potentiometer0 = A0; // potentiometer red
int potentiometer1 = A1; // potentiometer blue
int potentiometer2 = A2; // potentiometer green

void setup() {  
  pinMode(potentiometer0, INPUT);	// assign potentiometer 0 as input
  pinMode(potentiometer1, INPUT);	// assign potentiometer 1 as input
  pinMode(potentiometer2, INPUT);	// assign potentiometer 2 as input
  
  pinMode(3,OUTPUT);	// assign digital pin 3 as output
  pinMode(5,OUTPUT);	// assign digital pin 5 as output
  pinMode(6,OUTPUT);	// assign digital pin 6 as output
}

void loop() {
  
  int po0 = analogRead(potentiometer0);	// read from potentiometer 0
  int po1 = analogRead(potentiometer1);	// read from potentiometer 1
  int po2 = analogRead(potentiometer2);	// read from potentiometer 2
  
  analogWrite(3,(int)(po2/4));	// write po2 value in range 0-255 to digital pin 3 
  analogWrite(5,(int)(po1/4));	// write po1 value in range 0-255 to digital pin 5
  analogWrite(6,(int)(po0/4));	// write po0 value in range 0-255 to digital pin 6
}


