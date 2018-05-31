#ifndef DYNAMIXELSERVO_H
#define DYNAMIXELSERVO_H

class DynamixelServo
{
    public:

        DynamixelServo( int basePosition , double baseRadian , int positionsInOneTurn , int lowLimit , int upLimit );
        bool isValid();
        
        int position();
        double radian();
        
        void setPosition( int position);
        void setAngle( double angle );

        static double positionUnitToRadians( int position );
        static int radiansToPositionUnit( double radians );

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