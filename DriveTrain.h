#include "Wheel.h"
#include "../NewPing/NewPing.h"

class DriveTrain
{
    private:
        
        //Four Wheels on a compass orientation with
        //An array of 8 HRS04 sensors, in the following pattern
        /*   0   N   1
         * 7 --------- 2
         *   |  robo |
         * W |  body | E
         *   |  here | 
         * 6 --------- 3
         *   5   S   6
         */
        Wheel northWheel;
        Wheel southWheel;
        Wheel eastWheel;
        Wheel westWheel;
        NewPing HRS04Array[];
    
    public:
        enum CompassRose {NORTH, NEAST, EAST, SEAST, SOUTH, SWEST, WEST, NWEST};
        DriveTrain(byte northA, byte northB, byte nPWM, int nEncodA, int nEncodB,
                   byte southA, byte southB, byte sPWM, int sEncodA, int sEncodB,
                   byte eastA, byte eastB, byte ePWM, int eEncodA, int eEncodB, 
                   byte westA, byte westB, byte wPWM, int wEncodA, int wEncodB,
                   int firstHRS04Pin, int lastHRS04Pin);
        
        // Moves the robot a distance based on encoder feedback
        void moveDistance(CompassRose direction, int distance, int speed);
        
        //Moves the robot until the inputted distance(cm) from selected wall
        //Allowed Directions Are: NORTH, EAST, SOUTH, WEST
        boolean moveTillWall(CompassRose direction, int distance, int speed);
        
        //Moves the robot until the inputted distance(cm) from selected corner, 
        //with equal distance from each side
        //Allowed Directions Are: NEAST, SEAST, NWEST, SWEST
        boolean moveTillCorner(CompassRose direction, int distance, int speed);
        
        //moves the robot alng the N/S axis, with equal distance 
        //between the E/W walls... Only N/S will work for direction
        void moveCenterField(CompassRose direction, int distance, int speed);
        
        //moves the robot back to a 90 degree angle with the walls
        void recenter();
};

