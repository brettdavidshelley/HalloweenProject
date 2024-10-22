//Author: Brett Shelley
//Last Edited: 9/12/2024
//Modified from arduino PING sensor demo code

const int trigPin = 2; //sends signal
const int echoPin = 4; //reads signal delay (aka echo)
int LED1 = 6;
int LED2 = 7;
int LED3 = 8;
int LED4 = 9;
int LED5 = 10;
int LED6 = 11;
int soundSignalPin = 12;
int audioSignalPin = A0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(soundSignalPin, OUTPUT);
  pinMode(audioSignalPin, INPUT); //we could consider pull up if the signal was too weak, it should be able to handle 3.3v pico pi inputs though (cut off is 2.5 ish)
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches;

  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // The same pin is used to read the signal from the PING: a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);

  //This section controls the LEDs to demo the lidar
  if (inches < 24) {
    digitalWrite(soundSignalPin, HIGH); //currently have a step down voltage of around 3v going to pico
    delay(250); //delay should be long enough for pico to process signal, it finishes the sound even when low
    digitalWrite(soundSignalPin, LOW);
    while (digitalRead(audioSignalPin))
    {
      reaction();
    }
  }
}

void reaction() {
    digitalWrite(LED6, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED6, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, LOW);
    delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING, there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}
