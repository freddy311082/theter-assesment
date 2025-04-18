//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "MatchingEngine.h"
#include "../client/TradingClient.h"

#include "../communication_channel/ChannelFactory.h"


using namespace theter::matching_engine;

void MatchingEngine::registerClient(std::shared_ptr<TradingClient> client) {
    int clientId = client->clientId();

    std::shared_ptr<IClientToEngineChannel> toEngine = ChannelFactory::newClientToEngineChannel();
    std::shared_ptr<IEngineToClientChannel> toClient = ChannelFactory::newEngineToClientChannel();

    client->registerEngineToClientChannel(toClient);
    client->registerClientToEngineChannel(toEngine);

    toClient->setHandler(client.get());
    toClient->setClientId(clientId);

    toEngine->setHandler(this);
    toEngine->setClientId(clientId);
    toEngine->start();

    m_clientChannels[clientId] = toClient;
    m_clientInputChannels[clientId] = toEngine;

    client->start();
}

void MatchingEngine::handle(PlaceOrderMsg &msg, int clientId) {
    auto out = m_clientChannels[clientId];

    auto& book = (msg.order().side == Side::Buy) ? m_buyBook : m_sellBook;

    auto orderCopy = std::make_unique<Order>(msg.order());
    auto results = book.match(std::move(orderCopy));

    for (const auto& r : results) {
        out->sendOrderTraded(std::make_unique<OrderTradedMsg>(
            std::make_unique<Order>(msg.order()),
            r.tradedPrice,
            r.tradedAmount
        ));
    }

    out->sendOrderPlaced(std::make_unique<OrderPlacedMsg>(
        std::make_unique<Order>(msg.order())
    ));
}


void MatchingEngine::handle(CancelOrderMsg& msg, int clientId) {
    auto out = m_clientChannels[clientId];

    bool removed = m_buyBook.cancelOrder(msg.orderId()) || m_sellBook.cancelOrder(msg.orderId());

    if (removed) {
        out->sendOrderCanceled(std::make_unique<OrderCanceledMsg>(msg.orderId()));
    } else {
        auto reason = std::make_unique<RejectReason>(
            RequestRejectedReason::OrderNotFound, "Order not found");
        out->sendRequestRejected(std::make_unique<RequestRejectedMsg>(msg.orderId(), std::move(reason)));
    }
}


void MatchingEngine::stop() {
    m_listening = false;

    if (m_thread.joinable())
        m_thread.join();
}

MatchingEngine::~MatchingEngine() {
    stop();
}
