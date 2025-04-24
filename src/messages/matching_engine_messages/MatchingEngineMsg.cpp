//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "MatchingEngineMsg.h"
#include "../handler/MessageHandler.h"

using namespace theter::matching_engine;

void MatchingEngineMsg::dispatchTo(MessageHandler *handler, int clientId) {
    handleBy(*dynamic_cast<EngineMessageHandler*>(handler), clientId);
}
