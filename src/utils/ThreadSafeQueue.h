//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H
#include <mutex>
#include <queue>


namespace theter::matching_engine {

    template <typename T>
    class ThreadSafeQueue {
    public:
        ThreadSafeQueue() = default;
        ~ThreadSafeQueue() = default;

        // avoiding copies
        ThreadSafeQueue(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

        void push(T value) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(std::move(value));
            m_cond.notify_one();
        }

        T pop() {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cond.wait(lock, [this]() { return !m_queue.empty(); });

            T value = std::move(m_queue.front());
            m_queue.pop();
            return value;
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_queue.empty();
        }

        size_t size() const {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_queue.size();
        }

    private:
        mutable std::mutex m_mutex;
        std::queue<T> m_queue;
        std::condition_variable m_cond;
    };
}



#endif //THREADSAFEQUEUE_H
