#define outputA 10
#define outputB 11
int counter = 0; 
int aState, aLastState;  
const int   led1 = 9;
const int   led2 = 8;
const int   led4 = 7;
const int   led8 = 6;
const int  led16 = 5;
const int  led32 = 4;
const int  led64 = 3;
const int led128 = 2;

void decimal_to_binary_write(int decimal_number) {
      int bin_array[8] = {0,0,0,0,0,0,0,0} ; 
      for(int i=0; decimal_number > 0; i++) { 
          bin_array[i] = decimal_number % 2;
          decimal_number = decimal_number/2;
      }
      digitalWrite(led1,   bin_array[0]);   // Writes the respective LED to 0 or 1, the binary state. 
      digitalWrite(led2,   bin_array[1]);
      digitalWrite(led4,   bin_array[2]);
      digitalWrite(led8,   bin_array[3]);
      digitalWrite(led16,  bin_array[4]);
      digitalWrite(led32,  bin_array[5]);
      digitalWrite(led64,  bin_array[6]);
      digitalWrite(led128, bin_array[7]);
} 

void setup() {
      pinMode(led1, OUTPUT);
      pinMode(led2, OUTPUT);
      pinMode(led4, OUTPUT);
      pinMode(led8, OUTPUT);
      pinMode(led16, OUTPUT);
      pinMode(led32, OUTPUT);
      pinMode(led64, OUTPUT);
      pinMode(led128, OUTPUT);
      Serial.begin(9600);
      pinMode (outputA,INPUT);
      pinMode (outputB,INPUT);
      aLastState = digitalRead(outputA); 
}

void loop() { 
   aState = digitalRead(outputA); 
      if (aState != aLastState){  // IF the counter HAS moved (is NOT the same state)    
         if (digitalRead(outputB) != aState) { 
            counter ++;
              if (counter > 255) counter = 0;   // Needed to prevent overflow 
       } else counter --;
             if (counter < 0) counter = 255;   // Needed to prevent negative numbers 
   } 
      aLastState = aState; 
      decimal_to_binary_write(counter);
}
