/** @file
 *	@brief MAVLink comm testsuite protocol generated from anadrone.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "anadrone.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(anadrone, ANADRONE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::anadrone::msg::ANADRONE packet_in{};
    packet_in.FIELD1 = 'A';

    mavlink::anadrone::msg::ANADRONE packet1{};
    mavlink::anadrone::msg::ANADRONE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.FIELD1, packet2.FIELD1);
}

#ifdef TEST_INTEROP
TEST(anadrone_interop, ANADRONE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_anadrone_t packet_c {
         'A'
    };

    mavlink::anadrone::msg::ANADRONE packet_in{};
    packet_in.FIELD1 = 'A';

    mavlink::anadrone::msg::ANADRONE packet2{};

    mavlink_msg_anadrone_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.FIELD1, packet2.FIELD1);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
