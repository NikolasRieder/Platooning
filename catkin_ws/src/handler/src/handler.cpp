/**
Subscribed TEXT EINFÜGEN
*/


#include <ros/ros.h>
#include "sensor_msgs/Joy.h"
#include <std_msgs/UInt16.h>
#include <string>

#define FALSE 0
#define TRUE 1
#define RESET 10

// Globale Variablen zur Übergabe der Callbackfunktionen zur Main
int gl_joy_value_v = 0;
int gl_joy_value_a = 0;
int gl_rp_value_v = 0;
int gl_rp_value_a = 0;
int gl_btm_viereck = 0;
int gl_btm_x = 0;
int gl_btm_o = 0;
int gl_front_distance = RESET;
int gl_notstop = 0;
int gl_einscherung_zustand = 0;
int gl_einscherung_v = 0;
int gl_einscherung_a = 0;

// Zwischenmerker, ob Fahrzeug in Leitfahrzeugzustand, oder Kolonnenfahrtzustand sich befindet
int vier_merker = FALSE;
int x_merker = FALSE;



//Joy Node Subscriben
void joy_msgs_callback(const sensor_msgs::Joy::ConstPtr& joy_values)
{
	gl_btm_viereck = joy_values->buttons[3];
	gl_btm_x = joy_values->buttons[0];
	gl_btm_o = joy_values->buttons[1];
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

//verwertete UltraschallNotstop Subscriben
void notstop_msgs_callback(const std_msgs::UInt16::ConstPtr& notstop_value)
{
	gl_front_distance = notstop_value->data;
}

//Go-Signal von Einscherungsnode
void einscherung_zustand_msgs_callback(const std_msgs::UInt16::ConstPtr& einscherung_zustand)
{
	gl_einscherung_zustand = einscherung_zustand->data;
}

//Geschwindigkeit von Einscherung für Folgebetrieb
void einscherung_v_msgs_callback(const std_msgs::UInt16::ConstPtr& einscherung_v)
{
	gl_einscherung_v = einscherung_v->data;
}

//Lenkung von Einscherung für Folgebetrieb
void einscherung_a_msgs_callback(const std_msgs::UInt16::ConstPtr& einscherung_a)
{
	gl_einscherung_a = einscherung_a->data;
}



int main(int argc, char **argv){

ros::init(argc, argv, "handler");
ros::NodeHandle n;
ros::Rate r(10);

//--------------------------Publisher--------------------------
// Geschwindigkeit für Arduino
ros::Publisher pub_velocity = n.advertise<std_msgs::UInt16>("/velocity", 1);
// Winkelwerte für Arduino
ros::Publisher pub_angleDirection = n.advertise<std_msgs::UInt16>("/angleDirection", 10);
//Test publish
ros::Publisher pub_btm = n.advertise<std_msgs::UInt16>("/btm", 1);


//--------------------------Subscriber--------------------------
// Joystick Rohwerte
ros::Subscriber sub_joy_controllera = n.subscribe<std_msgs::UInt16>("/angleDirection_joy", 10, joy_a_msgs_callback);
// Antriebwerte von Joystick
ros::Subscriber sub_joy_controll = n.subscribe("/velocity_joy", 10, joy_v_msgs_callback);
// Lenkwerte von Joystick
ros::Subscriber sub_joy = n.subscribe("/joy", 10, joy_msgs_callback);
// Reglerwerte_Lenkung von RP-Lidar
ros::Subscriber sub_regler_lenkung = n.subscribe("/velocity_rp", 10, rp_v_msgs_callback);
// Reglerwerte_Antrieb von RP-Lidar
ros::Subscriber sub_regler_antrieb = n.subscribe("/angleDirection_rp", 10, rp_a_msgs_callback);
// Distanz-Wert von Arduino
ros::Subscriber sub_notstop = n.subscribe("/front_distance_us", 10, notstop_msgs_callback);
// Go-Signal von Einscherung für Folgebetrieb
ros::Subscriber sub_einscherung_zustand = n.subscribe("/einscherung_zustand", 10, einscherung_zustand_msgs_callback);
// Geschwindigkeit von Einscherung für Folgebetrieb
ros::Subscriber sub_einscherung_v = n.subscribe("/velocity_ein", 10, einscherung_v_msgs_callback);
// Lenkung von Einscherung für Folgebetrieb
ros::Subscriber sub_einscherung_a = n.subscribe("/angleDirection_ein", 10, einscherung_a_msgs_callback);



ros::Rate loop_rate(20);
ros::spinOnce();

while(ros::ok())
{

//Test publishen
/*

	std_msgs::UInt16 msg_a;
	msg_a.data = gl_joy_value_a;
	pub_angleDirection.publish(msg_a);

	std_msgs::UInt16 msg_v;
	msg_v.data = gl_joy_value_v;
	pub_velocity.publish(msg_v);

	std_msgs::UInt16 msg_btm;
	msg_btm.data = gl_btm_x;
	pub_angleDirection.publish(msg_btm);
*/
			if(gl_einscherung_zustand == FALSE)
			{
				std_msgs::UInt16 msg_v;
				msg_v.data = gl_einscherung_v;
				pub_velocity.publish(msg_v);

				std_msgs::UInt16 msg_a;
				msg_a.data = gl_einscherung_a;
				pub_angleDirection.publish(msg_a);
			}
			else if(gl_einscherung_zustand ==TRUE)
			{
				//PUBLISHTEIL - Kolonnenfahrt eingereiht
				std_msgs::UInt16 msg_v;
				msg_v.data = gl_rp_value_v;
				pub_velocity.publish(msg_v);

				std_msgs::UInt16 msg_a;
				msg_a.data = gl_rp_value_a;
				pub_angleDirection.publish(msg_a);
			}
	//IF(FALSE) ANFANG
	if(FALSE)
	{
		/*
		//Notstop funktion
		if( (gl_front_distance < 5) && gl_btm_x == FALSE)
		{
			gl_notstop = TRUE;
			x_merker = FALSE;
			vier_merker = FALSE;
			gl_front_distance = RESET;
			//Publish Wert 0 für Geschwindigkeit
			std_msgs::UInt16 msg_v;
			msg_v.data = 0;
			pub_velocity.publish(msg_v);
			// Publish Wert 85 für gerade Stellung der Lenkung
			std_msgs::UInt16 msg_a;
			msg_a.data = 85;
			pub_angleDirection.publish(msg_a);
		}
		//Reset of Notstop
		if(gl_notstop == TRUE && gl_btm_o == TRUE)
		{
			gl_notstop = FALSE;
			x_merker = FALSE;
			vier_merker = FALSE;
		}
		*/

		// VIERECK WURDE GEDRÜCKT ==> JOYSTICK WERTE PUBLISHEN
		if( (gl_btm_viereck == TRUE || vier_merker== TRUE) && (gl_btm_x == FALSE || x_merker == FALSE))
		{
			x_merker = FALSE;
			vier_merker = TRUE;
			if(gl_btm_x == TRUE)
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
		if ( (gl_btm_x == TRUE || x_merker == TRUE) && (gl_btm_viereck == FALSE || vier_merker == FALSE))
		{
			vier_merker = FALSE;
			x_merker = TRUE;
			if(gl_btm_viereck == TRUE)
			{	
				x_merker = FALSE;
			}
			if(gl_einscherung_zustand == FALSE)
			{
				std_msgs::UInt16 msg_v;
				msg_v.data = gl_einscherung_v;
				pub_velocity.publish(msg_v);

				std_msgs::UInt16 msg_a;
				msg_a.data = gl_einscherung_a;
				pub_angleDirection.publish(msg_a);
			}
			else if(gl_einscherung_zustand ==TRUE)
			{
				//PUBLISHTEIL - Kolonnenfahrt eingereiht
				std_msgs::UInt16 msg_v;
				msg_v.data = gl_rp_value_v;
				pub_velocity.publish(msg_v);

				std_msgs::UInt16 msg_a;
				msg_a.data = gl_rp_value_a;
				pub_angleDirection.publish(msg_a);
			}
		}	

		
	} // ENDE IF(FALSE)
	ros::spinOnce();
	loop_rate.sleep();
} // ENDE WHILE(rosok)
return 0;

}
