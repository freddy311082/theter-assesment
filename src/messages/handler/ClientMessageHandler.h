//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H


namespace theter::matching_engine {

    class PlaceOrderMsg;
    class CancelOrderMsg;

    class ClientMessageHandler {
    public:
        virtual void handle(PlaceOrderMsg& msg, int clientId) = 0;
        virtual void handle(CancelOrderMsg& msg, int clientId) = 0;

        virtual ~ClientMessageHandler() = default;
    };




    class OrderTradedMsg;
    class RequestRejectedMsg;
    class OrderPlacedMsg;
    class OrderCanceledMsg;

    class EngineMessageHandler {
    public:
        virtual void handle(OrderTradedMsg& msg, int clientId) = 0;
        virtual void handle(RequestRejectedMsg& msg, int clientId) = 0;
        virtual void handle(OrderPlacedMsg& msg, int clientId) = 0;
        virtual void handle(OrderCanceledMsg& msg, int clientId) = 0;


        virtual ~EngineMessageHandler() = default;
    };
}



#endif //MESSAGEHANDLER_H
