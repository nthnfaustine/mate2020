#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <mavros_msgs/OverrideRCIn.h>

using namespace std;

ros::Publisher override_publisher;

int currentspeedmaju = 1600;
int currentspeedmundur = 1400;

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg) {
    if (msg->axes[1] == 1) { //analog kiri(atas)
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        rcin.channels[2] = currentspeedmaju;
        rcin.channels[3] = currentspeedmaju;
        rcin.channels[4] = currentspeedmaju;
        rcin.channels[5] = currentspeedmaju;
        override_publisher.publish(rcin);
        ROS_INFO("Maju");
    }  else if (msg->axes[0] == -1) { //analog kiri(kanan)
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        rcin.channels[2] = 1600;
        rcin.channels[3] = 1400;
        rcin.channels[4] = 1400;
        rcin.channels[5] = 1600;
        override_publisher.publish(rcin);
        ROS_INFO("Geser Kanan");
    } else if (msg->axes[0] == 1) { //analog kiri(kiri)
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        rcin.channels[2] = 1400;
        rcin.channels[3] = 1600;
        rcin.channels[4] = 1600;
        rcin.channels[5] = 1400;
        override_publisher.publish(rcin);
        ROS_INFO("Geser Kiri");
    } else if (msg->axes[1] == -1) { //analog kiri(atas)
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        rcin.channels[2] = currentspeedmundur;
        rcin.channels[3] = currentspeedmundur;
        rcin.channels[4] = currentspeedmundur;
        rcin.channels[5] = currentspeedmundur;
        override_publisher.publish(rcin);
        ROS_INFO("Mundur");
    } else if (msg->axes[4] == 1) { //analog kanan(atas)
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        rcin.channels[0] = 1400;
        rcin.channels[1] = 1400;
        override_publisher.publish(rcin);
        ROS_INFO("Naik");
    } else if (msg->axes[4] == -1) { //analog kanan(bawah)
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        rcin.channels[0] = 1600;
        rcin.channels[1] = 1600;
        override_publisher.publish(rcin);
        ROS_INFO("Turun");
    } else if (msg->axes[3] == -1) { //analog kanan(kanan)
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        rcin.channels[2] = 1600;
        rcin.channels[3] = 1400;
        rcin.channels[4] = 1600;
        rcin.channels[5] = 1400;
        override_publisher.publish(rcin);
        ROS_INFO("Putar Kanan");
    } else if (msg->axes[3] == 1) { //analog kanan(kiri)
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        rcin.channels[0] = 1400;
        rcin.channels[1] = 1600;
        rcin.channels[0] = 1400;
        rcin.channels[1] = 1600;
        override_publisher.publish(rcin);
        ROS_INFO("Putar Kiri");
    } else if (msg->buttons[5]== 1) { //R1 Tambah kecepatan maju
        currentspeedmaju += 50;
        if (currentspeedmaju > 1900){currentspeedmaju = 1900;} 
        cout << "CurrentSpeed maju = " << currentspeedmaju << endl;
    } else if (msg->buttons[7]== 1) { //R2 Kurangi kecepatan maju
        currentspeedmaju -= 50;
        if (currentspeedmaju < 1550){currentspeedmaju = 1550;} 
        cout << "CurrentSpeed maju = " << currentspeedmaju << endl;
    } else if (msg->buttons[4]== 1) { //L1 Tambah kecepatan mundur
        currentspeedmundur -= 50;
        if (currentspeedmundur < 1100){currentspeedmundur = 1100;} 
        cout << "CurrentSpeed mundur = " << currentspeedmundur << endl;
    } else if (msg->buttons[6]== 1) { //L2 Kurangi kecepatan mundur
        currentspeedmundur += 50;
        if (currentspeedmundur > 1450){currentspeedmundur = 1450;} 
        cout << "CurrentSpeed mundur = " << currentspeedmundur << endl;
    } else{
        mavros_msgs::OverrideRCIn rcin;
        for(int i=0; i<=5; i++){rcin.channels[i] = 1500;}
        override_publisher.publish(rcin);
        ROS_INFO("Diem");
    }
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "testservo");
    ros::NodeHandle nh;

    override_publisher = nh.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 8);

    ros::Subscriber joy_subscriber = nh.subscribe("joy", 8, joyCallback);
    ros::spin();

}
