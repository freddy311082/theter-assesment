cmake_minimum_required(VERSION 3.31)
project(theter_matching_engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(theter_matching_engine main.cpp
        src/orders/Order.cpp
        src/orders/Order.h
        src/matching_engine/OrderBook.cpp
        src/matching_engine/OrderBook.h
        src/matching_engine/MatchingEngine.cpp
        src/matching_engine/MatchingEngine.h
        src/messages/client_messages/PlaceOrderMsg.cpp
        src/messages/client_messages/PlaceOrderMsg.h
        src/messages/client_messages/CancelOrderMsg.cpp
        src/messages/client_messages/CancelOrderMsg.h
        src/messages/matching_engine_messages/OrderPlacedMsg.cpp
        src/messages/matching_engine_messages/OrderPlacedMsg.h
        src/messages/matching_engine_messages/OrderCanceledMsg.cpp
        src/messages/matching_engine_messages/OrderCanceledMsg.h
        src/messages/matching_engine_messages/OrderTradedMsg.cpp
        src/messages/matching_engine_messages/OrderTradedMsg.h
        src/messages/matching_engine_messages/RequestRejectedMsg.cpp
        src/messages/matching_engine_messages/RequestRejectedMsg.h
        src/messages/Message.cpp
        src/messages/Message.h
        src/messages/client_messages/ClientMsg.cpp
        src/messages/client_messages/ClientMsg.h
        src/messages/matching_engine_messages/MatchingEngineMsg.cpp
        src/messages/matching_engine_messages/MatchingEngineMsg.h
        src/communication_channel/IClientToEngineChannel.h
        src/communication_channel/IEngineToClientChannel.h
        src/utils/IdGenerator.cpp
        src/utils/IdGenerator.h
        src/utils/ThreadSafeQueue.cpp
        src/utils/ThreadSafeQueue.h
        src/communication_channel/in_memory_channel/ThreadSafeQueueChannel_ClientToEngine.cpp
        src/communication_channel/in_memory_channel/ThreadSafeQueueChannel_ClientToEngine.h
        src/messages/IMessageHandler.h
        src/communication_channel/in_memory_channel/ThreadSafeQueueChannel_EngineToClient.cpp
        src/communication_channel/in_memory_channel/ThreadSafeQueueChannel_EngineToClient.h
        src/client/TradingClient.cpp
        src/client/TradingClient.h
        src/communication_channel/IChannelBase.h
        src/communication_channel/ChannelFactory.h
        src/messages/handler/ClientMessageHandler.h)
