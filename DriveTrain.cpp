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

void DriveTrain:: moveTillWall(CompassRose direction, int distance, int speed)
{
    //NORTH, NEAST, EAST, SEAST, SOUTH, SWEST, WEST, NWEST
    switch(direction)
    {
        case NORTH:
            while(HRS04Array[0].ping_cm() > distance && HRS04Array[1].ping_cm() > distance)
            {
                eastWheel.forward(speed);
                westWheel.backward(speed);
            }
            eastWheel.stop();
            westWheel.stop();
            break;
        
        case EAST:
            while(HRS04Array[2].ping_cm() > distance && HRS04Array[3].ping_cm() > distance)
            {
                northWheel.forward(speed);
                southWheel.backward(speed);
            }
            northWheel.stop();
            southWheel.stop();
            break;
        
        case SOUTH:
            while(HRS04Array[4].ping_cm() > distance && HRS04Array[5].ping_cm() > distance)
            {
                westWheel.forward(speed);
                eastWheel.backward(speed);
            }
            eastWheel.stop();
            westWheel.stop();
            break; 
             
        case WEST:
            while(HRS04Array[6].ping_cm() > distance && HRS04Array[7].ping_cm() > distance)
            {
                southWheel.forward(speed);
                northWheel.backward(speed);
            }
            northWheel.stop();
            southWheel.stop();
            break; 
    }
}

