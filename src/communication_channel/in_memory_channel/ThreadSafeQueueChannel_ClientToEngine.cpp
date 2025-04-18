//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "ThreadSafeQueueChannel_ClientToEngine.h"

#include <iostream>

#include "../../messages/IMessageHandler.h"
#include  "../../messages/handler/ClientMessageHandler.h"


using namespace theter::matching_engine;

void ThreadSafeQueueChannel_ClientToEngine::sendPlaceOrder(int clientId, std::unique_ptr<PlaceOrderMsg> msg) {
    m_queue.push(std::move(msg));
}

void ThreadSafeQueueChannel_ClientToEngine::sendCancelOrder(int clientId, std::unique_ptr<CancelOrderMsg> msg) {
    m_queue.push(std::move(msg));
}

std::unique_ptr<Message> ThreadSafeQueueChannel_ClientToEngine::pop() {
    std::cout << "👂 pop() desbloqueado para cliente " << m_clientId << std::endl;
    auto clientMsg = m_queue.pop();
    return std::unique_ptr<Message>(clientMsg.release());
}

void ThreadSafeQueueChannel_ClientToEngine::closeChannel() {
    m_queue.push(nullptr); // dummy push to release the lock
}

void ThreadSafeQueueChannel_ClientToEngine::dispatchLoop(std::unique_ptr<IMessageHandler> handler, int clientId) {
    while (true) {
        auto msg = m_queue.pop();
        handler->handle(std::move(msg), clientId);
    }
}

void ThreadSafeQueueChannel_ClientToEngine::stop() {
    m_running = false;
    closeChannel();
}

void ThreadSafeQueueChannel_ClientToEngine::join() {
    if (m_thread.joinable())
        m_thread.join();
}


ThreadSafeQueueChannel_ClientToEngine::~ThreadSafeQueueChannel_ClientToEngine() {
    // void stop();
}

void ThreadSafeQueueChannel_ClientToEngine::setHandler(ClientMessageHandler* handler) {
    m_handler = handler;
}

void ThreadSafeQueueChannel_ClientToEngine::setClientId(int clientId) {
    m_clientId = clientId;
}

void ThreadSafeQueueChannel_ClientToEngine::start() {
    std::cout << "🚀 Channel started for client " << m_clientId << std::endl;
    m_running = true;
    m_thread = std::thread([&]() {
        while (m_running) {
            auto msg = m_queue.pop();
            if (!msg) break;
            if (m_handler) {
                msg->handleWith(*m_handler, m_clientId);
            }
        }
    });

}
