#include <PID_v1.h>

const int pumpPin = 3;
const int drainValvePin = 7;
int flowPin = A0;
long delayTime = 250;
volatile int count;
bool drainValveOpen = false;

double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,15,10,2, DIRECT);

int closeDrainValve(){
  if(drainValveOpen){
    digitalWrite(drainValvePin, HIGH);
    drainValveOpen = false;
    Serial.print("\nDrain valve closed");
    return 0;
    }
    return 1;
  }

void openDrainValve(){
  if(drainValveOpen == false){
    digitalWrite(drainValvePin, LOW);
    drainValveOpen = true;
    Serial.print("\nDrain valve opened");
    return 0;
    }
    return 1;
  }

void setup() {
  // put your setup code here, to run once:
  pinMode(pumpPin, OUTPUT);
  pinMode(flowPin, INPUT);
  pinMode(drainValvePin, OUTPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(0, flow, RISING);
  Output = 10;
  Setpoint = 2.1025;
  myPID.SetMode(AUTOMATIC);
  Serial.begin(9600);
  drainValveOpen = false;

  //fddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddrbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbgo0penDrainValve();
  //delay(5000);
  //closeDrainValve();
  //delay(5000);
}

void loop() {
  
  
  // put your main code here, to run repeatedly:
  /*digitalWrite(transistorPin, HIGH);
  digitalWrite(13, HIGH);
  delay(delayTime);
  digitalWrite(transistorPin, LOW);
  digitalWrite(13, LOW);
  delay(delayTime);
  */

  count = 0;
  interrupts();
  delay(delayTime);
  noInterrupts();
  int flowValue;
  //digitalWrite(pumpPin, HIGH);
  analogWrite(pumpPin, Output);
  Serial.print("\nOutput: ");
  Serial.print(Output   );
  digitalWrite(13, HIGH);
 // delay(delayTime);
  //flowValue = analogRead(flowPin);
  //flowValue = flowValue / 7.5;
  double pulses = count / 7.5 * (1000 / delayTime);
  int freq = 1/ pulses;
  Serial.print(", Flowrate: ");
  Serial.print(pulses);
  Input = pulses;
  myPID.Compute();
  //flowValue = count * 2.25;
  Serial.print(pulses);
  //digitalWrite(pumpPin,LOW);
  //analogWrite(pumpPin, 50);
  //digitalWrite(13, LOW);
 // delay(delayTime);
  //flowValue = analogRead(flowPin);
  //Serial.println(flowValue);
  //delay(250);
  
  /*openDrainValve();
  delay(5000);
  closeDrainValve();
  delay(5000);*/
}

void flow(){
  count++;
  }
