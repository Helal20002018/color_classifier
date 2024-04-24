#include <opencv2/opencv.hpp>
#include <ros/ros.h>
// #include <sensor_msgs/MessageType.h>
#include <std_msgs/String.h>

using namespace cv;
using namespace std;
using ros::Publisher;

class ColorClassifier : public ros::Publisher
{
public:
    ColorClassifier(ros::NodeHandle &node, const string &topic) : Publisher(node, topic), topic_(topic) {}
    void process(Mat input)
    {
        // Color classification algorithm here (e.g., average color intensity, hue mask
        if (mean(input) == Vec3b(0, 255, 0))
        { // Green
            ros::Publisher::Publish(topic_, &std_msgs::String::SPtr("Green"), ros::Duration(0));
            return;
        }
        else if (mean(input) == Vec3b(0, 0, 255))
        { // Blue
            ros::Publisher::Publish(topic_, &std_msgs::String::SPtr("Blue"), ros::Duration(0));
            return;
        }
        else
        {
            ros::Publisher::Publish(topic_, &std_msgs::String(std::string("Other")), ros::Duration(0));
            return;
        }
    }
} int main(int argc, char **argv)
{
    ros::init(argc, argv, "color_classifier");
    ros::NodeHandle nh;
    string topic = "/color";
    ColorClassifier color_pub(nh, topic);

    while (ros::ok())
    {
        Mat input;
        // Read camera frame here and pass it to process function
        color_pub.process(input);

        ros::spinOnce();
        usleep(100000);
    }

    return 0;
}