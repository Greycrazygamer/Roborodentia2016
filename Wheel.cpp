#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(byte chA, byte chB, byte PWM, int encodA, int encodB)
    :Motor(chA, chB, PWM), qEncoder(encodA, encodB)
    {
        forwardLoop = true;
        backwardLoop= true;
    }

long Wheel::getPosition()
{
    return qEncoder.read();
}

void Wheel::reset()
{
    qEncoder.write(0);
}

void Wheel::moveForward(int distance, byte speed)
{
    forward(speed);
    long position = qEncoder.read();
    long destination;
    if(forwardLoop)
    {
        destination = position + distance;
        forwardLoop = false;
    }
     else
    {
        destination = 0;
    }
    
    if(destination > position)
    {
        stop();
        forwardLoop = true;
    }
}

void Wheel::moveBackward(int distance, byte speed)
{
    backward(speed);
    long position = qEncoder.read();
    long destination;
    if(backwardLoop)
    {
        destination = position + distance;
        backwardLoop = false;
    }
    else
    {
        destination = 0;
    }
    
    if(destination < position)
    {
        stop();
        backwardLoop = true;
    }
}



