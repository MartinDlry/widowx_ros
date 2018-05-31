#include "ros/ros.h"
#include <ros/spinner.h>
#include <widowx_ros/IntList.h>
#include <WidowX.h>
#include "ServoGroup.h"

#include <sstream>
#include <string>

using namespace std;


void posCallback(const widowx_ros::IntList::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->tag.c_str());
}

int main(int argc, char **argv)
{	
	WidowX r = WidowX();
	cout << r.headPosition();
	getchar();
	ros::init(argc, argv, "Controller_Node");
	ros::NodeHandle n;

	ros::Publisher chatter_pub = n.advertise<widowx_ros::IntList>("robot_1/request", 100);
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
		widowx_ros::IntList msg;
		cin >> msg.tag;
		msg.id = count;
		msg.time = ros::Time::now();
		//cout << typeid(msg.data).name() ;
		msg.data.resize(6);
		ROS_INFO("%ld", msg.data.size());
		for( int i = 0 ; i < 6 ; i++ )
		{
			//msg.data.push_back( 2048 );
		}
		//msg.data = pos;

		ROS_INFO("%s", msg.tag.c_str());
		ROS_INFO("%ld", msg.data.size());
		/**
		* The publish() function is how you send messages. The parameter
		* is the message object. The type of this object must agree with the type
		* given as a template parameter to the advertise<>() call, as was done
		* in the constructor above.
		*/
		chatter_pub.publish(msg);

		loop_rate.sleep();
		++count;
	}
	return 0;
}
