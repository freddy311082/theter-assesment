//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef PLACEORDER_H
#define PLACEORDER_H
#include <memory>

#include "ClientMsg.h"
#include "../../orders/Order.h"

namespace theter::matching_engine {

    class PlaceOrderMsg : public ClientMsg {
    public:
        PlaceOrderMsg(std::unique_ptr<Order> order) : m_order(std::move(order)) {
        }

        void handleBy(ClientMessageHandler &handler, int clientId) override;

        const Order& order() const { return *m_order; }
    private:
        std::unique_ptr<Order> m_order;
    };

}


#endif //PLACEORDER_H
