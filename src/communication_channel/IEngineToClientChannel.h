//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef IENGINETOCLIENTCHANNEL_H
#define IENGINETOCLIENTCHANNEL_H


#include "IChannelBase.h"
#include "../messages/matching_engine_messages/OrderPlacedMsg.h"
#include "../messages/matching_engine_messages/OrderCanceledMsg.h"
#include "../messages/matching_engine_messages/OrderTradedMsg.h"
#include "../messages/matching_engine_messages/RequestRejectedMsg.h"

namespace theter::matching_engine {

    class IEngineToClientChannel : public IChannelBase{
    public:
        virtual void sendOrderPlaced(std::unique_ptr<OrderPlacedMsg> msg) = 0;
        virtual void sendOrderCanceled(std::unique_ptr<OrderCanceledMsg> msg) = 0;
        virtual void sendOrderTraded(std::unique_ptr<OrderTradedMsg> msg) = 0;
        virtual void sendRequestRejected(std::unique_ptr<RequestRejectedMsg> msg) = 0;

        virtual void setHandler(EngineMessageHandler* handler) = 0;
        virtual void setClientId(int id) = 0;
    };

}



#endif //IENGINETOCLIENTCHANNEL_H
