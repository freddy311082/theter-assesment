//
// Created by Freddy Martinez Garcia on 18/04/2025.
//
#include "CancelOrderMsg.h"

#include "../handler/MessageHandler.h"

using namespace theter::matching_engine;

void CancelOrderMsg::handleBy(ClientMessageHandler &handler, int clientId) {
    handler.handle(*this, clientId);
}
