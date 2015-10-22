//this class is the Motor Class + the Encoder Library
#include "../Encoder/Encoder.h"
#include "Motor.h"

class Wheel: public Motor
{
    private:
        Encoder qEncoder;
        boolean forwardLoop;
        boolean backwardLoop;
        long destination;
               
    public:
        Wheel(byte chA, byte chB, byte PWM, int encodA, int encodB);
        //returns current value of encoder
        long getPosition();

        //resets value of encoder to zero
        void reset();
        
        //moves the wheel forward a distance at PWM speed
        boolean moveForward(int distance, byte speed=70);
        
        //moves the wheel opposite direction a distance at PWM speed
        boolean moveBackward(int distance, byte speed=70);  
};

