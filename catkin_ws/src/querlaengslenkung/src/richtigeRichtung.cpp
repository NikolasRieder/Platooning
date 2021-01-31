#include <ros/ros.h>
#include "PublisherSubscriber.h"
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/UInt16.h>

#define RAD2DEG(x) ((x)*180./M_PI)

int servoV = 85;
int servoIncrement = 3;

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<>
void PublisherSubscriber<std_msgs::UInt16, sensor_msgs::LaserScan>::subscriberCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
        // Parameter für Arbeitsflächeäc
        double distanceMin = 0.4; // eventuell größeren Distanzbereich auswählen
        double distanceMax = 0.7;
        double angleLeftMin = 2;
        double angleLeftMax = 12;
        double angleRightMin = -2;
        double angleRightMax = -12;

        double distanceMeasureMin = 12;
        double angle = 0;
        int lv = 0;

        // Anzahl der Messungen pro frame
        int count = scan->scan_time / scan->time_increment;

        // minimalen Abstand mit Randbedingungen finden
        for(int i = 0; i < count; i++)
        {
                if(        scan->ranges[i] < distanceMeasureMin
                        && RAD2DEG(scan->angle_min + scan->angle_increment * i) >= angleRightMax
                        && RAD2DEG(scan->angle_min + scan->angle_increment * i) <= angleLeftMax
                        && scan->ranges[i] <= distanceMax
                        && scan->ranges[i] >= distanceMin
                        && scan->ranges[i] != std::numeric_limits<float>::infinity())
                {
                        distanceMeasureMin = scan->ranges[i];
                        lv = i;
                }
                else
                {
                        continue;
                }
        }
        
        // zum minimalen Abstand dazugehöriger Winkel
        angle = RAD2DEG(scan->angle_min + scan->angle_increment * lv);

        double angleV = 0;

        // Biege nach rechts, wenn der Winkel zwischen -2deg und -10deg liegt
        if(angle <= angleRightMin && angle >= angleRightMax)
        {
                //ROS_INFO(": [%f, %f], biege nach rechts!", angle, distanceMeasureMin);
                angleV = angle *(-1);
                //servoV = map(angleV,angleRightMin*(-1),angleRightMax*(-1),86,110);
		if(servoV < (110-servoIncrement))
			servoV += servoIncrement;
        }

        // Biege nach links, wenn der Winkel zwischen 2deg und 10deg liegt
        else if(angle >= angleLeftMin && angle <= angleLeftMax)
        {
                //ROS_INFO(": [%f, %f], biege nach links!", angle, distanceMeasureMin);
                angleV = angle * (-1);
                //servoV = map(angleV,angleLeftMax*(-1),angleLeftMin*(-1),60,84);
		if(servoV > (60+servoIncrement))
			servoV -= servoIncrement;
        }

        // Gerade lenken, wenn der Winkel zwischen -2deg und 2deg liegt
        else if(angle < angleLeftMin && angle > angleRightMin)
        {
                //ROS_INFO(": [%f, %f], geradeaus!", angle, distanceMeasureMin);
		if(servoV > 85)
		{
                	servoV -= servoIncrement;
		}
		else if(servoV < 85)
		{
			servoV += servoIncrement;
		}
		else
		{
			servoV = 85;
		}
        }

        else
        {
                ros::spin();
        }
        // Daten publishen an /angleDirection
        std_msgs::UInt16 msg;
        msg.data = servoV;
        publisherObject.publish(msg);
}

int main(int argc, char **argv)
{
        ros::init(argc, argv, "querlaengslenkungNode");
        PublisherSubscriber<std_msgs::UInt16,sensor_msgs::LaserScan>querlaengslenkung("/angleDirection_rp","/scan",1);
        ros::spin();

        return 0;
}
