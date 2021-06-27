float V_ADC;
float R_PSR;
float currentVal = 0.0;
long elapsedTime;
long sampleTotal;
long numSamples;
int cycleTime = 50; // in ms
float runningAverage[51];
float runningAverageSum = 0.0;

void setup(){
  Serial.begin(250000);
  //LED
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  digitalWrite(A0, HIGH);
  //analog circuit
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT_PULLUP);
  pinMode(13,OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A4, LOW);
  digitalWrite(A2, LOW);
  
}
void loop(){
  // get resistance
  elapsedTime = micros();
  while(micros() - elapsedTime < 50000){
    V_ADC += analogRead(A3) * 0.004887585532746823069403714565;
    numSamples++;
  }
  V_ADC /= numSamples;
  numSamples = 0;
  R_PSR = (37600.0 * V_ADC)/(4.92-V_ADC);
  // done getting resistance
  for(int i = 0; i < 50; i++){
    runningAverage[i] = runningAverage[i+1];
  }
  
  runningAverage[50] = R_PSR;
  
  for(int i = 0; i < 51; i++){
    runningAverageSum += runningAverage[i];
  }

  runningAverageSum /= 52.0;
  currentVal = runningAverage[50] - runningAverageSum;
  analogWrite(A5, int(map(currentVal, -3000.0, 3000.0, 0.0, 255.0)));
  //Serial.print(runningAverageSum);Serial.print(",");
  Serial.println(currentVal);
  
}
