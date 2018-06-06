#include "ros/ros.h"
#include <ros/spinner.h>
#include <widowx_ros/IntList.h>
#include <WidowX.h>

#include "WidowXServos.h"
#include <sstream>
#include <string>

using namespace std;

Vec3 askForPosition()
{
	Vec3 v;
	cout << "Position of object to reach :" << endl << "x = ";
	cin >> v.mX;
	cout << "y = ";
	cin >> v.mY;
	cout <<"z = ";
	cin >> v.mZ;
	cout << endl;
	return v;
}

widowx_ros::IntList makeMsg( std::array<int,6> positions )
{
	widowx_ros::IntList msg;
	msg.id = rand();
	msg.tag = "tag";
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

	ros::Publisher chatter_pub_position = n.advertise<widowx_ros::IntList>("robot1/GOAL_POSITION", 100);
	ros::Publisher chatter_pub_speed = n.advertise<widowx_ros::IntList>("robot1/GOAL_SPEED", 100);
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
		
		/*r.setGoal( askForPosition(), M_PI );
		if( r.canReachGoal() )
		{
			r.goToGoal();
			cout << r.pWidowXServos << endl;
			chatter_pub_speed.publish( makeMsg( r.pWidowXServos->getSpeeds() ) );
			chatter_pub_position.publish( makeMsg( r.pWidowXServos->getPositions() ));
			cout << "Message published." << endl << endl;
		}
		else
		{
			cout << "Unreachable." << endl << endl;
		}*/
		loop_rate.sleep();
		++count;
	}
	return 0;
}


