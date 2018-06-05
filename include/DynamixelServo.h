#ifndef DYNAMIXELSERVO_H
#define DYNAMIXELSERVO_H

class DynamixelServo
{
    public:

        DynamixelServo( int basePosition , double baseRadian , int positionsInOneTurn , int lowLimit , int upLimit );
        bool isValid();
        bool isValid( int position );
        
        int position();
        double radian();
        
        void setPosition( int position);
        void setAngle( double angle );

        double positionUnitToRadians( int position );
        int radiansToPositionUnit( double radians );

    private:

        int mPosition;
        double mRadian;

        int mBasePosition;
        double mBaseRadian;

        int mPositionsInOneTurn;
        double mRatioPositionUnitToRadians;
        double mRatioRadiansToPositionUnit;

        int mLowlimit;
        int mUpLimit;

        void normalizePosition();
        void normalizeRadian();
        void normalize();
};

#endif