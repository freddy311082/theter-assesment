//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef MESSAGE_H
#define MESSAGE_H
#include "../utils/IdGenerator.h"

namespace theter::matching_engine {

    class ClientMessageHandler;
    class MessageHandler;

    enum class MsgType {
        ClientMsg,
        MatchingEngineMsg
    };

    class Message {

    public:
        int Id() const {return m_id;}
        virtual ~Message() = default;
        virtual void dispatchTo(MessageHandler* handler, int clientId) = 0;

    protected:
        Message(MsgType side) : m_side(side) {
            m_id = IdGenerator::nextId();
        }



        MsgType m_side;
        int m_id;
    };

}



#endif //MESSAGE_H
