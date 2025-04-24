//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "ClientMsg.h"
#include "../handler/MessageHandler.h"

using namespace theter::matching_engine;

void ClientMsg::dispatchTo(MessageHandler *handler, int clientId) {
    handleBy(*dynamic_cast<ClientMessageHandler*>(handler), clientId);
}
