#include <memory>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "custom_msg_pkg/msg/text_stamped.hpp"

using std::placeholders::_1;
using namespace rclcpp;

class TextStampedSubscriber : public Node {
    private:
        int headerPrinted = 0;
        void topic_callback (const custom_msg_pkg::msg::TextStamped & msg) {
            Time currentTime = this->get_clock()->now();
            Time timeSent = msg.timestamp;

            Duration deliveryDelay = currentTime - timeSent;

            std::stringstream header;
            std::stringstream content;
            std::string hyphonSeperator = std::string(100, '-');

            header<<"\033[1;33m"
                  <<std::left<<std::setw(18)<<"Message sent"
                  <<std::left<<std::setw(18)<<"Current Time"
                  <<std::left<<std::setw(10)<<"Delay"
                  <<std::left<<std::setw(25)<<"Received message"
                  <<std::left<<std::setw(15)<<"Sender"
                  <<std::left<<std::setw(5)<<"Sender Id"
                  <<"\033[0m";

            content<<"\033[1;35m"
                   <<std::fixed<<std::setprecision(2)
                   <<std::left<<std::setw(18)<<timeSent.seconds()
                   <<std::left<<std::setw(18)<<currentTime.seconds()
                   <<std::left<<std::setw(10)<<deliveryDelay.seconds()
                   <<std::left<<std::setw(25)<<msg.text
                   <<std::left<<std::setw(15)<<msg.sender_name
                   <<std::left<<std::setw(5)<<msg.id
                   <<"\033[0m";
            
            if (headerPrinted == 0) {
                RCLCPP_INFO (this->get_logger(), "%s", header.str().c_str());
                headerPrinted = 1;
            }
            RCLCPP_INFO (this->get_logger(), "%s", hyphonSeperator.c_str());
            RCLCPP_INFO (this->get_logger(), "%s", content.str().c_str());

        }
        Subscription<custom_msg_pkg::msg::TextStamped>::SharedPtr subscription_;
    
        public:
            TextStampedSubscriber(): Node("cstm_msg_sub") {
                subscription_ = this->create_subscription<custom_msg_pkg::msg::TextStamped> (
                    "TextStamped", 10, std::bind(&TextStampedSubscriber::topic_callback, this, _1)
                );
                RCLCPP_INFO (this->get_logger(), 
                    "Subscriber is ready. Waiting for a message from publisher..." 
                ); 
            }

};

int main (int argc, char* argv[]) {

    init(argc, argv);
    spin(std::make_shared<TextStampedSubscriber>());

    shutdown();

    return 0;
}