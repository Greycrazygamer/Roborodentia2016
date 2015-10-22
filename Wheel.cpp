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

boolean Wheel::moveForward(int distance, byte speed)
{
    long position = qEncoder.read();
    destination;
    if(forwardLoop)
    {
        destination = position + distance;
        forwardLoop = false;
    }
         
    if(destination > position)
    {
        stop();
        forwardLoop = true;
        return true;
    }
    forward(speed);
    return false;
}

boolean Wheel::moveBackward(int distance, byte speed)
{
    long position = qEncoder.read();
    if(backwardLoop)
    {
        destination = position + distance;
        backwardLoop = false;
    }
    
    if(destination < position)
    {
        stop();
        backwardLoop = true;
        return true;
    }
    backward(speed);
    return false;
}



