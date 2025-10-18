#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/range.hpp"
#include <random>
#include <chrono>

class DistancePublisher : public rclcpp::Node
{
public:
    DistancePublisher()
    : Node("distance_publisher"), rng_(rd_()), dist_(0.1, 1.0)
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::Range>("range_sensor", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&DistancePublisher::publishDistance, this));
    }

private:
    void publishDistance()
    {
        auto msg = sensor_msgs::msg::Range();
        msg.header.stamp = now();
        msg.header.frame_id = "distance_sensor";
        msg.radiation_type = 0;
        msg.field_of_view = 0.5;
        msg.min_range = 0.1;
        msg.max_range = 1.0;
        msg.range = dist_(rng_);
        publisher_->publish(msg);
        RCLCPP_INFO(get_logger(), "Mért távolság: %.2f m", msg.range);
    }

    rclcpp::Publisher<sensor_msgs::msg::Range>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::random_device rd_;
    std::mt19937 rng_;
    std::uniform_real_distribution<float> dist_;
};

class DistanceSubscriber : public rclcpp::Node
{
public:
    DistanceSubscriber() : Node("distance_subscriber")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::Range>(
            "range_sensor", 10,
            std::bind(&DistanceSubscriber::topicCallback, this, std::placeholders::_1));
    }

private:
    void topicCallback(const sensor_msgs::msg::Range::SharedPtr msg)
    {
        if (msg->range < 0.3)
            RCLCPP_WARN(get_logger(), "Veszélyes! %.2f m", msg->range);
        else
            RCLCPP_INFO(get_logger(), "Biztonságos!: %.2f m", msg->range);
    }

    rclcpp::Subscription<sensor_msgs::msg::Range>::SharedPtr subscription_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    auto publisher_node = std::make_shared<DistancePublisher>();
    auto subscriber_node = std::make_shared<DistanceSubscriber>();

    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(publisher_node);
    executor.add_node(subscriber_node);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}
