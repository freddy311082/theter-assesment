//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef ORDERPLACEDMSG_H
#define ORDERPLACEDMSG_H
#include <memory>

#include "MatchingEngineMsg.h"
#include "../../orders/Order.h"
#include "../handler/MessageHandler.h"


namespace theter::matching_engine {

    class OrderPlacedMsg : public MatchingEngineMsg {
    public:
        OrderPlacedMsg(std::unique_ptr<Order> order) : m_order(std::move(order)) {
        }

        void handleBy(EngineMessageHandler &handler, int clientId) override {
            handler.handle(*this, clientId);
        }

        const Order& order() const { return *m_order; }

    private:
        std::unique_ptr<Order> m_order;
    };
}


#endif //ORDERPLACEDMSG_H
