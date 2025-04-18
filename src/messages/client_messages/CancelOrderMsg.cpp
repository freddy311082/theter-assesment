//
// Created by Freddy Martinez Garcia on 18/04/2025.
//
#include "CancelOrderMsg.h"

#include "../handler/ClientMessageHandler.h"

using namespace theter::matching_engine;

void CancelOrderMsg::handleWith(ClientMessageHandler &handler, int clientId) {
    handler.handle(*this, clientId);
}
