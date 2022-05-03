#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <cmath>


template <typename T>
class guarded_queue{
private:
    std::mutex sign;
    std::queue<T> queue;
public:
    // default constructor and destructor
    guarded_queue() = default;
    ~guarded_queue() = default;


    // rewrite main operations with mutex
    T& front() {
        std::lock_guard guard(sign);
        return queue.front();
    }
    T& back() {
        std::lock_guard guard(sign);
        return queue.back();
    }
    bool empty() {
        std::lock_guard guard(sign);
        return queue.empty();
    }
    size_t size() {
        std::lock_guard guard(sign);
        return queue.size();
    }

    void push(T a){
        std::lock_guard guard(sign);
        queue.push(a);
    }

    void pop(){
        std::lock_guard guard(sign);
        queue.pop();
    }
};

int main() {
    guarded_queue<long> gq;
    return 0;
}
