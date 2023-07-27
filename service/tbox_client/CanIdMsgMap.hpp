if (topic == TOPIC_CAN_ID_0x64) { 
    COWA::CanMsg::CanMsg_0x64 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x64 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x65) { 
    COWA::CanMsg::CanMsg_0x65 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x65 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x6E) { 
    COWA::CanMsg::CanMsg_0x6E canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x6E << ", data:" << canMsg.DebugString() <<  std::endl;
        std::cout << "can msg 6e speed ------------------: " << canMsg.travel_distance() << std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x6F) { 
    COWA::CanMsg::CanMsg_0x6F canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x6F << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x70) { 
    COWA::CanMsg::CanMsg_0x70 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x70 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x71) { 
    COWA::CanMsg::CanMsg_0x71 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x71 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x78) { 
    COWA::CanMsg::CanMsg_0x78 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x78 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x79) { 
    COWA::CanMsg::CanMsg_0x79 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x79 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x7B) { 
    COWA::CanMsg::CanMsg_0x7B canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x7B << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x7C) { 
    COWA::CanMsg::CanMsg_0x7C canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x7C << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x7D) { 
    COWA::CanMsg::CanMsg_0x7D canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x7D << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x63) { 
    COWA::CanMsg::CanMsg_0x63 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x63 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x62) { 
    COWA::CanMsg::CanMsg_0x62 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x62 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x61) { 
    COWA::CanMsg::CanMsg_0x61 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x61 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x5F) { 
    COWA::CanMsg::CanMsg_0x5F canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x5F << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x60) { 
    COWA::CanMsg::CanMsg_0x60 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x60 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x5E) { 
    COWA::CanMsg::CanMsg_0x5E canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x5E << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x5D) { 
    COWA::CanMsg::CanMsg_0x5D canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x5D << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x5C) { 
    COWA::CanMsg::CanMsg_0x5C canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x5C << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x511) { 
    COWA::CanMsg::CanMsg_0x511 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x511 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x512) { 
    COWA::CanMsg::CanMsg_0x512 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x512 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x18FF32F0) { 
    COWA::CanMsg::CanMsg_0x18FF32F0 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x18FF32F0 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x0CFF15EF) { 
    COWA::CanMsg::CanMsg_0x0CFF15EF canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x0CFF15EF << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x0CFF16EF) { 
    COWA::CanMsg::CanMsg_0x0CFF16EF canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x0CFF16EF << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x18FF12F7) { 
    COWA::CanMsg::CanMsg_0x18FF12F7 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x18FF12F7 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x18F412EF) { 
    COWA::CanMsg::CanMsg_0x18F412EF canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x18F412EF << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x18F413EF) { 
    COWA::CanMsg::CanMsg_0x18F413EF canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x18F413EF << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x18F433EF) { 
    COWA::CanMsg::CanMsg_0x18F433EF canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x18F433EF << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x18F411EF) { 
    COWA::CanMsg::CanMsg_0x18F411EF canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x18F411EF << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x0CFF7902) { 
    COWA::CanMsg::CanMsg_0x0CFF7902 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x0CFF7902 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x0CFF7A02) { 
    COWA::CanMsg::CanMsg_0x0CFF7A02 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x0CFF7A02 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x0CFF7B02) { 
    COWA::CanMsg::CanMsg_0x0CFF7B02 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x0CFF7B02 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

if (topic == TOPIC_CAN_ID_0x0CFF7C02) { 
    COWA::CanMsg::CanMsg_0x0CFF7C02 canMsg;
    if (canMsg.ParseFromString(data)) {
        std::cout << "topic:" << TOPIC_CAN_ID_0x0CFF7C02 << ", data:" << canMsg.DebugString() <<  std::endl;
    } else {
        std::cout << "parse error" << std::endl;
    }
}

