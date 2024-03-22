#include <AFMotor.h>  // Include the Adafruit Motor Shield library
#include <SoftwareSerial.h>  // Include the SoftwareSerial library
#include <Servo.h>  // Includes the Servo library

SoftwareSerial mySerial(2, 3); // Define a software serial port on pins 2 (RX) and 3 (TX)
Servo myservo; // Creates a servo object for controlling the servo motor

char command;  // Stores the received command

// Define the motor shield
AF_DCMotor motor1(1, MOTOR12_64KHZ); // Motor 1 is connected to M1
AF_DCMotor motor2(2, MOTOR12_64KHZ); // Motor 2 is connected to M2
AF_DCMotor motor3(3, MOTOR34_8KHZ); // Motor 3 is connected to M3
AF_DCMotor motor4(4, MOTOR34_8KHZ); // Motor 4 is connected to M4

void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);
  myservo.attach(10); // Defines on which pin is the servo motor attached
}

void loop() {
  

  // Motor control routine
  if (mySerial.available() > 0) {
    command = mySerial.read();
    Serial.println("R.C Car Control!");  // Read the command from NodeMCU
    Serial.println(command);  // Read the command from NodeMCU

    // Check the received command and control the motors accordingly
    if (command == 'F') {
      forward();
    } else if (command == 'B') {
      backward();
    } else if (command == 'L') {
      left();
    } else if (command == 'R') {
      right();
    } else if (command == '1') {
      speed1();
    } else if (command == '2') {
      speed2();
    } else if (command == '3') {
      speed3();
    } else if (command == '4') {
      speed4();
    }
  }

  // Servo motor control routine
 for(int i = 15; i <= 165; i++) 
	{
		myservo.write(i);
		delay(30);
	}
  Serial.print("Going Well\n");
	// sweeps from 180 degrees to 0 degrees
	for(int i = 165; i > 15; i--)
	{
		myservo.write(i);
		delay(30);
	}
}

void forward() {
  // Drive the motors to move forward
  motor1.setSpeed(255);  // Set the speed (0-255)
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

void backward() {
  // Drive the motors to move backward
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
}

void left() {
  // Turn left by controlling the motors
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

void right() {
  // Turn right by controlling the motors
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
}

void speed1() {
  // Set the motors to speed level 1
  motor1.setSpeed(0);  // You can adjust the speed level as needed
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

void speed2() {
  // Set the motors to speed level 2
  motor1.setSpeed(128);
  motor2.setSpeed(128);
  motor3.setSpeed(128);
  motor4.setSpeed(128);
}

void speed3() {
  // Set the motors to speed level 3
  motor1.setSpeed(192);
  motor2.setSpeed(192);
  motor3.setSpeed(192);
  motor4.setSpeed(192);
}

void speed4() {
  // Set the motors to speed level 4
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
}