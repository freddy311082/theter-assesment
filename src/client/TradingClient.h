//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef TRADINGCLIENT_H
#define TRADINGCLIENT_H
#include <thread>

#include "../communication_channel/IClientToEngineChannel.h"
#include "../communication_channel/IEngineToClientChannel.h"
#include "../utils/IdGenerator.h"

namespace theter::matching_engine {

    class TradingClient : public EngineMessageHandler{
    public:
        int clientId() const { return m_clientId; }
        void registerEngineToClientChannel(std::shared_ptr<IEngineToClientChannel> channel);
        void registerClientToEngineChannel(std::shared_ptr<IClientToEngineChannel> channel);
        void start();
        void stop();
        ~TradingClient();

        void handle(OrderTradedMsg &msg, int clientId) override;
        void handle(RequestRejectedMsg &msg, int clientId) override;
        void handle(OrderPlacedMsg &msg, int clientId) override;
        void handle(OrderCanceledMsg &msg, int clientId) override;

        void placeOrder(const Order& order);
        void cancelOrder(int orderId);


    private:
        int m_clientId = IdGenerator::nextId();
        std::shared_ptr<IClientToEngineChannel> m_clientToEngineChannel;
        std::weak_ptr<IEngineToClientChannel> m_engineToClientChannel;

        std::atomic<bool> m_listening = false;
        std::thread m_thread;


    };
}



#endif //TRADINGCLIENT_H
