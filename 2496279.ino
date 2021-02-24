void setup()
{
  DDRD = B11111111;
  PORTD = B00000001;
}

void loop()
{
  for(int i = 0; i < 7; i++)
  {
    delay(500);
    PORTD <<= 1;
  }
  for(int i = 0; i < 7; i++)
  {
    delay(500);
    PORTD >>= 1;
  }
}