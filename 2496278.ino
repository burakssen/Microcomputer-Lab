byte data = B00000000;

void setup()
{
  DDRD = B11111111;
}

void loop()
{
  data = data + B00000001;
  delay(1000);
  PORTD = data;
}