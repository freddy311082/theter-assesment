//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "IdGenerator.h"


using namespace theter::matching_engine;
std::atomic<int> IdGenerator::m_counter = 0;

int IdGenerator::nextId() {
    return m_counter.fetch_add(1, std::memory_order_relaxed);
}

