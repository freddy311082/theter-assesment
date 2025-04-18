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
        virtual void handleWith(EngineMessageHandler& handler, int clientId) = 0;
    protected:
        MatchingEngineMsg() : Message(MsgType::MatchingEngineMsg) {
        }
    };


}



#endif //MATCHINGENGINEMSG_H
