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
#define MAX_DISTANCE 200
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

// Actual bot code

void botMe(){
  
  // Input from A  
   unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
   int wide = (uS / US_ROUNDTRIP_CM); // Convert to cm, returns a number between 1 and MAX_DISTANCE
   wide = map(wide, 0, MAX_DISTANCE, MAX_DISTANCE, 0);
   
  // Input from B
   int narrow = analogRead(sensorPin); // returns a number between 0 and 300 

  // Combine inputs
   int fear = (narrow * 4) + (wide * .5);
   fear < 80 && (fear = 0);
   fear = map(fear, 0, 800 + MAX_DISTANCE, 0, 255); // some integer between 0 and 255, fed by the sesnsors

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
