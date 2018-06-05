#include "DynamixelServo.h"

#include <math.h>

DynamixelServo::DynamixelServo( int basePosition , double baseRadian , int positionsInOneTurn , int lowLimit , int upLimit )
{
    mBasePosition = basePosition;
    mBaseRadian = baseRadian ;
    mPositionsInOneTurn = positionsInOneTurn;
    mLowlimit = lowLimit;
    mUpLimit = upLimit;

    mPosition = basePosition;
    mRadian = baseRadian;

    mRatioPositionUnitToRadians = ( M_PI * 2) / mPositionsInOneTurn ;
    mRatioRadiansToPositionUnit = 1 / mRatioPositionUnitToRadians ;

    if ( mPositionsInOneTurn < 0 )
        mPositionsInOneTurn = -mPositionsInOneTurn;
}

bool DynamixelServo::isValid()
{
    return( ( mPosition >= mLowlimit ) && ( mPosition <= mUpLimit) );
}

bool DynamixelServo::isValid( int position )
{
    return( ( position >= mLowlimit ) && ( position <= mUpLimit) );
}

int DynamixelServo::position()
{
    return ( mPosition );
}

double DynamixelServo::radian()
{
    return ( mRadian );
}

void DynamixelServo::setPosition( int position )
{
    mPosition =  position;
    mRadian = positionUnitToRadians( position );
    normalize();
}

void DynamixelServo::setAngle( double radians )
{
    mRadian = radians;
    mPosition = radiansToPositionUnit( radians );
    normalize();
}

double DynamixelServo::positionUnitToRadians( int position )
{
    return( mBaseRadian + mRatioPositionUnitToRadians * ( position - mBasePosition ) );
}

int DynamixelServo::radiansToPositionUnit( double radians )
{
    return( mBasePosition + mRatioRadiansToPositionUnit * ( radians - mBaseRadian ) + 0.5 );
}

void DynamixelServo::normalizePosition()
{   
    mPosition = mPosition % mPositionsInOneTurn;
    if( mPosition < 0 )
        mPosition += mPositionsInOneTurn;
}

void DynamixelServo::normalizeRadian()
{
    mRadian = remainder ( mRadian , 2 * M_PI );
    if( mRadian < 0 )
        mRadian += 2 * M_PI;
}

void DynamixelServo::normalize()
{
    normalizePosition();
    normalizeRadian();
}

