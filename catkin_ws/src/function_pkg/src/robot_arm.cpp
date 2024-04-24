#include "ros/ros.h"
#include "std_msgs/Int32.h"

/**
 * This function is the callback that gets executed whenever a message is received on the "color" topic.
 * It prints "arm robot is picking" when it receives a value of "1".
 */
void chatterCallback(const std_msgs::Int32::ConstPtr &msg)
{
    // Extract the received message
    std::int32_t received_message = msg->data;

    // Check if the received message is "1"
    if (received_message == 1)
    {
        // Print "arm robot is picking"
        ROS_INFO("arm robot is picking");
    }
    else
    {
        ROS_INFO("arm robot is not picking");
    }
}

int main(int argc, char **argv)
{
    // Initialize the ROS node
    ros::init(argc, argv, "listener");

    // Create a NodeHandle object
    ros::NodeHandle n;

    // Subscribe to the "color" topic
    ros::Subscriber sub = n.subscribe("color", 1000, chatterCallback);

    // Enter the ROS spin loop
    ros::spin();

    return 0;
}
