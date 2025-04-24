//
// Created by Freddy Martinez Garcia on 18/04/2025.
//
#include "PlaceOrderMsg.h"

#include "../handler/MessageHandler.h"

using namespace theter::matching_engine;

void PlaceOrderMsg::handleBy(ClientMessageHandler &handler, int clientId) {
    handler.handle(*this, clientId);
}
