//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef ORDERTRADEDMSG_H
#define ORDERTRADEDMSG_H
#include <memory>

#include "MatchingEngineMsg.h"
#include "../../orders/Order.h"
#include "../handler/MessageHandler.h"


namespace theter::matching_engine {
    class OrderTradedMsg : public MatchingEngineMsg {
    public:
        OrderTradedMsg(std::unique_ptr<Order> order,
                       int tradedPrice,
                       int tradedAmount)
            : m_order(std::move(order)),
              m_tradedPrice(tradedPrice),
              m_tradedAmount(tradedAmount) {}

        const Order& order() const { return *m_order; }
        int tradedPrice() const { return m_tradedPrice; }
        int tradedAmount() const { return m_tradedAmount; }
        int orderId() const { return m_order->orderId; }
        int amountRemaining() const { return m_order->amount - m_tradedAmount; }

        void handleBy(EngineMessageHandler &handler, int clientId) override {
            handler.handle(*this, clientId);
        }

    private:
        std::unique_ptr<Order> m_order;
        int m_tradedPrice;
        int m_tradedAmount;
    };
}



#endif //ORDERTRADEDMSG_H
