int flexs[4] = {A0,A1,A2,A3}; //set pins

void setup()
{
  Serial.begin(9600); //for using serial monitor
  pinMode(flexs[0], INPUT);
  pinMode(flexs[1], INPUT);
  pinMode(flexs[2], INPUT);
  pinMode(flexs[3], INPUT);
}

//function for delaying
void waitMillis(int time)
{
  long start_time = millis();
  while(millis() - start_time >= time);
}

 
void loop()
{
  for(int i=0; i<4;i++){ 										//loop through pins
  	double data = analogRead(flexs[i]);							//read pins analog value
    double readVoltage = (data/1023.0)*5.0;						//convert it to voltage
    double current = (5.0 - readVoltage)/100.0;					//calculate current
    double resistance = readVoltage/current;					//calculate flex resistance
    double angle = abs(((resistance-29.99)/132.99)*180.0);		//calculate angle assuming its linear
    Serial.print('!');											//print accordingly
    Serial.print(i);
    Serial.print(';');
    Serial.print(data);
    Serial.print(';');
    Serial.print(resistance);
    Serial.print(';');
    Serial.print(angle);
    Serial.println('#');
  }
  waitMillis(200);
}
