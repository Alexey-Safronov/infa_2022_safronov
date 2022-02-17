#include <iostream>
#include <chrono>
#include <cmath>

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
		if (paused){
			int res = time.count();
		} else{
			int res = (time + gap()).count();
		}
		std::cout << "Time from start is: " << (time + gap()).count() << std::endl;
			
	}
	void stop(){
		paused = true;
		time += gap();

	}
	void start(){
		paused = false;
		time_mark = steady_clock::now();
	}
};
					
	int main(){
		Timer<std::chrono::milliseconds> timer;    
		int square;
		for(unsigned i = 0; i < 10000000; ++i){
			square = i*i;	
		}
		timer.stop();
		timer.start();
		
	}
	
