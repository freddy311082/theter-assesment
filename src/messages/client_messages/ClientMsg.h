//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef CLIENTMESSAGE_H
#define CLIENTMESSAGE_H
#include "../Message.h"
#include "../../utils/IdGenerator.h"


namespace theter::matching_engine {
    class ClientMsg : public Message{
    public:
        virtual void handleBy(ClientMessageHandler& handler, int clientId) = 0;
        void dispatchTo(MessageHandler *handler, int clientId) override;
    protected:
        ClientMsg() : Message(MsgType::ClientMsg) {
        }

    };

}




#endif //CLIENTMESSAGE_H
