

// Include the servo library and create a Servo object (for steering)
 #include <Servo.h>
 Servo myservo;

// Program options
#define MEASURE_TIMING 0    // Measure and display pulse timing
#define SWEEP_STEERING 0    // Sweep the stearing back and forth
#define DRIVE_FORWARD  0    // Drive forward at a given speed
#define DRIVE_BACKWARD 0    // Drive backward at a given speed
#define DRIVE_FWD_BWD  1    // Drive forward then backward

// Pin assignments
int led = 13;         // LED on Teensy 3.0
int btn = 17;         // Button to control start and stop of drive program
int outSignal = 7;   // Output signal to control ESC (electronic speed controller)
int inSignal = 7;    // Input signal from the remote receiver that controls ESC (learn signal pattern)
int steering = 4;    // Output PWM signal to control steering
int rpmsensor = 5;

// Variables to control signal timing
unsigned long refTime = 0;  // Starting reference time for the rising or falling edge of signal
unsigned int initTime = 0;  // Initial system time reference to create delay before starting program (reverse requires a delay before starting
unsigned int nLow = 8435;   // Duration of low outSignal for neutral signal
unsigned int nHigh = 1494;  // Duration of high outSignal for neutral signal
unsigned int aLow,aHigh;    // Low and high durations to control ESC (multiple of nLow and nHigh)
bool highState = false;     // Current state of signal (low or high)
unsigned long startDelay = 3000000; // Length of time (microseconds) to wait before string the program (needed for reverse signal)

// Variables to control steering
int wheelPos = 175;           // Wheel position as determined by servo postion (between 0 and 180)
bool wpForward = true;      // Current direction of sweep
unsigned int wpRefTime = 0; // Wheep position reference time
unsigned wpDelay = 10000;      // Number of micro seconds to wait between adjustments

// Variables for a generic wait timer
int waitRefTime = 0;        // Reference timer for a generic wait timer
int systemMode = 0;

int counter=0;

// the setup routine runs once when you press reset:
void setup() {                
  // Set output pins
  pinMode(led, OUTPUT);     
  pinMode(outSignal,OUTPUT);
  pinMode(rpmsensor, INPUT_PULLUP); 
  pinMode(13, OUTPUT);  
  pinMode(15, INPUT);

  // Set the pin to control the servo
  myservo.attach(14);

  // Set the default pulse timings
  aLow = nLow;
  aHigh = nHigh;

  // Start serial communication
  Serial.begin(38400);
}

// Measure pulse timings from receiver
void MeasurePulseTiming() {
  Serial.print(pulseIn(outSignal,HIGH));
  Serial.print(",");
  Serial.println(pulseIn(outSignal,LOW));  
}

// Sweep steering back and forth


// Drive forward at speed given (percentage of full power) after driveDelay micro seconds
void DriveForward(int speed, int driveDelay) {


  if (refTime == 0) refTime = micros();
  if (initTime == 0) initTime = micros();
  if (micros() - initTime > driveDelay) {
    aLow = (1-speed/100.0) * nLow;
    aHigh = (1+speed/100.0) * nHigh;
  }
  
  if (!highState) {
    if (micros() - refTime > aLow) {
      //Serial.print(micros() - refTime);
      //Serial.print(",");
      refTime = micros();
      highState = !highState;
      digitalWrite(outSignal,HIGH);
      Serial.println(1);
    }
  }
  else {
    if (micros() - refTime > aHigh) {
      //Serial.println(micros() - refTime);
      refTime = micros();
      highState = !highState;
      digitalWrite(outSignal,LOW);
      Serial.println(0);
    }
  }  
  
}

// Drive forward at speed given (percentage of full power) after driveDelay micro seconds
void DriveBackward(int speed, int driveDelay) {
  DriveForward(-speed,driveDelay);
}

// the loop routine runs over and over again forever:
void loop() {
digitalWrite (13, HIGH);
  if (counter >= 20) {
//    Serial.println(digitalRead(rpmsensor));
    counter = 0;
  }
  counter++;

  if (DRIVE_FWD_BWD) {
    if (waitRefTime == 0) waitRefTime = micros();
    if (micros() - waitRefTime > 1000000) {
      systemMode++;
      waitRefTime = micros();
    }
    switch (systemMode) {
      case 0: DriveForward(0,0); break; //Neutral for 3 seconds
      case 1: myservo.write(0); break;
      case 2: DriveBackward(7,0); break; //Drive forwards for 3 seconds
      //case 3: DriveForward(0,0); break; //Neutral for 3
      case 3: DriveBackward(7,0); break; // Drive forwards for 3 seconds
      //case 4: DriveForward(0,0); break;
      case 4: DriveBackward(7,0); break;
      //case 5: DriveForward(0,0); break;
      case 5: DriveBackward(7,0); break;
      //case 7: DriveForward(0,0); break;
      //case 6: DriveBackward(7,0); break;
      //case 8: DriveForward(0,0); break;
      //case 7:DriveBackward(7,0); break;
      //case 8: DriveBackward(7,0); break;
      case 6: DriveForward(0,0); break;
      case 7: myservo.write(180); break;
      case 8: DriveBackward(7,0); break; //Drive forwards for 3 seconds
      //case 3: DriveForward(0,0); break; //Neutral for 3
      case 9: DriveBackward(7,0); break; // Drive forwards for 3 seconds
      //case 10: DriveForward(0,0); break;
      case 10: DriveBackward(8,0); break;
      //case 5: DriveForward(0,0); break;
      case 11: DriveBackward(8,0); break;
      //case 7: DriveForward(0,0); break;
      //case 15: DriveBackward(7,0); break;
      //case 8: DriveForward(0,0); break;
      //case 16:DriveBackward(7,0); break;
      //case 17: DriveBackward(7,0); break;
      case 12: DriveForward(0,0); break;
      case 13: myservo.write(0); break;
      case 14: myservo.write(180); break;
      case 15: myservo.write(0); break;
      case 16: myservo.write(180); break;
      case 17: myservo.write(90); break;
      
      
    }
  }
}
