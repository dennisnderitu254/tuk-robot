/*
 * Author: Omambia Dauglous
 * Admin: CIT-227-005/2014
 * Real-Time Programming Assignment
 * The program is to make a moving robot be 
 * able to navigate objects andtake the 
 * right path, it will be able to navigate 
 * to another object if the distance between 
 * it and the object is 10 cm 
 */
 /* --------------------------------------------*/
           /* 
            *  All the imports or Includes  
             */
#include <Servo.h>

            /* 
            * Global accessed Variables  
            */
long minimum_right_distance = 2;
long minimum_left_distance  = 2;
long minimum_front_distance = 2;
double distance_front, distance_right, distance_left;
    /*
     * Ultra sonic Sensor 
     */
// Front Sensor
int echo_front = 6;
int trig_front = 7;

//Right Sensor
int echo_right = 10;
int trig_right = 11;

// Left Sensor
int echo_left = 9;
int trig_left = 8;
    /*
     *Relay Board 
     * Where motors will be connected to 
     * since the Gear Motors Require 12v 
     * that can be given by the Arduino board 
     */
     
int relayRightWheel = 2;
int relayLeftWheel = 3;


    /*
      * The Led indicators
      * 
      */
const int forword_led = 4;
const int stop_led = 5;
     /*
     * Servo Motor 
     * For sterrring on the robot
     * And Creating the Servo Object ..
     */

int sterPin = 12;
Servo sterring;
 /* --------------------------------------------*/
void setup() {
  // put your setup code here, to run once:
  intializer();
}

void loop() {
  // put your main code here, to run repeatedly:
  front_sensor();
  left_sensor();
  right_sensor();
  forward_movement();
  indicators_moving();
  int angle = 90;
  // Forward movement as long as the distance remaining in front is more than 2 cm 
  if((distance_front != minimum_front_distance) && (distance_left <= minimum_left_distance) 
  && (distance_right <= minimum_right_distance) && (distance_front <= minimum_front_distance)){
    sterring.write(angle);
  }
  // turn right 
  if((distance_front == minimum_front_distance) && (distance_left == minimum_left_distance)){
    int right_ster = angle + 45;
    sterring.write(right_ster);
    Serial.println("Am turning Right omambia @");
  }

  // turn left
  if((distance_front <= minimum_front_distance) && (distance_right == minimum_right_distance)){
    int left_ster = angle - 45;
    sterring.write(left_ster);
    Serial.println("Am turning Left omambia");
  }
  // stop the robot if there is no place to navigate to
  if((distance_front == minimum_front_distance && distance_right == minimum_right_distance) && 
   (distance_left == minimum_left_distance)){
    stop_robot();
    indicators_stop();
    Serial.print("Omambia: I am in the Parking.");
  }
  
}
/* 
  *  Helper Functions that help the robot in the 
  *  navigation of the objects
  */
// the Intializer
void intializer(){
  Serial.begin(9600);
  sterring.attach(sterPin);
  // the led intializer
  pinMode(forword_led, OUTPUT);
  // the sensor intializer
  pinMode(echo_left, INPUT);
  pinMode(trig_left, OUTPUT);
  
  pinMode(echo_front, INPUT);
  pinMode(trig_front, OUTPUT);
  
  pinMode(echo_right, INPUT);
  pinMode(trig_right, OUTPUT);
}

// Forward movement of the Robot 
void forward_movement(){
  digitalWrite(relayRightWheel, HIGH);
  digitalWrite(relayLeftWheel, HIGH);
}
// Function to stop the robot after moving
// for 2 minutes 
void stop_robot(){
  digitalWrite(relayRightWheel, LOW);
  digitalWrite(relayLeftWheel, LOW);
}
// The Front Sensor
void front_sensor(){
  digitalWrite(trig_front, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_front, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig_front, LOW);
  // get the time and distance using the echo_front sensor 
  double time_front = pulseIn(echo_front, HIGH);
  distance_front = (time_front * 0.034)/2;
}

// The Left Sensor
void left_sensor(){
  digitalWrite(trig_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_left, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig_left, LOW);
  // get the time and distance using the echo_left sensor 
  double time_left = pulseIn(echo_left, HIGH);
  distance_left = (time_left * 0.034)/2;
}

// The Right Sensor
void right_sensor(){
  digitalWrite(trig_right, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_right, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig_right, LOW);
  // get the time and distance using the echo_right sensor 
  double time_right = pulseIn(echo_right, HIGH);
  distance_right = (time_right * 0.034)/2;
}

// helper functions to show the state of the robot
// Will light green -- to show forward propagation
void indicators_moving(){
  digitalWrite(forword_led, HIGH);
}
// Will light red -- to show  stop
void indicators_stop(){
  digitalWrite(stop_led, HIGH);
}



