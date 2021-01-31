#ifndef PUBLISHER_SUBSCRIBER_H
#define PUBLISHER_SUBSCRIBER_H

#include <ros/ros.h>
#include <string>

template<typename PublishT, typename SubscrubeT>
class PublisherSubscirber
{
public:
	PublisherSubscriber(){}
	PublisherSubscriber(std::string publishTopicName, std::string subscribeTopicName, int queueSize)
	{
		publisherObject = nh.advertise<PublishT>(publishTopicName, queueSize);
		subscriberObject = nh.subscribe<SubscribeT>(subscribeTopicName, queueSize, &PublisherSubscriber::subcriberCallback,this);
	}
	coid subscribeCallback(const typename SubscribeT::ConstPtr& scan);

protected:
	ros::Subscriber subscriberObject;
	ros::Publisher publisherObject;
	ros::NodeHandle nh;
};

#endif
