//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef CHANNELFACTORY_H
#define CHANNELFACTORY_H
#include "IClientToEngineChannel.h"
#include "IEngineToClientChannel.h"
#include "in_memory_channel/ThreadSafeQueueChannel_ClientToEngine.h"
#include "in_memory_channel/ThreadSafeQueueChannel_EngineToClient.h"

namespace theter::matching_engine {
    class ChannelFactory {
    public:
        static std::unique_ptr<IClientToEngineChannel> newClientToEngineChannel() {
            return std::make_unique<ThreadSafeQueueChannel_ClientToEngine>();
        }
        static std::unique_ptr<IEngineToClientChannel> newEngineToClientChannel() {
            return std::make_unique<ThreadSafeQueueChannel_EngineToClient>();
        }
    };
}

#endif //CHANNELFACTORY_H
