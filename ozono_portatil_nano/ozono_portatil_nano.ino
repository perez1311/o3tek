#define speaker 12
#define fanRelay 2
#define ozoneRelay 3
#define outputLed 13

unsigned long workingTime = 300;    //time the generator is on in seconds
unsigned long loadTime = 10;      //time before it starts in seconds

unsigned long startTime;

void setup() {
  workingTime = workingTime * 1000;
  loadTime = loadTime * 1000;
  Serial.begin(9600);
  pinMode(fanRelay, OUTPUT);
  pinMode(ozoneRelay, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(outputLed, OUTPUT);
  
  for (int i = 0; i < (loadTime/1000); i++){
    Serial.println("here");
    digitalWrite(outputLed, HIGH);
    digitalWrite(speaker, HIGH);
    delay(loadTime*0.02);
    digitalWrite(outputLed, LOW);
    digitalWrite(speaker, LOW);
    delay(loadTime*0.08);  
  }
}

void loop() {
  Serial.println("start");
  startTime = millis(); 
  Serial.print("Start ");
  Serial.println(startTime);
  digitalWrite(fanRelay, HIGH);
  digitalWrite(ozoneRelay, HIGH);
  digitalWrite(outputLed, HIGH);
  
  while (millis() - startTime < workingTime) {
    Serial.println(millis() - startTime);
  }
  
  digitalWrite(fanRelay, LOW);
  digitalWrite(ozoneRelay, LOW);
  digitalWrite(outputLed, LOW);
  
  while (millis() - startTime > workingTime) {
    digitalWrite(speaker, HIGH);
    delay(1000);
    digitalWrite(speaker, LOW);
    delay(1000);
  }
}
