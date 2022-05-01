#include <iostream>
#include <thread>
#include <algorithm>
#include <numeric>
#include <vector>
#include <mutex>

std::mutex mutex;

template <typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T& result){
	mutex.lock();
	result += std::accumulate(first, last, 0);
	mutex.unlock();
}

template <typename Iterator, typename T>
void parallel_accumulate(Iterator first, Iterator last, T& result, int num_workers = std::thread::hardware_concurrency()){
	auto length = std::distance(first, last);
	if ((length < 32) || (num_workers <= 1)){
		result = std::accumulate(first, last, 0);
	}

	auto length_per_thread = length / (num_workers - 1);

	std::vector<std::thread> threads;

	for (auto i = 0; i < num_workers - 1; i++){
		auto beginning = std::next(first, i * length_per_thread);
		auto ending = std::next(first, (i+1) * length_per_thread);
		threads.push_back(std::thread(accumulate_block<Iterator, T>, beginning, ending, std::ref(result)));
	}

	mutex.lock();
	result += std::accumulate(std::next(first, (num_workers - 1) * length_per_thread), last, 0);
	mutex.unlock();

	std::for_each(std::begin(threads), std::end(threads), std::mem_fun_ref(&std::thread::join));

}



int main(){
	std::vector<int> sequence(100);
	std::iota(std::begin(sequence), std::end(sequence), 1);
	int sum = 0;
	parallel_accumulate(std::begin(sequence), std::end(sequence), sum);

	std::cout << sum << std::endl;
}
