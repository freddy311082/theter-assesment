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

        void handle(PlaceOrderMsg &msg, int clientId) override;
        void handle(CancelOrderMsg &msg, int clientId) override;
        void stop();
        ~MatchingEngine();

        void print() const;


    private:
        OrderBook m_buyBook{Side::Buy};
        OrderBook m_sellBook{Side::Sell};
        std::unordered_map<int, std::shared_ptr<IEngineToClientChannel> > m_clientChannels;

        std::atomic<bool> m_listening = false;
        std::thread m_thread;
        std::unordered_map<int, std::shared_ptr<IClientToEngineChannel>> m_clientInputChannels;

    };
}


#endif //MATCHINGENGINE_H
