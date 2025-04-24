//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "ThreadSafeQueueChannel_EngineToClient.h"
using namespace theter::matching_engine;

void ThreadSafeQueueChannel_EngineToClient::sendOrderPlaced(
    std::unique_ptr<OrderPlacedMsg> msg) {
    m_queue.push(std::move(msg));
}

void ThreadSafeQueueChannel_EngineToClient::sendOrderCanceled(
    std::unique_ptr<OrderCanceledMsg> msg) {
    m_queue.push(std::move(msg));
}

void ThreadSafeQueueChannel_EngineToClient::sendOrderTraded(
    std::unique_ptr<OrderTradedMsg> msg) {
    m_queue.push(std::move(msg));
}

void ThreadSafeQueueChannel_EngineToClient::sendRequestRejected(
    std::unique_ptr<RequestRejectedMsg> msg) {
    m_queue.push(std::move(msg));
}

std::unique_ptr<Message> ThreadSafeQueueChannel_EngineToClient::pop() {
    return m_queue.pop();
}

void ThreadSafeQueueChannel_EngineToClient::closeChannel() {
    m_queue.close();
}

void ThreadSafeQueueChannel_EngineToClient::setHandler(EngineMessageHandler *handler) {
    m_handler = handler;
}

void ThreadSafeQueueChannel_EngineToClient::setClientId(int id) {
    m_clientId = id;
}
