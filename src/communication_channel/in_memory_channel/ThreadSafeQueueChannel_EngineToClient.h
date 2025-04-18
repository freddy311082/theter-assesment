//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef THREADSAFEQUEUECHANNEL_ENGINETOCLIENT_H
#define THREADSAFEQUEUECHANNEL_ENGINETOCLIENT_H
#include "../IEngineToClientChannel.h"
#include "../../utils/ThreadSafeQueue.h"


namespace theter::matching_engine {
    class ThreadSafeQueueChannel_EngineToClient : public IEngineToClientChannel {
    public:
        void sendOrderPlaced(std::unique_ptr<OrderPlacedMsg> msg) override;

        void sendOrderCanceled(std::unique_ptr<OrderCanceledMsg> msg) override;

        void sendOrderTraded(std::unique_ptr<OrderTradedMsg> msg) override;

        void sendRequestRejected(std::unique_ptr<RequestRejectedMsg> msg) override;

        std::unique_ptr<Message> pop() override;
        void closeChannel() override;

        void setClientId(int id) override;
        void setHandler(EngineMessageHandler *handler) override;

    private:
        ThreadSafeQueue<std::unique_ptr<MatchingEngineMsg> > m_queue;
        int m_clientId = -1;
        EngineMessageHandler *m_handler = nullptr;
    };
}


#endif //THREADSAFEQUEUECHANNEL_ENGINETOCLIENT_H
