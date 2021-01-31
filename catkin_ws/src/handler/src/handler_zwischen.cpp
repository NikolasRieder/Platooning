/*
Subscribed 
*/


#include <ros/ros.h>
#include "sensor_msgs/Joy.h"
#include <std_msgs/UInt16.h>
#include <string>

#define FALSE 0
#define TRUE 1


double gl_joy_value_v = 0;
double gl_joy_value_a = 0;
double gl_rp_value_v = 0;
double gl_rp_value_a = 0;
double gl_btm_viereck = 0;
double gl_btm_x = 0;
double gl_btm_o = 0;
double gl_front_distance = 0;
double gl_notstop = 0;

bool Flankenmerker_leit;
bool Hilfsmerker_leit;

//Joy Node Subscriben
void joy_msgs_callback(const sensor_msgs::Joy::ConstPtr& joy_values)
{
	gl_btm_viereck = joy_values->buttons[0];
	gl_btm_x = joy_values->buttons[1];
	gl_btm_o = joy_values->buttons[2];
}
//verwertete Joystickwerte für Gasgeben Subscriben
void joy_v_msgs_callback(const std_msgs::UInt16::ConstPtr& joy_value_v)
{
	gl_joy_value_v = joy_value_v->data;
}
//verwertete Joystickwerte für Lenkung Subscriben
void joy_a_msgs_callback(const std_msgs::UInt16::ConstPtr& joy_value_a)
{
	gl_joy_value_a = joy_value_a->data;
}

//verwertete RPLIDARwerte für Gasgeben Subscriben
void rp_v_msgs_callback(const std_msgs::UInt16::ConstPtr& rp_value_v)
{
	gl_rp_value_v = rp_value_v->data;

}
//verwertete RPLIDARwerte für Lenkung Subscriben
void rp_a_msgs_callback(const std_msgs::UInt16::ConstPtr& rp_value_a)
{
	gl_rp_value_a = rp_value_a->data;
}



//verwertete RPLIDARwerte für Lenkung Subscriben
void notstop_msgs_callback(const std_msgs::UInt16::ConstPtr& notstop_value)
{
	gl_front_distance = notstop_value->data;
}




int main(int argc, char **argv){

ros::init(argc, argv, "handler");
ros::NodeHandle n;
ros::Rate r(10);

//Subscriber
ros::Subscriber sub_joy = n.subscribe("/joy", 1, joy_msgs_callback);


ros::Subscriber sub_joy_controll = n.subscribe("/velocity_joy", 1, joy_v_msgs_callback);
// ------------

//Testsubscriber
ros::Subscriber sub_joy_controllera = n.subscribe<std_msgs::UInt16>("/angleDirection_joy", 1, joy_a_msgs_callback);
// ------------

// NOTIZ: Namenändern im folgenden
ros::Subscriber sub_reglerlenkung = n.subscribe("/velocity_rp", 1, rp_v_msgs_callback);
ros::Subscriber sub_reglerantrieb = n.subscribe("/angleDirection_rp", 1, rp_a_msgs_callback);

ros::Subscriber sub_notstop = n.subscribe("/notstop", 1, notstop_msgs_callback);


//Publisher
ros::Publisher pub_velocity = n.advertise<std_msgs::UInt16>("/velocity", 1);
ros::Publisher pub_angleDirection = n.advertise<std_msgs::UInt16>("/angleDirection", 1);

ros::Publisher pub_btm = n.advertise<std_msgs::UInt16>("/btm", 1);

bool vier_merker = FALSE;
bool x_merker = FALSE;

while(ros::ok())
{
	// TEST weiterpublishen
	std_msgs::UInt16 msg_v;
	msg_v.data = gl_joy_value_v;
	pub_velocity.publish(msg_v);

	std_msgs::UInt16 msg_a;
	msg_a.data = gl_joy_value_a;
	pub_angleDirection.publish(msg_a);

	
	std_msgs::UInt16 msg_btm;
	msg_btm.data = gl_btm_x;
	pub_btm.publish(msg_btm);

	//IF(FALSE) ANFANG
if(FALSE){
//Notstop
	if( gl_front_distance < 5 && gl_btm_x == FALSE)
	{
		gl_notstop = TRUE;
	}
//Reset of Notstop
	if(gl_notstop = TRUE && gl_btm_o == TRUE)
	{
		gl_notstop = FALSE;
	}

// VIERECK WURDE GEDRÜCKT ==> JOYSTICK WERTE PUBLISHEN
	if ( (gl_btm_viereck == TRUE || vier_merker== TRUE) && (gl_btm_x == FALSE || x_merker == FALSE) )
	{
		// JOYSTICK´_WERTE PUBLISHEN
		vier_merker = TRUE;
		if(gl_btm_x = TRUE)
		{	
			vier_merker = FALSE;
		}
		//PUBLISHTEIL
		std_msgs::UInt16 msg_v;
		msg_v.data = gl_joy_value_v;
		pub_velocity.publish(msg_v);

		std_msgs::UInt16 msg_a;
		msg_a.data = gl_joy_value_a;
		pub_angleDirection.publish(msg_a);

	}

// X WURDE GEDRÜCKT ==> RPLIDAR WERTE PUBLISHEN
	if ( (gl_btm_x == TRUE || x_merker== TRUE) && (gl_btm_viereck == FALSE || vier_merker == FALSE) && gl_notstop == FALSE)
	{
		x_merker = TRUE;
		if(gl_btm_viereck = TRUE)
		{	
			x_merker = FALSE;
		}

		//PUBLISHTEIL
		std_msgs::UInt16 msg_v;
		msg_v.data = gl_rp_value_v;
		pub_velocity.publish(msg_v);

		std_msgs::UInt16 msg_a;
		msg_a.data = gl_rp_value_a;
		pub_angleDirection.publish(msg_a);
	}


	r.sleep();
}
return 0;

}
