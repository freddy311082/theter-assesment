//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef ICLIENTTOENGINECHANNEL_H
#define ICLIENTTOENGINECHANNEL_H
#include <memory>

#include "IChannelBase.h"
#include "../messages/client_messages/PlaceOrderMsg.h"
#include "../messages/client_messages/CancelOrderMsg.h"

namespace theter::matching_engine {

    class IClientToEngineChannel : public IChannelBase{
    public:
        virtual void sendPlaceOrder(int clientId, std::unique_ptr<PlaceOrderMsg> msg) = 0;
        virtual void sendCancelOrder(int clientId, std::unique_ptr<CancelOrderMsg> msg) = 0;
        virtual void setHandler(ClientMessageHandler* handler) = 0;
        virtual void setClientId(int clientId) = 0;
        virtual void start() = 0;
    };

}


#endif //ICLIENTTOENGINECHANNEL_H
