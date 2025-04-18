//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef CANCELORDERMSG_H
#define CANCELORDERMSG_H
#include "ClientMsg.h"


namespace theter::matching_engine {

    class CancelOrderMsg : public ClientMsg {
    public:
        explicit CancelOrderMsg(int orderId) : m_orderId(orderId) {}
        void handleWith(ClientMessageHandler &handler, int clientId) override;

        int orderId() const { return m_orderId; }

    private:
        int m_orderId;
    };

}





#endif //CANCELORDERMSG_H
