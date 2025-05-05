#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from custom_msg_pkg.msg import TextStamped

class TextStampedPublisher(Node):
    def __init__(self):
        super().__init__('txt_publisher')
        self.custom_msg_publisher_ = self.create_publisher(TextStamped, 'TextStamped', 10)
        self.get_logger().info("You may now enter your custom message")
        self.counter = 1

    def timer_callback(self):
        msg = TextStamped()
        try:
            msg.text = input("Enter the message: ")
            msg.sender_name = input("Enter sender name: ")
        except KeyboardInterrupt:
            return False
        
        msg.id = self.counter
        msg.timestamp = self.get_clock().now().to_msg()

        self.counter += 1
        self.custom_msg_publisher_.publish(msg)
        self.get_logger().info('Published')
        return True

def main (args = None):
    rclpy.init(args=args)
    txt_publisher = TextStampedPublisher()

    while rclpy.ok():
        if not txt_publisher.timer_callback():
            break


    txt_publisher.destroy_node()
    
    if rclpy.ok():
        rclpy.shutdown()