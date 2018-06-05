#include "ros/ros.h"
#include <ros/spinner.h>
#include <widowx_ros/IntList.h>
#include <WidowX.h>

#include "ServoGroup.h"
#include "WidowXServos.h"
#include <sstream>
#include <string>

using namespace std;

Vec3 askForPosition()
{
	Vec3 v;
	cout << "Position of object to reach :" << endl << "x = ";
	cin >> v.mX;
	cout << endl << "y = ";
	cin >> v.mY;
	cout << endl << "z = ";
	cin >> v.mZ;
	cout << endl;
	return v;
}

widowx_ros::IntList makeMsg( std::array<int,6> positions )
{
	widowx_ros::IntList msg;
	msg.id = rand();
	msg.tag = "GOAL_POSITION";
	msg.time = ros::Time::now();
	for( int i = 0 ; i < 6 ; i ++ )
	{
		msg.data.push_back(positions[i]);
	}
	return msg;
}

void posCallback(const widowx_ros::IntList::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->tag.c_str());
}

int main(int argc, char **argv)
{	
	WidowX r = WidowX();
	ros::init(argc, argv, "Controller_Node");
	ros::NodeHandle n;

	ros::Publisher chatter_pub = n.advertise<widowx_ros::IntList>("robot1/GOAL_POSITION", 100);
	ros::Subscriber sub = n.subscribe("robot_1/output", 100 , posCallback);
	ros::Rate loop_rate(10);
	ros::AsyncSpinner aSpinner( 1 );
	aSpinner.start();
	/**
	* A count of how many messages we have sent. This is used to create
	* a unique string for each message.
	*/
	int count = 0;
	std::vector<int> pos( 6 , 2048 );
	while (ros::ok())
	{
		r.setGoal( askForPosition(), M_PI );
		if( r.canReachGoal() )
		{
			r.goToGoal();
			widowx_ros::IntList msg = makeMsg( ((WidowXServos*)r.pServoGroup)->getPositions() );
			chatter_pub.publish(msg);
		}

		loop_rate.sleep();
		++count;
	}
	return 0;
}


