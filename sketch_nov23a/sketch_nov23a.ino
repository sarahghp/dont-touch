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
int sensorPin = 0;

// Test components
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
  delay(500);                      // Wait 500ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}

void sensorBTest(){
  int val = analogRead(sensorPin);
  Serial.println(val);

  //just to slow down the output - remove if trying to catch an object passing by
  delay(200);
}

// Actual bot code

void botMe(){
  
   int narrow = analogRead(sensorPin); // returns a number between

   int fear = (7 * narrow) + (3 * wide)
   fear = map(fear, 0, narrow + wide, 0, 255) // some integer between 0 and 255, fed by the sesnsors
   
   analogWrite(fadePin, fear);
   delay(5);

}


// Run things

void setup(){
  Serial.begin(9600);
  pinMode(fadePin, OUTPUT);  
}

void loop(){
 // motorTest();
 // sensorA();
 // sensorB();
}
