//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef MATCHINGENGINEMSG_H
#define MATCHINGENGINEMSG_H
#include "../Message.h"


namespace theter::matching_engine {

    class EngineMessageHandler;

    class MatchingEngineMsg : public Message {
    public:
        virtual void handleBy(EngineMessageHandler& handler, int clientId) = 0;
        void dispatchTo(MessageHandler* handler, int clientId) override;
    protected:
        MatchingEngineMsg() : Message(MsgType::MatchingEngineMsg) {
        }
    };


}



#endif //MATCHINGENGINEMSG_H
