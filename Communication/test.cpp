#include <iostream>
#include <stdio.h>
#include <TEST/anadrone/mavlink.h>

int main()
{
    uint8_t buffer[1024];
    mavlink_message_t msg;
    mavlink_anadrone_t tst;
    tst.FIELD1 = 'd';
    mavlink_msg_anadrone_encode(200, 1, &msg, &tst);
    const int len = mavlink_msg_to_send_buffer(buffer, &msg);

    for(int i = 0; i < len; i++)
        printf("%02x", buffer[i]);

    std::cout << std::endl << len << std::endl;

    mavlink_message_t mg;
    mavlink_status_t st;

    // MAVLINK_MSG_ID_ANADRONE;

    for(int i = 0; i < len; i++)
    {
        if(mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &msg, &st))
        {

        }
    }

    
    mavlink_anadrone_t tt;

    mavlink_msg_anadrone_decode(&msg, &tt);

    std::cout <<msg.msgid << " , " << tt.FIELD1 << std::endl;




    return 0;
        
}

