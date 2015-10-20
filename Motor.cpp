//This class contains only the raw motor commands
#include "Arduino.h"
#include "Motor.h"

Motor::Motor(byte A, byte B, byte PWM)
: channelA(A), channelB(B), PWM(PWM)
{
    pinMode(channelA, OUTPUT);
    pinMode(channelB, OUTPUT);
    pinMode(PWM, OUTPUT);
}


void Motor::forward(byte speed)
{
    analogWrite(PWM, speed);
    digitalWrite(channelA, LOW);
    digitalWrite(channelB, HIGH);
}

void Motor::backward(byte speed)
{
    analogWrite(PWM, speed);
    digitalWrite(channelA, HIGH);
    digitalWrite(channelB, LOW);
}

void Motor::stop()
{
    analogWrite(PWM, 0);
    digitalWrite(channelA, LOW);
    digitalWrite(channelB, LOW);
}
