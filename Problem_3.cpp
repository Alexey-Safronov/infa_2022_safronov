#include <iostream>
#include <iterator>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>


template <typename C> void print(const C& c) {
    for (const auto& e : c) {
       std::cout << e << " ";
    }
    std::cout << std::endl;
}

int not_zero(int& a){
    if (a >= 0){
        return a;
    } else{
        return 0;
    }
}

int main(){
    int a,b;
    std::vector<int> v1(11);
	std::iota(std::begin(v1), std::end(v1), 0);
    std::cout << "Input 2 numbers: ";
    std::cin >> a >> b;
    v1.push_back(a);
    v1.push_back(b);
    std::random_device rd;
    std::mt19937 gen(rd());
    auto distribution = std::uniform_int_distribution<>(1, 10);
    std::shuffle(v1.begin(), v1.end(), gen);
    v1.erase(std::unique(v1.begin(), v1.end()), v1.end());
    std::cout <<  "Odd elements: " << std::count_if(v1.begin(), v1.end(), [](int i){return i % 2 != 0;}) << std::endl;
    std::sort(v1.begin(), v1.end(), [](int a, int b) {
        return a > b;
    });
    std::cout << "Max: " << v1.front() << "; Min: " << v1.back() << std::endl; 
    std::transform(v1.begin(), v1.end(), v1.begin(), [](int i)  -> int {return i*i;});
    std::vector<int> v2(v1.size());
    std::generate_n(v2.begin(), v1.size(), gen);
    std::cout << "Sum: " << std::accumulate(v2.begin(), v2.end(), 0) << std::endl;
    v2[0] = 1;
    v2[1] = 1;
    std::vector<int> v3(v1.size());
    for(int i = 0; i < v1.size(); ++i){
        v3[i] = v1[i] - v2[i];
        if(v3[i] < 0){
            v3[i] = 0;
        }
    }
    v3.erase(std::remove(v3.begin(), v3.end(), 0), v3.end());
    std::reverse(std::begin(v3), std::end(v3));
    std::sort(v3.begin(), v3.end(), [](int a, int b) {
        return a > b;
    });
    std::cout << "3 Max: " << v3[0] << " " << v3[1] << " " << v3[2] << std::endl;
    std::sort(v1.begin(), v1.begin());
    std::sort(v2.begin(), v2.begin());
    std::vector<int> v4 = v1;
    v4.insert(v4.end(), v2.begin(), v2.end());
    std::sort(v4.begin(), v4.end());
    auto upper = std::upper_bound(v4.begin(), v4.end(), 1);
    auto lower = std::lower_bound(v4.begin(), v4.end(), 1);
    auto distance = std::distance(lower, upper);
    std::cout << "Range of 1: " << distance << std::endl;
    print(v1);
    print(v2);
    print(v3);
    print(v4);
}