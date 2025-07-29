#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>


#define MAX_MOTORS 16


struct ServoPacket
{
  /// \brief Motor speed data.
  /// should rename to servo_command here and in ArduPilot SIM_Gazebo.cpp
  float motorSpeed[MAX_MOTORS] = {0.0f};
};


/// \brief Flight Dynamics Model packet that is sent back to the ArduPilot
struct fdmPacket
{
  /// \brief packet timestamp
  double timestamp;

  /// \brief IMU angular velocity
  double imuAngularVelocityRPY[3];

  /// \brief IMU linear acceleration
  double imuLinearAccelerationXYZ[3];

  /// \brief IMU quaternion orientation
  double imuOrientationQuat[4];

  /// \brief Model velocity in NED frame
  double velocityXYZ[3];

  /// \brief Model position in NED frame
  double positionXYZ[3];
};

fdmPacket pkt;

void receive_loop(int recv_sock) {
    char buffer[1024];
    sockaddr_in from_addr{};
    socklen_t addr_len = sizeof(from_addr);

    while (true) {
        ssize_t len = recvfrom(recv_sock, buffer, sizeof(buffer) - 1, 0,
                               (sockaddr*)&from_addr, &addr_len);
        if (len == sizeof(fdmPacket)) {
            std::memcpy(&pkt, buffer, sizeof(fdmPacket));
            std::cout << "Received: x = " << pkt.positionXYZ[0] << " y = " << pkt.positionXYZ[1] << " z = " << pkt.positionXYZ[2]<< std::endl;
        }
    }
}

int main() {
    // Create sending socket
    int send_sock = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in send_addr{};
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(9002);
    inet_pton(AF_INET, "127.0.0.1", &send_addr.sin_addr);

    // Create receiving socket
    int recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in recv_addr{};
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(9003);
    recv_addr.sin_addr.s_addr = INADDR_ANY;
    bind(recv_sock, (sockaddr*)&recv_addr, sizeof(recv_addr));

    // Start receiver in background
    std::thread receiver(receive_loop, recv_sock);
    receiver.detach();


    ServoPacket spkt;
    // for(int i = 0; i < MAX_MOTORS; i ++)
    // {
    //     if(i == 2)
    //         spkt.motorSpeed[i] = 1000;
    //     spkt.motorSpeed[i] = 1000;
    // }

    // spkt.motorSpeed[0] = 1500;
    // spkt.motorSpeed[1] = 1500;
    // spkt.motorSpeed[2] = 800;
    while (true) {
        sendto(send_sock, &spkt, sizeof(spkt), 0,
               (sockaddr*)&send_addr, sizeof(send_addr));
        // std::cout << "Sent: " << sizeof(spkt) << std::endl;
        sleep(1);
    }

    close(send_sock);
    close(recv_sock);
    return 0;
}
