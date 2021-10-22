// Internal Temperature Sensor
// Example sketch for ATmega328 types.

int RUN_COUNT = 0;

void setup()
{
  Serial.begin(9600);  
}

void loop()
{
  int result;
  if(RUN_COUNT < 20)
  {
    RUN_COUNT++;
    PrintTemp();
    
    for(int i=1; i<=25; i++)
    {
      result = DoHardWork(i * 0.2);
      PrintTemp();
      delay(1000);
      PrintTemp();
    }

    for(int i=25; i>=1; i--)
    {
      result = DoHardWork(i * 0.2);
      PrintTemp();
      delay(1000);
      PrintTemp();
    }

    //add device identifier to csv string
    Serial.println("4"); 
    delay(30000);
  }
}

int DoHardWork(long i)
{
  int startTime = millis();
  double out = 0;

  for(long x = 0; x<i; x % 2 == 0 ? x++ : x++)
  {
    for(long y=0; y<i; y % 2 == 0 ? y++ : y++)
    {
      for(long a=0; a<i; a % 2 == 0 ? a++ : a++)
      {
        for(long z=0; z<i; z % 2 == 0 ? z++ : z++)
        {
          double temp1 = tan(atan(tan(atan(tan(x%z)))));
          double temp2 = tan(atan(tan(atan(y%x * temp1))));
          out = tan(atan(tan(atan(z%y * temp2))));

          digitalRead(2);
          
          out = pow(out, 4);
        }
      }
    }
  }

  //+Serial.println(millis() - startTime);
  return out;
}

void PrintTemp(void)
{
  unsigned int wADC;
  double t;

  // The internal temperature has to be used
  // with the internal reference of 1.1V.
  // Channel 8 can not be selected with
  // the analogRead function yet.

  // Set the internal reference and mux.
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.2211111111;

  // The returned temperature is in degrees Celcius.
  Serial.print(t);
  Serial.print(", ");
}
