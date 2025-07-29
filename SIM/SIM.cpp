#include "SIM.h"
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <cstring>


/*
  Create and set in/out socket
*/
void SIM::set_interface_ports(const char* address, const int port_in, const int port_out)
{
    // Create sending socket
    send_socket = socket(AF_INET, SOCK_DGRAM, 0);
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(port_out);
    inet_pton(AF_INET, address, &send_addr.sin_addr);

    // Create receiving socket
    rec_socket = socket(AF_INET, SOCK_DGRAM, 0);
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(port_in);
    recv_addr.sin_addr.s_addr = INADDR_ANY;
    bind(rec_socket, (sockaddr*)&recv_addr, sizeof(recv_addr));
}

/*
  decode and send servos
*/
void SIM::send_servos(float input[])
{
    servo_packet pkt;
    // should rename servo_command
    // 16 because struct sitl_input.servos is 16 large in SIM_Aircraft.h
    for (unsigned i = 0; i < 16; ++i)
    {
      pkt.motor_speed[i] = (input[i]-1000) / 1000.0f;
      
    }
    
    sendto(send_socket, &pkt, sizeof(pkt), 0,
               (sockaddr*)&send_addr, sizeof(send_addr));
}

/*
  receive an update from the FDM
  This is a blocking function
 */
void SIM::recv_fdm(float input[])
{
    fdm_packet pkt;
    char buffer[1024];
    sockaddr_in from_addr{};
    socklen_t addr_len = sizeof(from_addr);
    /*
      we re-send the servo packet every 0.1 seconds until we get a
      reply. This allows us to cope with some packet loss to the FDM
     */
    while(true)
    {
        ssize_t len = recvfrom(rec_socket, buffer, sizeof(buffer) - 1, 0,
                               (sockaddr*)&from_addr, &addr_len);
        
        if (len == sizeof(pkt)) {
            std::memcpy(&pkt, buffer, sizeof(fdm_packet));
        }
    }

    // get imu stuff
    accel_body = Vector3f(static_cast<float>(pkt.imu_linear_acceleration_xyz[0]),
                          static_cast<float>(pkt.imu_linear_acceleration_xyz[1]),
                          static_cast<float>(pkt.imu_linear_acceleration_xyz[2]));

    
    gyro = Vector3f(static_cast<float>(pkt.imu_angular_velocity_rpy[0]),
                    static_cast<float>(pkt.imu_angular_velocity_rpy[1]),
                    static_cast<float>(pkt.imu_angular_velocity_rpy[2]));

    // compute dcm from imu orientation
    Quaternion quat(static_cast<float>(pkt.imu_orientation_quat[0]),
                    static_cast<float>(pkt.imu_orientation_quat[1]),
                    static_cast<float>(pkt.imu_orientation_quat[2]),
                    static_cast<float>(pkt.imu_orientation_quat[3]));
    quat.rotation_matrix(dcm);

    velocity_ef = Vector3f(static_cast<float>(pkt.velocity_xyz[0]),
                           static_cast<float>(pkt.velocity_xyz[1]),
                           static_cast<float>(pkt.velocity_xyz[2]));

    position = Vector3d(pkt.position_xyz[0],
                        pkt.position_xyz[1],
                        pkt.position_xyz[2]);
    position.xy() += origin.get_distance_NE_double(home);

}

/*
  Drain remaining data on the socket to prevent phase lag.
 */
void SIM::drain_sockets()
{
    const uint16_t buflen = 1024;
    char buf[buflen];
    ssize_t received;
    errno = 0;
    do {
        received = socket_sitl.recv(buf, buflen, 0);
        if (received < 0) {
            if (errno != EAGAIN && errno != EWOULDBLOCK && errno != 0) {
                fprintf(stderr, "error recv on socket in: %s \n",
                        strerror(errno));
            }
        } else {
            // fprintf(stderr, "received from control socket: %s\n", buf);
        }
    } while (received > 0);

}

/*
  update the Gazebo simulation by one time step
 */
void SIM::update(const struct sitl_input &input)
{
    send_servos(input);
    recv_fdm(input);
   

    
    // update magnetic field
    drain_sockets();
}
