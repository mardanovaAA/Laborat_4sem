#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <fstream>

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


		double print(){
			if (!flag_pause){
				current_duration += std::chrono::duration_cast<U>(std::chrono::steady_clock::now() - start_period).count();
			}
			return current_duration;
		}
};


template <typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, T& result){
	result = std::accumulate(first, last, init);
}

template <typename Iterator, typename T>
T accumulate (Iterator first, Iterator last, T init, int num_workers){
	auto length = std::distance(first, last);
	if ((length < 32) || (num_workers <= 1)){
		return std::accumulate(first, last, init);
	}

	auto length_per_thread = length / (num_workers - 1);

	std::vector<std::thread> threads;
	std::vector<T> results(num_workers - 1);

	for (auto i = 0; i < num_workers - 1; i++){
		auto beginning = std::next(first, i * length_per_thread);
		auto ending = std::next(first, (i+1) * length_per_thread);
		threads.push_back(std::thread(accumulate_block<Iterator, T>, beginning, ending, 0, std::ref(results[i])));
	}

	auto main_res = std::accumulate(std::next(first, (num_workers - 1) * length_per_thread), last, init);

	std::for_each(std::begin(threads), std::end(threads), std::mem_fun_ref(&std::thread::join));


	return std::accumulate(std::begin(results), std::end(results), main_res);

}



int main(){

	std::vector<int> sequence(100000);
	std::iota(std::begin(sequence), std::end(sequence), 1);

	std::ofstream out;
	out.open("Time.txt");

	for (int i = 1; i < 100; i++){
		Timer<std::chrono::microseconds> T;
		auto res = accumulate(std::begin(sequence), std::end(sequence), 0, i);
		T.pause();
		out << i << " " << T.print() << "\n";  

	}



	return 0;
}