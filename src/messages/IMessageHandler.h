//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef IMESSAGEHANDLER_H
#define IMESSAGEHANDLER_H
#include <memory>

#include "Message.h"

namespace theter::matching_engine {
    class ClientMsg;

    class IMessageHandler {
    public:
        virtual void handle(std::unique_ptr<ClientMsg> msg, int clientId) = 0;
        virtual ~IMessageHandler() = default;
    };
}

#endif //IMESSAGEHANDLER_H
