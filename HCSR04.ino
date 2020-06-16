const int trigPin = 9;
const int echoPin = 10;

float duration;
float distance;

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  
}


void loop() {
// Clear the trig pin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


// Send out a soundwave for 10 microseconds, then turn back off 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Read the duration of the soundwave
duration = pulseIn(echoPin, HIGH);


// Convert time to distance, and display on monitor
distance = duration * 0.034/2;

Serial.println(distance);



  
}
