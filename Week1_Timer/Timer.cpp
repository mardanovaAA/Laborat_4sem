#include <iostream>
#include <cmath>

#include <chrono>


//Example of using variadic templates
template <typename U>
void print (U t){
	std::cout << t << " ";
}

template <typename... Types, typename Firstype>
void print(Firstype firstype, Types... args) {
	std::cout << firstype << " ";
	print(args...);
}

template <typename U>
class Timer{
	private:
		double current_duration;
		std::chrono::steady_clock::time_point start_period;

		bool flag_pause = false;

	public:
		Timer(): start_period(std::chrono::steady_clock::now()){};

		void pause(){
			//checking if timer has been already stopped before
			if (!flag_pause){
				flag_pause = true;
				current_duration += std::chrono::duration_cast<U>(std::chrono::steady_clock::now() - start_period).count();
			}
		};

		void contin(){ 
			if (flag_pause){
				flag_pause = false;
				start_period = std::chrono::steady_clock::now();
			}
		}


		~Timer() {
			if (!flag_pause){
				current_duration += std::chrono::duration_cast<U>(std::chrono::steady_clock::now() - start_period).count();
			}
			std::cout << current_duration << std::endl;
		}
};

int main(){

	double result = 0;
	{
		Timer<std::chrono::milliseconds> T;
		for (int i = 0; i < 100000; i++){
			result += cos(i);
		}
	}

	std::cout << "Result is " << result << std::endl;


	return 0;

}