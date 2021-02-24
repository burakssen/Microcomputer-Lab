void setup()
{
	DDRD = B11111111;
}

void loop()
{
  PORTD = 0;
  delay(1000);
  PORTD = 'B';
  delay(1000);
  PORTD = 'O';
  delay(1000);
  PORTD = 'B';
  delay(1000);
}