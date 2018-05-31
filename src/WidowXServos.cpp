#include "WidowXServos.h"

#include <array>

#include "DynamixelServo.h"

WidowXServos::WidowXServos()
{
    for( int i = 0 ; i < 6 ; i++ )
    {
        mServos[i] = new DynamixelServo( BASE_POSITIONS[i] , BASE_ANGLES[i] , TOTAL_POS[i] , LOW_LIMITS[i] , UP_LIMITS[i] );
    }
}

WidowXServos::~WidowXServos()
{
    for( int i = 0 ; i < 6 ; i++ )
    {
        delete mServos[i];
    }
}

bool WidowXServos::validPositions()
{
    for( int i = 0 ; i < 6 ; i++ )
    {
        if( !( mServos[i]->isValid() ) )
            return false;
    }
    return true;
}

std::array<int,6> WidowXServos::getPositions()
{
    std::array<int,6> array;
    for( int i = 0 ; i < 6 ; i++ )
    {
        array[i] = mServos[i]->position();
    }
}