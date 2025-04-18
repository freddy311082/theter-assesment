//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef REQUESTREJECTEDMSG_H
#define REQUESTREJECTEDMSG_H
#include <algorithm>
#include <string>

#include "MatchingEngineMsg.h"


namespace theter::matching_engine {
    enum class RequestRejectedReason {
        OrderNotFound,
        NotOwner,
        InvalidQuantity,
        InvalidPrice
    };

    class RejectReason {
    public:
        RejectReason(RequestRejectedReason code, const std::string &description) : m_code(code),
            m_description(description) {
        }

        RequestRejectedReason code() const { return m_code; }
        const std::string &description() const { return m_description; }

    private:
        RequestRejectedReason m_code;
        std::string m_description;
    };

    class RequestRejectedMsg : public MatchingEngineMsg {
    public:
        RequestRejectedMsg(int orderId, std::unique_ptr<RejectReason> reason)
            : m_orderId(orderId),
              m_reason(std::move(reason)) {
        }

        int orderId() const { return m_orderId; }
        RejectReason &reason() const { return *m_reason; }

        void handleWith(EngineMessageHandler &handler, int clientId) override {
            handler.handle(*this, clientId);
        }

    private:
        int m_orderId;
        std::unique_ptr<RejectReason> m_reason;
    };
}


#endif //REQUESTREJECTEDMSG_H
