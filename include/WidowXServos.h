#ifndef WIDOWXSERVOS_H
#define WIDOWXSERVOS_H

#include <array>
#include <math.h>

#include "ServoGroup.h"
#include "DynamixelServo.h"

#define ALPHA 0.3272 // sin(5/15)

const std::array<int,6> BASE_POSITIONS = { 2048 , 2048 , 2048 , 2048 , 512 , 256 };
const std::array<double,6> BASE_ANGLES = { M_PI , M_PI_2 + ALPHA , M_PI_2 - ALPHA , 0 , 0 , 0 }; 
const std::array<int,6> LOW_LIMITS = { 0 , 1024 , 1024 , 1024 , 0 , 0 }; 
const std::array<int,6> UP_LIMITS = { 4095 , 3072 , 3072 , 3072 , 1023 , 512 }; 
const std::array<int,6> TOTAL_POS = { 4096 , 4096 , 4096 , -4096 , 1280 , 512 }; 

class WidowXServos : public ServoGroup
{
    public:
        std::array<DynamixelServo*,6> mServos;
        std::array<int,6> mSpeeds;

        WidowXServos();
        ~WidowXServos();
        
        bool validPositions();

        std::array<int,6> getPositions();

    private:
    
};
#endif