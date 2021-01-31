#include <ros/ros.h>
#include "PublisherSubscriber.h"
#include "sensor_msgs/Joy.h"
#include <std_msgs/UInt16.h>

//verwertete Joystickwerte für Lenkung Subscriben
template<>
void PublisherSubscriber<std_msgs::UInt16, std_msgs::UInt16>::subscriberCallback(const std_msgs::UInt16::ConstPtr& joy_value_a)
{
	ROS_INFO(": [%d]", joy_value_a->data);

	std_msgs::UInt16 msg_a;
	msg_a.data = joy_value_a->data;
	publisherObject.publish(msg_a);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "handler");
	PublisherSubscriber<std_msgs::UInt16,std_msgs::UInt16>handler("/angleDirection","/angleDirection_joy",1);
	
	ros::spin();

	return 0;

}
