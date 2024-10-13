#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

class InvertLaserNode : public rclcpp::Node {
public:
    InvertLaserNode() : Node("invert_laser") {
        this->declare_parameter<std::string>("out_frame", "lidar_front_v2_1");   //replace with your lidar frame id
        this->get_parameter("out_frame", out_frame);

        laser_pub = this->create_publisher<sensor_msgs::msg::LaserScan>("/scan_inv", 10);
        laser_sub = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan_back_filtered", 10,  //replace with your scan topic
            std::bind(&InvertLaserNode::scanCB, this, std::placeholders::_1)
        );
    }

private:
    void scanCB(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
        sensor_msgs::msg::LaserScan msg_out = *msg; // Copy the original message

        if (!out_frame.empty()) { 
            msg_out.header.frame_id = out_frame;
        }

        // Reverse readings
        std::reverse(msg_out.ranges.begin(), msg_out.ranges.end());
        std::reverse(msg_out.intensities.begin(), msg_out.intensities.end());

        laser_pub->publish(msg_out);
    }

    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr laser_pub;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub;
    std::string out_frame;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<InvertLaserNode>());
    rclcpp::shutdown();
    return 0;
}
