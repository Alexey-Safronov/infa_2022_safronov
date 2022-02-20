// Result: containers sort speed in descending order: array, vector, deque, list, forward_list
#include <iostream>
#include <deque>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#include <chrono>
#include <random>
#include <iterator>
#include <list>
#include <forward_list>

using namespace std::chrono;

template<typename X>
class Timer{
	steady_clock::time_point time_mark;
	bool paused;
	X time;
	public:
	X gap(){
		return duration_cast<X>(steady_clock::now() - time_mark);
	}
	Timer(): time(0), time_mark(steady_clock::now()), paused(false) {}
	~Timer(){
	}

	void stop(){
		if (paused){
			std::cout <<  time.count();
		} else{
			std::cout <<  (time + gap()).count();
		}
		paused = true;
	}
	void start(){
		paused = false;

		time_mark = steady_clock::now();
	}
};
 
int main(){
	std::vector<int> v(1e6);
	std::deque<int> d(1e6);
	std::array<int, 1000000> a;
	std::list<int> l(1e6);
	std::forward_list<int> fl(1e6);
	auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
	auto generator = std::mt19937(seed); //mersene twister
	auto distribution = std::uniform_int_distribution<>(1, 10);
	std::cout << std::endl;
	for(auto i = 0; i < 1e6; i++){
		v.push_back(distribution(generator));
	}
	for(auto i = 0; i < 1e6; i++){
		d.push_back(distribution(generator));
	}
	for(auto i = 0; i < 1000000; i++){
		a[i] = distribution(generator);
	}
	for(auto i = 0; i < 1e6; i++){
		l.push_back(distribution(generator));
	}
	for(auto i = 0; i < 1e6; i++){
		fl.push_front(distribution(generator));
	}
	Timer<std::chrono::milliseconds> timer;   
	
	std::cout << "*Time in milliseconds*" << std::endl;
	std::sort(v.begin(), v.end());
	std::cout << "Vector sort time is: ";
	timer.stop();	
	std::cout << std::endl;
	
	
	timer.start();
	std::sort(d.begin(), d.end());	
	std::cout << "Deque sort time is: ";
	timer.stop();
	std::cout << std::endl;
	
	timer.start();
	std::sort(a.begin(), a.end());
	std::cout << "Array sort time is: ";
	timer.stop();
	std::cout << std::endl;

	timer.start();
	l.sort();
	std::cout << "List sort time is: ";
	timer.stop();
	std::cout << std::endl;

	timer.start();
	fl.sort();
	std::cout << "Forward list sort time is: ";
	timer.stop();	
	std::cout << std::endl;


	//std::deque<int> random_numbers;
	//std::generate_n(std::front_inserter(random_numbers), 11, 
	//		[generator, distribution](){
	//		return distribution(generator);
	//		});
	//std::cout << random_numbers << std::endl;



}
