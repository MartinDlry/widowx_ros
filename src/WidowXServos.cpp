#include "WidowXServos.h"
#include <array>

const std::array<int,12> WidowXServos::boundaries = { 0 , 4095 , 1024 , 3072 , 1024 , 3072 , 1024 , 3072 , 0 , 1023 , 0 , 512 }; 
const std::array<int,6> WidowXServos::basePositions = { 2048 , 2048 , 2048 , 2048 , 512 , 256 };

WidowXServos::WidowXServos()
{
    positions = basePositions;
    printf("jean ma");
}

bool WidowXServos::isValid()
{
    for( int i = 0 ; i < 6 ; i++ )
    {
        if( positions[i] < boundaries[2*i] || positions[i] > boundaries[2*i+1] )
            return false;
    }
    return true;
}