//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef ICHANNELBASE_H
#define ICHANNELBASE_H
#include <memory>

#include "../messages/Message.h"

namespace theter::matching_engine {
    class IChannelBase {
    public:
        virtual std::unique_ptr<Message> pop() = 0;
        virtual void closeChannel() = 0;
        virtual ~IChannelBase() = default;
    };
}

#endif //ICHANNELBASE_H
