#include <iostream>
#include <numeric>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

// 1. Проверить размер. Если он мал, то не распараллеливаем.
// 2. Определить количество исполнителей -- спросить у ОС.
// 3. Распределить данные между исполнителями.
// 4. Обернуть работу потоков с помощью мьютекса
// 5. Посчитать остаток и добавить его к ответу.



template <typename Iterator, typename T>
void accumulate_wrapper(Iterator begin, Iterator end, T init, T& result) {
    result = std::accumulate(begin, end, init);
}

template <typename Iterator, typename T>
T parallel_accumulate(Iterator begin, Iterator end, T init, T& result) {
    // Создаем мьютекс
    std::mutex sign;
    // Размер диапазона
    auto size = std::distance(begin, end);
    // Количество исполнителей
    auto num_workers = std::thread::hardware_concurrency();
    // Проверяем, нужно ли распараллеливать
    if (size < num_workers * 4) {
        return std::accumulate(begin, end, init);
    }
    // Распараллеливать всё-таки нужно, тогда:
    // Считаем количество данных на одного исполнителя
    auto size_per_worker = size / num_workers;
    // Распределяем данные и запускаем потоки.
    for(auto i = 0u; i < num_workers - 1; i++) {
        std::lock_guard guard(sign);
        std::thread thread(std::thread(accumulate_wrapper<Iterator, T>,
            std::next(begin, i * size_per_worker), // сдвиг begin
            std::next(begin, (i + 1) * size_per_worker), // сдвиг begin
            0, // init
            std::ref(result))); // для записи результата
            thread.join(); //блокируем текущий поток, пока наш поток не закончит работу
    }
    //делаем вычисление остатка
    accumulate_wrapper<Iterator, T>(
            std::next(begin, (num_workers - 1)*size_per_worker),
            end,
            0, // init
            std::ref(result));
    return result;
}

int main() {
    std::vector<int> sequence(100);
    int result;
    std::iota(std::begin(sequence), std::end(sequence), 0);
    std::cout << parallel_accumulate(std::begin(sequence),
                                     std::end(sequence),
                                     0, result);
}