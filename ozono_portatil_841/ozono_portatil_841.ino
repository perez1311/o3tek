#define speaker 10
#define fanRelay 6
#define ozoneRelay 5
#define outputLed 1
#define pitch 4000


//-----------------------------USER VARIABLES-----------------------------
unsigned long workingTime = 2;    //time the generator is on in minutes
unsigned long loadTime = 10;      //time before it starts in seconds
//-----------------------------USER VARIABLES-----------------------------

//SYSTEM VARIABLES
unsigned long startTime;


void setup() {
  Serial.begin(115200);

  //CONVERSIONS
  workingTime = workingTime * 60000;
  loadTime = loadTime * 1000;

  //PIN DEFINITIONS
  pinMode(fanRelay, OUTPUT);
  pinMode(ozoneRelay, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(outputLed, OUTPUT);

  digitalWrite(fanRelay, HIGH);
  digitalWrite(ozoneRelay, HIGH);
  digitalWrite(speaker, LOW);
  digitalWrite(outputLed, LOW);

  for (int i = 0; i < (loadTime / 1000); i++) {
    Serial.print("starting ");
    Serial.println(i);
    digitalWrite(outputLed, HIGH);
    digitalWrite(speaker, HIGH);
    delay(loadTime * 0.02);
    digitalWrite(outputLed, LOW);
    digitalWrite(speaker, LOW);
    delay(loadTime * 0.08);
  }
}

void loop() {
  startTime = millis();
  Serial.println(startTime);
  digitalWrite(fanRelay, LOW);
  digitalWrite(ozoneRelay, LOW);
  digitalWrite(outputLed, HIGH);

  while (millis() - startTime < workingTime) {
    Serial.println(millis() - startTime);
  }

  Serial.println("END OF CYCLE, FAN WILL STAY ON");

  digitalWrite(fanRelay, LOW);
  digitalWrite(ozoneRelay, HIGH);
  digitalWrite(outputLed, LOW);

  while (millis() - startTime > workingTime) {
    digitalWrite(speaker, HIGH);
    delay(1000);
    digitalWrite(speaker, LOW);
    delay(1000);
  }
}
