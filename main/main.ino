#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace 
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;

  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

void setup()
{
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
  code_setup();
}

void code_setup()
 {
   
 }

void loop()
{ 
  for (int turn_time=100; turn_time <= 1500; turn_time = turn_time + 100){
    for(int x=0; x<4;x++){
      left_motor.reverse(speed);
      right_motor.forward(speed);
      delay(turn_time);

      // Stop the robots motors
      left_motor.stop();
      right_motor.stop();
      delay(200); 
    }
    delay(5000);
    
  }
    

  exit(0);

  
}

void test1()
{
  // Move robot forwards for one second
  left_motor.forward(speed);
  right_motor.forward(speed);

  delay(1000);

  left_motor.forward(0.25*speed);
  right_motor.forward(0.25*speed);

  delay(1000);

  left_motor.forward(1.25*speed);
  right_motor.forward(1.25*speed);

  delay(500);

  // Turn right
  left_motor.forward(speed);
  right_motor.reverse(speed);

  delay(1000);

  // Turn left
  left_motor.reverse(speed);
  right_motor.forward(speed);

  delay(5000);

  // Move robot backwards for one second
  left_motor.reverse(speed);
  right_motor.reverse(speed);

  delay(1000);

  // Move robot forwards for one second
  left_motor.forward(speed);
  right_motor.forward(speed);

  delay(1000);

  // Stop the robots motors
  left_motor.stop();
  right_motor.stop();
}

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
