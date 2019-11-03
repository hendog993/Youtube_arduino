/*    Henry Gilbert
 *    Arudino Space Invaders
 *    Date: 11/2/2019
 *    
 * 
 *    Description: 
 * 
 * 
 * 
 * 
 */


// LED matrix definitions
const int R1 = 38 ;
const int R2 = 40 ;
const int R3 = 42 ;
const int R4 = 44 ;
const int R5 = 46 ;
const int R6 = 48 ;
const int R7 = 50 ;
const int R8 = 52 ;
const int C1 = 39 ;
const int C2 = 41 ;
const int C3 = 43 ;
const int C4 = 45 ;
const int C5 = 47 ;
const int C6 = 49 ;
const int C7 = 51 ;
const int C8 = 53 ;


int led_rows[8] = {R1, R2, R3, R4, R5, R6, R7, R8};
int led_cols[8] = {C1, C2, C3, C4, C5, C6, C7, C8}; 


void setup() {
  pinMode(R1, OUTPUT);  pinMode(C1, OUTPUT);
  pinMode(R2, OUTPUT);  pinMode(C2, OUTPUT);
  pinMode(R3, OUTPUT);  pinMode(C3, OUTPUT);
  pinMode(R4, OUTPUT);  pinMode(C4, OUTPUT);
  pinMode(R5, OUTPUT);  pinMode(C5, OUTPUT);
  pinMode(R6, OUTPUT);  pinMode(C6, OUTPUT);
  pinMode(R7, OUTPUT);  pinMode(C7, OUTPUT);
  pinMode(R8, OUTPUT);  pinMode(C8, OUTPUT);   
}


// Clears all LEDs to allow for calculation reset
void clear_leds() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
  digitalWrite(R5, LOW);
  digitalWrite(R6, LOW);
  digitalWrite(R7, LOW);
  digitalWrite(R8, LOW);
  delay(500);
}

void diagonal_pattern() {
  for (int i = 0; i<8; i++) {
  digitalWrite(led_rows[i], HIGH);
  digitalWrite(C2, HIGH);
  digitalWrite(C3, HIGH);
  digitalWrite(C4, HIGH);
  digitalWrite(C5, HIGH);
  digitalWrite(C6, HIGH);
  digitalWrite(C7, HIGH);
  digitalWrite(C8, HIGH);  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  diagonal_pattern();
  delay(200);
  clear_leds();

}
