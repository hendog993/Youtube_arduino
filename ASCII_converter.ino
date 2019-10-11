void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void blank_leds() {
  for (int i=3; i<10; i++) {
    digitalWrite(i, LOW);
  }
  delay(5);
}


void decimal_to_binary_write(int decimal_number) {
      int bin_array[7] = {0,0,0,0,0,0,0} ;
      for(int i = 0; decimal_number > 0; i++) {
          bin_array[i] = decimal_number % 2;
          decimal_number = decimal_number/2;
      }
      // Writes the respective LED to 0 or 1, the binary state.
      digitalWrite(3,   bin_array[6]);
      digitalWrite(4,   bin_array[5]);
      digitalWrite(5,   bin_array[4]);
      digitalWrite(6,   bin_array[3]);
      digitalWrite(7,   bin_array[2]);
      digitalWrite(8,   bin_array[1]);
      digitalWrite(9,   bin_array[0]);
}

const char * message = "This is going to a test, how well does these LEDs blink. " ;
void loop() {
 // For every character in the string, print to serial monitor
  for (int i; i<strlen(message); i++) {
    decimal_to_binary_write((int)message[i]);
    blank_leds();
    delay(50);
  }
  delay(1000);

}
