#include "Arduino.h"
#include "DriveTrain.h"

DriveTrain::DriveTrain(byte northA, byte northB, byte nPWM, int nEncodA, int nEncodB,
                   byte southA, byte southB, byte sPWM, int sEncodA, int sEncodB,
                   byte eastA, byte eastB, byte ePWM, int eEncodA, int eEncodB, 
                   byte westA, byte westB, byte wPWM, int wEncodA, int wEncodB,
                   int firstHRS04Pin, int lastHRS04Pin)
        :northWheel(northA,  northB,  nPWM,  nEncodA,  nEncodB),
         southWheel(southA,  southB,  sPWM,  sEncodA,  sEncodB),
         eastWheel(eastA,  eastB,  ePWM,  eEncodA,  eEncodB),
         westWheel(westA,  westB,  wPWM,  wEncodA,  wEncodB)
{
    int j =0;
    HRS04Array[8];
    for(int i=firstHRS04Pin; i<=lastHRS04Pin; i++)
    {
        if(firstHRS04Pin%2==0) //pins start even e.g. 12-27
        {
            if(i%2==0)// if first pin in group of two
            {
                HRS04Array[j]= NewPing(i, i+1);
                j++;
            }
        }
        else //pins start even e.g. 13-28
        {
            if(i%2==1)// if first pin in group of two
            {
                HRS04Array[j]= NewPing(i, i+1);
                j++;
            }
        }
    }
}

void DriveTrain:: moveDistance(CompassRose direction, int distance, int speed)
{
    
}

boolean DriveTrain:: moveTillWall(CompassRose direction, int distance, int speed)
{
    //NORTH, NEAST, EAST, SEAST, SOUTH, SWEST, WEST, NWEST
    switch(direction)
    {
        case NORTH:
            if(HRS04Array[0].ping_cm() > distance && HRS04Array[1].ping_cm() > distance)
            {
                eastWheel.forward(speed);
                westWheel.backward(speed);
                return false;
            }
            else
            {
                eastWheel.stop();
                westWheel.stop();
                return true;
            }
            break;
        
        case EAST:
            if(HRS04Array[2].ping_cm() > distance && HRS04Array[3].ping_cm() > distance)
            {
                northWheel.forward(speed);
                southWheel.backward(speed);
                return false;
            }
            else
            {
                northWheel.stop();
                southWheel.stop();
                return true;
            }
            break;
        
        case SOUTH:
            if(HRS04Array[4].ping_cm() > distance && HRS04Array[5].ping_cm() > distance)
            {
                westWheel.forward(speed);
                eastWheel.backward(speed);
                return false;
            }
            else
            {
                eastWheel.stop();
                westWheel.stop();
                return true;
            }
            break; 
             
        case WEST:
            if(HRS04Array[6].ping_cm() > distance && HRS04Array[7].ping_cm() > distance)
            {
                southWheel.forward(speed);
                northWheel.backward(speed);
                return false;
            }
            else
            {
                northWheel.stop();
                southWheel.stop();
                return true;
            }
            break; 
    }
}

boolean DriveTrain::moveTillCorner(CompassRose direction, int distance, int speed)
{
    //NEAST,SEAST, SWEST, NWEST
    switch(direction)
    {
        case NEAST:
            if(moveTillWall(NORTH, distance, speed))
            {
                return false;
            }
            else
            {
                if(moveTillWall(EAST, distance, speed))
                    return true;
                else
                    return false;
            }
            break;
            
        case NWEST:
            if(moveTillWall(NORTH, distance, speed))
            {
                return false;
            }
            else
            {
                if(moveTillWall(WEST, distance, speed))
                    return true;
                else
                    return false;
            }
            break;
            
         case SEAST:
            if(moveTillWall(SOUTH, distance, speed))
            {
                return false;
            }
            else
            {
                if(moveTillWall(EAST, distance, speed))
                    return true;
                else
                    return false;
            }
            break;
            
        case SWEST:
            if(moveTillWall(SOUTH, distance, speed))
            {
                return false;
            }
            else
            {
                if(moveTillWall(WEST, distance, speed))
                    return true;
                else
                    return false;
            }
            break;
    }
}

boolean DriveTrain::moveCenterField(CompassRose direction, int distance, int speed, byte error)
{
    switch(direction)
    {
        case NORTH:
            // robot is drifting to the left
            if(HRS04Array[2].ping_cm() - HRS04Array[7].ping_cm() > error)
            {
                 northWheel.forward();
                 southWheel.backward();
            }
            //robot is drifting to the right
            else if(HRS04Array[7].ping_cm() - HRS04Array[2].ping_cm() > error)
            {
                northWheel.backward();
                southWheel.forward();
            }
            if(eastWheel.moveForward(distance, speed) || westWheel.moveBackward(distance, speed))
            {
                return true;
            }
            return false;
    }
}


