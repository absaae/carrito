#include <AFMotor.h>

AF_DCMotor motorA(1);
AF_DCMotor motorB(2);

void setup() 
{
  motorA.setSpeed(250);
  motorB.setSpeed(250);
}

void loop() 
{
  motorA.run(FORWARD);
  motorB.run(FORWARD);
  delay(5000);

  motorA.run(FORWARD);
  motorB.run(BACKWARD);
  delay(1000);

  motorA.run(BACKWARD);
  motorB.run(BACKWARD);
  delay(5000);

  motorA.run(BACKWARD);
  motorB.run(FORWARD);
  delay(1000);
  
  motorA.run(RELEASE);
  motorB.run(RELEASE);
  delay(5000);
}