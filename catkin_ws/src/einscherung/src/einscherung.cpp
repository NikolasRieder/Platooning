#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include <std_msgs/UInt16.h>

#define RAD2DEG(x) ((x)*180./M_PI)

#define FALSE 0
#define TRUE 1


// Globale Variablen
int gl_distance = 0;
int gl_angle = 0; 
bool einscherungsphase = false;
bool einscherungsfahrt = false;

int v_ausscheren = 650;
int a_ausscheren_links = 61;
int a_ausscheren_gerade = 85;
// Abzuwartende Takte bis nächste Sequenz
int stoppzeit = 8;
int stoppuhr = 0;
int wand_merker = 0;
int fertig_merker = 0;
int pegel_merker = 0;

// Parameter für Kegelbereich -- Initialisiert mit hinterem Pegel
double distanceMin = 0.4;
double distanceMax = 0.8;
double angleLeftMax = 80;
double angleRightMax = 180;

//Rückgabewerte von Callback
int pub_vel = 0;
int pub_angle = 85;
int pub_zustand = 0;

//Subscriber Callback Funktionen
void rp_werte_callback(const sensor_msgs::LaserScan::ConstPtr& scan)
{

	double distanceMeasure = 0;

	// Anzahl der Messungen pro frame
        int count = scan->scan_time / scan->time_increment;

	if(pegel_merker == 0){

		// Abstand mit Randbedingungen finden
       	 	for(int i = 0; i < count; i++)
        	{
                	if(        RAD2DEG(scan->angle_min + scan->angle_increment * i) <= angleRightMax
                        	&& RAD2DEG(scan->angle_min + scan->angle_increment * i) >= angleLeftMax
				&& scan->ranges[i] <= distanceMax
                        	&& scan->ranges[i] >= distanceMin
                        	&& scan->ranges[i] != std::numeric_limits<float>::infinity())
                	{
                        	distanceMeasure = scan->ranges[i];
                	}
                	else
                	{
                        	continue;
                	}
        	}
	}
	else if(pegel_merker == 1){

		// Abstand mit Randbedingungen finden
       	 	for(int i = 0; i < count; i++)
        	{
                	if(        RAD2DEG(scan->angle_min + scan->angle_increment * i) >= angleRightMax
                        	&& RAD2DEG(scan->angle_min + scan->angle_increment * i) <= angleLeftMax
				&& scan->ranges[i] <= distanceMax
                        	&& scan->ranges[i] >= distanceMin
                        	&& scan->ranges[i] != std::numeric_limits<float>::infinity())
                	{
                        	distanceMeasure = scan->ranges[i];
                	}
                	else
                	{
                        	continue;
                	}
        	}
	}
	ROS_INFO(": [%f], Entfernung!, [%d], stoppuhr!, [%d], einscherungsphase!, [%d], einscherungsfahrt!", distanceMeasure, stoppuhr, einscherungsphase, einscherungsfahrt);

	// Wenn was gemessen wird - Bis das erste mal was gemessen wird
	if(distanceMeasure != 0 && einscherungsphase == false && einscherungsfahrt == false && fertig_merker == 0)
	{
		// beginne mit der Einscherungsphase
		einscherungsphase = true;
	}
	
	// Beginn der Einscherungsphase
	else if(einscherungsphase == true)
	{	//DistanceMeasure geändert 5 auf 1, 1 auf 0.2
		// warte solange sich nichts hinter unserem Fahrzeug befindet
		//if((distanceMeasure < 1 && distanceMeasure > 0.2) && stoppuhr <= stoppzeit && distanceMeasure == 0)
		if(stoppuhr <= stoppzeit && distanceMeasure == 0)
		{
			// beginne mit der Einscherungsfahrt
			// maximale servo lenkung nach links
			// minimaler motorantrieb
			// für eine gewisse zeit

			pub_angle = a_ausscheren_links;
			pub_vel = v_ausscheren;
			// Wenn nun das erste mal der hintere/seitliche FOI verlassen wird, kann 				//auch Wand detektiert werden
			wand_merker = 1;

			stoppuhr = stoppuhr +1;
		}
//		else if((distanceMeasure != 0 && stoppuhr <= stoppzeit) && wand_merker == 1)
		// Fahre weiter auch, wenn du während des Drehens Wand erkennst
		else if((stoppuhr <= stoppzeit) && wand_merker == 1)
		{
			// beginne mit der Einscherungsfahrt
			// maximale servo lenkung nach links
			// minimaler motorantrieb
			// für eine gewisse zeit

			pub_angle = a_ausscheren_links;
			pub_vel = v_ausscheren;

			stoppuhr = stoppuhr +1;
		}
		else if(stoppuhr > stoppzeit)
		{
			einscherungsfahrt = true;
			einscherungsphase = false;
		}
		
	}

	//Einscherungsfahrt beginnen
	else if(einscherungsfahrt == true && (fertig_merker == 0)){
		// FOI vor dem Fahrzeug
		angleRightMax = -15;
		angleLeftMax = 30;
		distanceMax = 0.8;
		distanceMin = 0.2;
		
		pegel_merker = 1;

		pub_angle = a_ausscheren_gerade;
		pub_vel = v_ausscheren;
		
	}

	if((einscherungsfahrt == true) && (einscherungsphase == false) && (distanceMeasure < 0.3) && (distanceMeasure > 0.1) )
	{
	//Go für Kolonnenfahrt geben
		pub_zustand = 1;
		fertig_merker = 1;
	}

}


int main(int argc, char **argv)
{
	// CODE
	ros::init(argc, argv, "einscherung");
	ros::NodeHandle n;
	ros::Rate loop_rate(20);
	// -----Publisher-----
	ros::Publisher pub_angleDirection_ein = n.advertise<std_msgs::UInt16>("/angleDirection_ein", 10);
	ros::Publisher pub_velocity_ein = n.advertise<std_msgs::UInt16>("/velocity_ein", 10);
	ros::Publisher pub_einscherung_zustand = n.advertise<std_msgs::UInt16>("/einscherung_zustand", 10);

	// -----Subscriber-----
	// RP-Lidar-Werte
	ros::Subscriber sub_SUBSCRIBER = n.subscribe("/scan", 10, rp_werte_callback);

	ros::spinOnce();

	while(ros::ok() )
	{
		// publish
		// Lenkungs-Wert
		std_msgs::UInt16 msg_a;
		msg_a.data = pub_angle;
		pub_angleDirection_ein.publish(msg_a);
		// Geschwindigkeits-Wert
		std_msgs::UInt16 msg_v;
		msg_v.data = pub_vel;
		pub_velocity_ein.publish(msg_v);

		// Status publishen
		std_msgs::UInt16 msg_z;
		msg_z.data = pub_zustand;
		pub_einscherung_zustand.publish(msg_z);
		
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;

}
