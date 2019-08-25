// Pin numbers
const int led1 = 2;
const int led2 = 3;
const int led4 = 4;
const int led8 = 5;
const int led16 = 6;
const int led32 = 7;
const int led64 = 8;
const int led128 = 9;

// Rotary encoder
const int inRot1 = 10;
const int inRot2 = 11;

// Variables 
int counter = 0;
int aState, aLastState;

void decimal_to_binary(int input) {
// Construct a binary array and update its contents with the result of loop.
int bin_array[8] = {0,0,0,0,0,0,0,0};
// Set up a for loop to iterate input
for (int i = 0; input > 0; i++) {
     bin_array[i] = input%2 ; // stores the answer backwards
     input = input/2;
}
// Write LED based on array
digitalWrite(led1, bin_array[0]); 
digitalWrite(led2, bin_array[1]); 
digitalWrite(led4, bin_array[2]); 
digitalWrite(led8, bin_array[3]); 
digitalWrite(led16, bin_array[4]); 
digitalWrite(led32, bin_array[5]); 
digitalWrite(led64, bin_array[6]); 
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
  pinMode(inRot1, INPUT);
  pinMode(inRot2, INPUT);
  Serial.begin(9600);
  
  
}

void loop() {
// generate integer from knob, 
int state1 = digitalRead(inRot1);
int state2 = digitalRead(inRot2);


// if state 1 changes, increment counter. 
// the knob changes if state1 does not equal laststate
if (state1!= aLastState) {
  // Clockwise 
   if (state2 != state1) {
    counter ++;
    if (counter > 255) counter = 0;
   }
   else counter--;
    if (counter < 0) counter = 255;
  // Decrement is ccw 
}
decimal_to_binary(counter);

Serial.println(counter);
aLastState = state1;
}











