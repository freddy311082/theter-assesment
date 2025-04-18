//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef THREADSAFEQUEUECHANNEL_CLIENTTOENGINE_H
#define THREADSAFEQUEUECHANNEL_CLIENTTOENGINE_H
#include <thread>

#include "../IClientToEngineChannel.h"
#include "../../utils/ThreadSafeQueue.h"

namespace theter::matching_engine {
    class IMessageHandler;

    class ThreadSafeQueueChannel_ClientToEngine : public IClientToEngineChannel {
    public:
        void sendPlaceOrder(int clientId, std::unique_ptr<PlaceOrderMsg> msg) override;
        void sendCancelOrder(int clientId, std::unique_ptr<CancelOrderMsg> msg) override;
        std::unique_ptr<Message> pop() override;
        void closeChannel() override;
        void dispatchLoop(std::unique_ptr<IMessageHandler> handler, int clientId);
        void stop();
        void join();

        void setHandler(ClientMessageHandler *handler) override;
        void setClientId(int clientId) override;
        void start() override;

        ~ThreadSafeQueueChannel_ClientToEngine() override;

    private:
        std::atomic<bool> m_running = false;
        std::thread m_thread;
        ThreadSafeQueue<std::unique_ptr<ClientMsg>> m_queue;
        ClientMessageHandler* m_handler = nullptr;
        int m_clientId = -1;
    };

}




#endif //THREADSAFEQUEUECHANNEL_CLIENTTOENGINE_H
