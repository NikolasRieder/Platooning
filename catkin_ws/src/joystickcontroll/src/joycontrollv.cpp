#include <ros/ros.h>
#include "sensor_msgs/Joy.h"
#include <std_msgs/UInt16.h>
#include "PublisherSubscriber.h"

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




template <>
void PublisherSubscriber<std_msgs::UInt16, sensor_msgs::Joy>::subscriberCallback(const sensor_msgs::Joy::ConstPtr& scan)
{
	std_msgs::UInt16 msg;

	double y_Achse = scan->axes[1];
	int velocity = 0;

	if(y_Achse < 0.04)
	{ 
		velocity = 0;
	
	}
	else
	{
		double y_Achse = scan->axes[1] + 1;
		velocity = map(y_Achse, 1.041, 2, 550, 786);
	}


	msg.data = velocity;
	publisherObject.publish(msg);

}





int main(int argc, char **argv)
{
	ros::init(argc, argv, "joyControllv");
	PublisherSubscriber<std_msgs::UInt16,sensor_msgs::Joy>joystickworkv("/velocity_joy", "/joy", 1000);
	ros::spin();

	return 0;
}
