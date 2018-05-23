#include "ros/ros.h"
#include <widowx_ros/Request.h>
#include <sstream>

using namespace std;
/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{

	ros::init(argc, argv, "node");

	ros::NodeHandle n;

	ros::Publisher chatter_pub = n.advertise<widowx_ros::Request>("robot1/input", 1000);

	ros::Rate loop_rate(10);

	/**
	* A count of how many messages we have sent. This is used to create
	* a unique string for each message.
	*/
	int count = 0;
	while (ros::ok())
	{
		/**
		* This is a message object. You stuff it with data, and then publish it.
		*/
		widowx_ros::Request msg;
		cin >> msg.request;
		msg.requestId = count;
		msg.time = ros::Time::now();

		ROS_INFO("%s", msg.request.c_str());

		/**
		* The publish() function is how you send messages. The parameter
		* is the message object. The type of this object must agree with the type
		* given as a template parameter to the advertise<>() call, as was done
		* in the constructor above.
		*/
		chatter_pub.publish(msg);

		ros::spinOnce();

		loop_rate.sleep();
		++count;
	}


	return 0;
}
