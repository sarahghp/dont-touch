//////////////////////////////////////////////////////////////////
//Released under the MIT License - Please reuse change and share
//Includes code examples from bildr (http://bildr.org/)
//////////////////////////////////////////////////////////////////

// Motor constants
#define fadePin 9

// Ultrasonic sensor constants (sensorA)
#include <NewPing.h>
#define TRIGGER_PIN  2 
#define ECHO_PIN     4
#define MAX_DISTANCE 100
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

// IR sensor constants (sensorB)
#define sensorPin 0

// Tests
void motorTest(){
  for(int i = 0; i<360; i++){
  //convert 0-360 angle to radian (needed for sin function)
  float rad = DEG_TO_RAD * i;

  //calculate sin of angle as number between 0 and 255
  int sinOut = constrain((sin(rad) * 128) + 128, 0, 255); 

  analogWrite(fadePin, sinOut);

  delay(5);
  }
}

void sensorATest(){
  delay(500);                      
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}

void sensorBTest(){
  int val = analogRead(sensorPin);
  Serial.println(val);
  delay(200);
}

// Calibrate

void calculateMin(int* minRange, int narrow, int wide){
  *minRange = max(*minRange, max(narrow, wide)); 
}

// Actual bot code

void botMe(){
  
  // Input from A  
   unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
   int wide = (uS / US_ROUNDTRIP_CM); // Convert to cm, returns a number between 1 and MAX_DISTANCE
   wide = map(wide, 0, MAX_DISTANCE, MAX_DISTANCE, 0);
   Serial.print("Wide: ");
   Serial.println(wide);
   wide > 65 && (wide = 0);
   
  // Input from B
   int narrow = analogRead(sensorPin); // returns a number between 0 and 500
   narrow = map(narrow, 1, 630, 1, 80); //  which corresponds to 10 to 80cm
   int multiplier = 3; // how much to weight narrow
   
  // Get calibrations
  int minRange = 1;
  int maxRange = MAX_DISTANCE + (100 * multiplier);
  
  if (millis() % 5000 == 0) 
    calculateMin(&minRange, narrow, wide);
    
   // Combine inputs
   int fear = (multiplier * narrow) + wide;
   Serial.print("Pre-map: ");
   Serial.println(fear);
   fear = map(fear, 0, maxRange, 0, 255); // some integer between 0 and 255, fed by the sesnsors
   fear < 20 && (fear = 0); // reduce whine
   (fear > 20 && fear < 45) && (fear = 45); // reduce whine but add in power
   Serial.print("Post-map: ");
   Serial.println(fear);

  // Send to motor   
   analogWrite(fadePin, fear);
   delay(50);

}


// Run things

void setup(){
  Serial.begin(9600);
  pinMode(fadePin, OUTPUT);  
}

void loop(){
// motorTest();
// sensorATest();
// sensorBTest();
  botMe();
}
