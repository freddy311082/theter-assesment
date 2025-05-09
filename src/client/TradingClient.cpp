//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "TradingClient.h"
#include <iostream>

using namespace theter::matching_engine;

void TradingClient::registerEngineToClientChannel(
    std::shared_ptr<IEngineToClientChannel> channel) {
    m_engineToClientChannel = channel;
}

void TradingClient::registerClientToEngineChannel(
    std::shared_ptr<IClientToEngineChannel> channel) {
    m_clientToEngineChannel = channel;
}

void TradingClient::start() {
    m_listening = true;
    
    if (auto channel = m_engineToClientChannel.lock(); channel != nullptr) {
        m_thread = std::thread([this, channel]() {
            while (m_listening) {
                auto msg = channel->pop();
                if (!msg)
                    break; // empty and closed queue
                msg->dispatchTo(this, m_clientId);
            }
        });
    }
}

void TradingClient::stop() {
    if (auto channel = m_engineToClientChannel.lock()) {
        channel->closeChannel();
    }

    if (m_thread.joinable())
        m_thread.join();
}

TradingClient::~TradingClient() {
    stop();
}

void TradingClient::handle(OrderTradedMsg &msg, int clientId) {
    std::cout << "[Client " << clientId << "] Trade executed: "
            << msg.tradedAmount() << " @ " << msg.tradedPrice() << "\n";
}

void TradingClient::handle(OrderPlacedMsg &msg, int clientId) {
    std::cout << "[Client " << clientId << "] Order placed: ID="
            << msg.order().orderId << ", Price=" << msg.order().price
            << ", Amount=" << msg.order().amount << "\n";
}

void TradingClient::handle(OrderCanceledMsg &msg, int clientId) {
    std::cout << "[Client " << clientId << "] Order canceled: ID="
            << msg.orderId() << "\n";
}

void TradingClient::placeOrder(const Order &order) {
    std::cout << "📤 Enviando orden desde cliente: ID=" <<m_clientId << ", Order Id =" << order.orderId << std::endl;
    auto orderCopy = std::make_unique<Order>(order);
    auto msg = std::make_unique<PlaceOrderMsg>(std::move(orderCopy));

    m_clientToEngineChannel.lock()->sendPlaceOrder(m_clientId, std::move(msg));
}

void TradingClient::cancelOrder(int orderId) {
    std::cout << "Client " << m_clientId << " is requesting to cancel order ID=" << orderId << std::endl;

    if (auto channel = m_clientToEngineChannel.lock()) {
        channel->sendCancelOrder(m_clientId, std::make_unique<CancelOrderMsg>(orderId));
    } else {
        std::cerr << "Client " << m_clientId << " has no active channel to cancel order." << std::endl;
    }
}

void TradingClient::handle(RequestRejectedMsg &msg, int clientId) {
    std::cout << "[Client " << clientId << "] Order rejected: ID="
            << msg.orderId() << ", Reason=" << msg.reason().description() << "\n";
}


