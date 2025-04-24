//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef ORDERCANCELEDMSG_H
#define ORDERCANCELEDMSG_H

#include "MatchingEngineMsg.h"


namespace theter::matching_engine {
    class OrderCanceledMsg : public MatchingEngineMsg{
    public:
        OrderCanceledMsg(int orderId) : m_orderId(orderId) {
        }

        void handleBy(EngineMessageHandler &handler, int clientId) override {
            handler.handle(*this, clientId);
        }

        int orderId() const { return m_orderId; }
    private:
        int m_orderId;
    };

}




#endif //ORDERCANCELEDMSG_H
