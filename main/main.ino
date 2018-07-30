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

//int move_time = 1000;

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
 one_eighty();
 Serial.println("turn_left");
 turn_left_test();
 Serial.println("test complete!");

  Serial.println("exit run");
  exit(0);
  

}

void one_eighty()
{
  int time_unit = 1000;
  for (int x = 0; x < 3; x++) {
    timed_forwards(time_unit);
    turn_left_90();
    Serial.println("loop complete");
  }
  timed_forwards(time_unit * 2);
  Serial.println("long forwards complete");
  for (int x = 0; x < 3; x++) {
    turn_right_90();
    timed_forwards(time_unit);
    Serial.println("loop2 complete");
  }
}
void turn_left_90()
{
  left_motor.reverse(200);
  right_motor.forward(200);
  delay(730);
  left_motor.stop();
  right_motor.stop();
}

void turn_right_90()
{
  left_motor.forward(200);
  right_motor.reverse(200);
  delay(800);
  left_motor.stop();
  right_motor.stop();
}

void timed_forwards(int move_time)
{
  // Move robot forwards for one second
  left_motor.forward(speed);
  right_motor.forward(speed);

  delay(move_time);
  Serial.println(move_time);

  left_motor.stop();
  right_motor.stop();
}
 
void turn_left_test()
{
  Serial.println("message from function");
  for (int turn_time = 100; turn_time <= 800; turn_time = turn_time + 100) {
    for (int x = 0; x < 4; x++) {
      Serial.println("motors on");
      left_motor.reverse(speed);
      right_motor.forward(speed);
      delay(turn_time);

      // Stop the robots motors
      left_motor.stop();
      right_motor.stop();
      Serial.println("motors stop");
      delay(200);
    }
    delay(5000);

  }


  exit(0);


}

void turn_right_test()
{
  for (int turn_time = 100; turn_time <= 800; turn_time = turn_time + 100) {
    for (int x = 0; x < 4; x++) {
      right_motor.reverse(speed);
      left_motor.forward(speed);
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

void robot_movement_test()
{
  // Move robot forwards for one second
  left_motor.forward(speed);
  right_motor.forward(speed);

  delay(1000);

  left_motor.forward(0.25 * speed);
  right_motor.forward(0.25 * speed);

  delay(1000);

  left_motor.forward(1.25 * speed);
  right_motor.forward(1.25 * speed);

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
