/*
  US-100 Sensor

  This sketch reads a US-100 ultrasonic rangefinder and returns the distance
  to the closest object in range. To do this, it sends a pulse to the sensor to
  initiate a reading, then listens for a pulse to return. The length of the
  returning pulse is proportional to the distance of the object from the sensor.

  The circuit:
	- Vcc connection of the US-100 attached to +5V
	- GND connection of the US-100 attached to ground
	- Trig/Tx connection of the US-100 attached to digital pin D7
  - Echo/Rx connection of the US-100 attached to digital pin D6

  created 3 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe
  modified 15 Apr 2018
  by Cristian G Guerrero

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Ping
*/



void setup() {
  // initialize serial communication:
  Serial.begin(115200);
 
}

long measureDistance() {
  // these constants won't change. They are the pin numbers of the sensor's outputs:
  const int trigerPin = D7;
  const int echoPin = D6;

  pinMode(trigerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  digitalWrite(trigerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigerPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  
  return pulseIn(echoPin, HIGH);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;

  duration = measureDistance();

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
