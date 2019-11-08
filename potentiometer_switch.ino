const int led1 = 5;
const int led2 = 6;
const int led3 = 7;
const int led4 = 8;
const int potin = A0;
// Potentiometer values: 0-260-520-780

void setup() 
{
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(potin, INPUT);
    Serial.begin(9600);
}

void clear_leds() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW); 
}

void loop() 
{
  int val = analogRead(potin);
  Serial.println(val);
if (val < 260) {
  clear_leds();
  digitalWrite(led1, HIGH);
}
else if (val < 520) {
  clear_leds();
  digitalWrite(led2, HIGH);
}
else if (val < 780) {
  clear_leds();
  digitalWrite(led3, HIGH);
}
else if (val < 1023) {
  clear_leds();
  digitalWrite(led4, HIGH);
}
  
}
