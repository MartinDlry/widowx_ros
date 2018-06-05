#include "WidowXServos.h"

#include <array>
#include <math.h>
#include <ostream>

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

bool WidowXServos::validPositions( std::array<int,6> positions )
{
    for( int i = 0 ; i < 6 ; i++ )
    { 
        if( !( mServos[i]->isValid( positions[i]) ) )
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
    return array;
}

void WidowXServos::setPositions( std::array<int,6> positions )
{
    for( int i = 0 ; i < 6 ; i++ )
    {
        mServos[i]->setPosition( positions[i] );
    }
}

int WidowXServos::variation( WidowXServos *servos )
{
    int variation = 0;
    for ( int i = 0 ; i < 6 ; i++ )
        variation += abs( mServos[i]->position() - servos->mServos[i]->position() );
}

std::array<double,6> WidowXServos::getRadians()
{
    std::array<double,6> array;
    for( int i = 0 ; i < 6 ; i++ )
    {
        array[i] = mServos[i]->radian();
    }
    return array;
}

std::ostream& operator<<(std::ostream &strm, const WidowXServos &wxServos )
{
    strm << "WidowX Servos : [ " << wxServos.mServos[0]->position(); 
    for( int i = 1 ; i < 6 ; i++ )
    {
        strm << " , " << wxServos.mServos[i]->position();
    }
    strm << " ]" << std::endl;

    return strm;
}