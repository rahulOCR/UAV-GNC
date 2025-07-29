// MESSAGE ANADRONE support class

#pragma once

namespace mavlink {
namespace anadrone {
namespace msg {

/**
 * @brief ANADRONE message
 *
 * Test all field types
 */
struct ANADRONE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 1;
    static constexpr size_t LENGTH = 1;
    static constexpr size_t MIN_LENGTH = 1;
    static constexpr uint8_t CRC_EXTRA = 214;
    static constexpr auto NAME = "ANADRONE";


    char FIELD1; /*<  char */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  FIELD1: " << +FIELD1 << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << FIELD1;                        // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> FIELD1;                        // offset: 0
    }
};

} // namespace msg
} // namespace anadrone
} // namespace mavlink
