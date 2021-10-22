//from https://tomalmy.com/reading-the-chip-temperature/

int RUN_COUNT = 0;

void setup()
{
  Serial.begin(9600);  
  delay(1000);
  Serial.println("starting in 3 sec");
  delay(3000);
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
    Serial.println("1"); 
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
  VREF.CTRLA = VREF_ADC0REFSEL_1V1_gc; // 1.1 volt reference
  ADC0.CTRLC = ADC_SAMPCAP_bm + 3; // VREF reference, correct clock divisor
  ADC0.MUXPOS = ADC_MUXPOS_TEMPSENSE_gc; // Select temperature sensor
  ADC0.CTRLD = 2 * (1 << ADC_INITDLY_gp); // Initial delay of 32us 
  ADC0.SAMPCTRL = 31; // Maximum length sample time (32us is desired) 
  ADC0.COMMAND = 1; // Start the conversion 
  while ((ADC0.INTFLAGS & ADC_RESRDY_bm) == 0) ; // wait for completion 
  // The following code is based on the ATmega4809 data sheet
  int8_t sigrow_offset = SIGROW.TEMPSENSE1; // Read signed value from signature row 
  uint8_t sigrow_gain = SIGROW.TEMPSENSE0; // Read unsigned value from signature row 
  uint16_t adc_reading = ADC0.RES; // ADC conversion result with 1.1 V internal reference 
  uint32_t temp = adc_reading - sigrow_offset; 
  temp *= sigrow_gain; // Result might overflow 16 bit variable (10bit+8bit) 

  //return temp;
  //temp += 0x80; // Add 1/2 to get correct rounding on division below 
  double temperature_in_K = temp / 256.0; // Divide result to get Kelvin

  Serial.print(temperature_in_K - 273);
  Serial.print(", ");
}
