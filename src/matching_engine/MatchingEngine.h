//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include <thread>

#include "OrderBook.h"
#include "../communication_channel/IEngineToClientChannel.h"
#include "../messages/IMessageHandler.h"


namespace theter::matching_engine {
    class IClientToEngineChannel;
    class TradingClient;

    class MatchingEngine : public ClientMessageHandler {
    public:
        void registerClient(std::shared_ptr<TradingClient> client);

        void reportOrderTraded(PlaceOrderMsg &msg,
                               IEngineToClientChannel* out,
                               std::list<MatchResult> results);

        void updateOrderOwners(std::list<MatchResult> results);

        void handle(PlaceOrderMsg &msg, int clientId) override;
        void handle(CancelOrderMsg &msg, int clientId) override;

        void print() const;
        ~MatchingEngine();


    private:
        OrderBook m_buyBook{Side::Buy};
        OrderBook m_sellBook{Side::Sell};

        std::unordered_map<int, std::shared_ptr<IEngineToClientChannel> > m_clientChannels;
        std::unordered_map<int, std::shared_ptr<IClientToEngineChannel>> m_clientInputChannels;

        bool validateOrder(Order *order, IEngineToClientChannel *out);
        std::unordered_map<int, int> m_orderOwners;
        std::recursive_mutex m_mutex;

    };
}


#endif //MATCHINGENGINE_H
