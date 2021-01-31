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

	double x_Achse = scan->axes[0];
	int angleDirection = 0;

	if(x_Achse < 0.04 && x_Achse > -0.04)
	{ 
		//double x_Achse = 1;
		angleDirection = 85;
	
	}
	// Biege nach rechts ab
	else if(x_Achse < -0.04)
	{
		double y_Achse = scan->axes[0] + 2;
		angleDirection = map(y_Achse, 1.96, 0.998, 86, 108);
	}
	// Biege nach Links ab
	else if(x_Achse > 0.04)
	{
		double y_Achse = scan->axes[0];
		angleDirection = map(y_Achse, 0.05, 0.998, 84, 62);
	}


	msg.data = angleDirection;
	publisherObject.publish(msg);

}





int main(int argc, char **argv)
{
	ros::init(argc, argv, "joyControlla");
	PublisherSubscriber<std_msgs::UInt16,sensor_msgs::Joy>joystickworka("/angleDirection_joy", "/joy", 1000);
	ros::spin();

	return 0;
}
