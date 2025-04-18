//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef IDGENERATOR_H
#define IDGENERATOR_H
#include <atomic>

namespace theter::matching_engine {

    class IdGenerator {
    public:
        static int nextId();
    private:
        static std::atomic<int> m_counter;
    };

}




#endif //IDGENERATOR_H
