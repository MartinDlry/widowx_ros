#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define L0 15.0
#define L1 14.14 // sqrt(15²-5²)
#define L2 14.75

#define PRECISION_X 0.5
#define PRECISION_Y 0.5

#define ALPHA 0.3272 // sin(5/15)


double MXToRadRatio = M_PI / 2048 ;
double radToMXRatio = 2048 / M_PI;

double l0 = L0;
double l2 = L2;
double l1 = L1;
double alpha = ALPHA;

/*
struct _2DPos
{
    double x;
    double y;
};

struct _3DPos
{
    double x;
    double y;
    double z;
};

struct motors
{
    int baseMotor;
    int shoulderMotor;
    int elbowMotor;
    int wristMotor;
};

struct circle
{
    struct _2DPos center;
    double radius;
};*/

struct _2DPos computeBaseToGrip( double a0 , double a1 , double a2 );
struct _2DPos computePos( double length , double angle );
struct _2DPos addPos( struct _2DPos pos1 , struct _2DPos pos2 );
double MXToRad ( int motorPos );
int radToMX( double radAngle );
int radToMXWrist( double radAngle );
double MXToRadWrist( int motorPos );
double MXToRadBase( int motorPos );
int isValid( struct motors m );
double distanceSquared( struct _2DPos pos1 , struct _2DPos pos2 );
int computeMotorsPositions( struct _3DPos goalPos, double goalAngle, struct motors *motors );
void compute3LastMotors( struct motors *motors, struct _2DPos elbowPosition, struct _2DPos wristPosition, double goalAngle );
struct _2DPos to2D( struct _3DPos pos );
struct _2DPos computeWristPos( struct _2DPos goalPos , double goalAngle );
int circlesIntersections( struct circle c1 , struct circle c2 , struct _2DPos intersections[] ); //table size >=2
int solveEquation( double a , double b , double c , double solutions[]); // size of table >=2
void printMotors( struct motors m );
void set2DPos( struct _2DPos *position , double x , double y );
void set3DPos( struct _3DPos *position , double x , double y , double z );
void setMotors( struct motors *motors , int baseMotor , int shoulderMotor , int elbowMotor , int wristMotor );
void setCircle( struct circle *circle , double centerX , double centerY , double radius );
struct _3DPos computeHead3DPosition( struct motors motors );
struct _2DPos computeHead2DPosition( struct motors motors );
void print2DPosition( struct _2DPos position );
void print3DPosition( struct _3DPos position );
void printCircle ( struct circle circle );

int main()
{
    struct motors m;
    struct _3DPos goal;
    setMotors( &m , 2048 , 2048 , 2048 , 2048 );
    printMotors( m );
    set3DPos( &goal , -25, 10 , 0 );
    //goal = computeHead3DPosition( m );
    print3DPosition( goal );
    int n = computeMotorsPositions( goal ,  M_PI , &m );
    printf( "\n%d", n );
    printMotors(m);
    print3DPosition( computeHead3DPosition( m ));
}

struct _3DPos computeHead3DPosition( struct motors motors )
{
    struct _3DPos head3DPosition;
    struct _2DPos head2DPosition = computeHead2DPosition( motors );
    head2DPosition.x = -head2DPosition.x;
    double baseAngle = MXToRadBase( motors.baseMotor );
    set3DPos( &head3DPosition , head2DPosition.x*cos(baseAngle) , head2DPosition.y , head2DPosition.x * sin(baseAngle) );
    return head3DPosition;
}

struct _2DPos computeHead2DPosition( struct motors motors )
{
    double a = MXToRad(motors.shoulderMotor);
    struct _2DPos pos = computePos( l0 , a + alpha );
    a += MXToRad(motors.elbowMotor);
    pos = addPos( pos , computePos( l1 , a ) );
    a += MXToRadWrist(motors.wristMotor);
    pos = addPos( pos , computePos( l2 , a ) );
    return pos;
}

struct _2DPos computePos( double length , double angle )
{
    struct _2DPos pos;
    set2DPos( &pos , length * cos(angle) , length * sin(angle) );
    return pos;
}

struct _2DPos addPos( struct _2DPos pos1 , struct _2DPos pos2 )
{
    struct _2DPos res;
    set2DPos( &res , pos1.x + pos2.x , pos1.y + pos2.y );
    return res;
}

void set2DPos( struct _2DPos *position , double x , double y )
{
    position->x = x;
    position->y = y;
}

void set3DPos( struct _3DPos *position , double x , double y , double z )
{
    position->x = x;
    position->y = y;
    position->z = z;
}

void setMotors( struct motors *motors , int baseMotor , int shoulderMotor , int elbowMotor , int wristMotor )
{
    motors->baseMotor = baseMotor;
    motors->shoulderMotor = shoulderMotor;
    motors->elbowMotor = elbowMotor;
    motors->wristMotor = wristMotor;
}

void setCircle( struct circle *circle , double centerX , double centerY , double radius )
{
    circle->center.x = centerX;
    circle->center.y = centerY;
    circle->radius = radius;
}

double MXToRad ( int motorPos )
{
    return ( (motorPos - 1024) * MXToRadRatio );
}

double MXToRadWrist( int motorPos )
{
    return ( (2048 - motorPos ) * MXToRadRatio );
}

double MXToRadBase( int motorPos )
{
    return ( motorPos * MXToRadRatio );
}

int radToMX( double radAngle )
{
    return ( 1024 + (int)(radAngle * radToMXRatio + 0.5 ) + 4096 ) % 4096 ;
}

int radToMXWrist( double radAngle )
{
    return ( (int)( 2048 - radAngle * radToMXRatio + 0.5 ) + 4096 ) % 4096 ;
}

int radToMXBase( double radAngle )
{
    return ( (int)( radAngle * radToMXRatio + 0.5) + 4096 )%4096;
}

/*int isValid( struct motors m )
{
    return (
    m.baseMotor >= 0 &&
    m.baseMotor <= 4095 &&
    m.shoulderMotor >= 1024 &&
    m.shoulderMotor <= 3072 &&
    m.elbowMotor >= 1024 &&
    m.elbowMotor <= 3072 &&
    m.wristMotor >= 1024 &&
    m.wristMotor <= 3072
    );
}*/

double distanceSquared( struct _2DPos pos1 , struct _2DPos pos2 )
{
    return ( (pos1.x-pos2.x)*(pos1.x-pos2.x) + (pos1.y-pos2.y)*(pos1.y-pos2.y) );
}

int computeMotorsPositions( struct _3DPos goalPos, double goalAngle, struct motors *motors )
{
    printf( "\n--- Computing Motors Positions ---\n");
    motors->baseMotor = radToMXBase( atan2( goalPos.z , goalPos.x ) );
    printf( "Computed Base motor : %d\n" , motors->baseMotor );
    struct _2DPos goal2D = to2D( goalPos );
    printf("\nComputed 2D goal position : \n");
    print2DPosition(goal2D);
    struct _2DPos wristPos = computeWristPos( goal2D , goalAngle);
    printf("\nComputed 2D wrist position : \n");
    print2DPosition( wristPos );
    struct circle shoulderCircle , wristCircle;

    setCircle( &shoulderCircle , 0 , 0 , l0 );
    wristCircle.center = wristPos;
    wristCircle.radius = l1;
    printf( "\n Computing Circles Instersections: \n");
    printCircle(shoulderCircle);
    printCircle(wristCircle);
    struct _2DPos possibleElbowPos[2];
    if ( circlesIntersections( shoulderCircle , wristCircle , possibleElbowPos ) == -1 )
    {
        printf("zebi");
        return -1;
    }
    printf( "\nPossible Elbow Positions :" );
    print2DPosition(possibleElbowPos[0]);
    print2DPosition(possibleElbowPos[1]);
    compute3LastMotors( motors , possibleElbowPos[0], wristPos , goalAngle );
    if( isValid( *motors ) )
    {
        return 0;
    }

    compute3LastMotors( motors , possibleElbowPos[1], wristPos , goalAngle );
    if( isValid( *motors ) )
    {
        return 0;
    }
    return -1;
}

void compute3LastMotors( struct motors *motors, struct _2DPos elbowPosition, struct _2DPos wristPosition, double goalAngle )
{
    double s = atan2( elbowPosition.y , elbowPosition.x ) -alpha , e =  atan2( (wristPosition.y - elbowPosition.y) , (wristPosition.x - elbowPosition.x ) );
    printf( "\n shoulder angle = %lf , elbow angle = %lf" , (s)*180/M_PI , (e-s) *180/M_PI );
    motors->shoulderMotor = radToMX( s );
    motors->elbowMotor = radToMX( e - s );
    motors->wristMotor = radToMXWrist(goalAngle - e);
    printf( "\n%lf", ( goalAngle - e )*180/M_PI );
}

struct _2DPos to2D( struct _3DPos pos )
{
    struct _2DPos pos2;
    set2DPos( &pos2 , -sqrt( pos.x*pos.x + pos.z*pos.z ) , pos.y );
    return pos2;
}

struct _2DPos computeWristPos( struct _2DPos goalPos , double goalAngle )
{
    struct _2DPos wristPos;
    set2DPos( &wristPos , goalPos.x - l2*cos( goalAngle ) , goalPos.y - l2*sin( goalAngle ) );
    return wristPos;
}

int circlesIntersections( struct circle c1 , struct circle c2 , struct _2DPos intersections[] ) //table size >=2
{
    double x1 = c1.center.x , y1 = c1.center.y , x2 = c2.center.x , y2 = c2.center.y , r1 = c1.radius , r2 = c2.radius;
    double m = (x1-x2)/(y2-y1);
    double p = (r1*r1 - r2*r2 - x1*x1 - y1*y1 +x2*x2 +y2*y2 )/(2*(y2-y1));
    printf("\n y = %lfx + %lf \n" , m , p );
    double a = m*m + 1;
    double b = 2*( m*p - x1 - m*y1);
    double c = x1*x1 + y1*y1 - 2*p*y1 + p*p - (r1*r1);
    printf( "\na = %lf , b = %lf , c = %lf \n" , a ,b ,c );
    double xIntersections[2];
    if ( solveEquation( a , b , c , xIntersections ) == -1 )
    {
        return -1;
    }

    intersections[0].x = xIntersections[0];
    intersections[0].y = m * xIntersections[0] + p;
    intersections[1].x = xIntersections[1];
    intersections[1].y = m * xIntersections[1] + p;
    return 0;
}

int solveEquation( double a , double b , double c , double solutions[]) // size of table >=2
{
    double delta = b*b - 4*a*c;
    if ( delta < 0 )
    {
        return -1;
    }
    solutions[0] = (-b - sqrt(delta)) / ( 2*a );
    solutions[1] = (-b + sqrt(delta)) / ( 2*a );
    return 0;
}

void printMotors( struct motors m )
{
    printf( "\nMotors:\n Base: %d\n Shoulder: %d\n Elbow: %d\n Wrist: %d\n" , m.baseMotor , m.shoulderMotor , m.elbowMotor , m.wristMotor );
}

void print2DPosition( struct _2DPos position )
{
    printf( "\n2D Position:\n x: %lf\n y: %lf\n" , position.x , position.y);
}

void print3DPosition( struct _3DPos position )
{
    printf( "\n3D Position:\n x: %lf\n y: %lf\n z: %lf\n" , position.x , position.y , position.z);
}

void printCircle ( struct circle circle )
{
    printf( "\nCircle:\n x: %lf\n y: %lf\n radius: %lf\n" , circle.center.x , circle.center.y , circle.radius );
}


