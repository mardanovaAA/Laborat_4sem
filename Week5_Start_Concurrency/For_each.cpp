#include <iostream>
#include <future>
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <vector>
#include <iterator>


template <typename Iterator, typename T>
void block_paral_for_each(Iterator first, Iterator last, T func){
	std::for_each(first, last, func);
}


template <typename Iterator, typename T>
void paral_for_each(Iterator first, Iterator last, T func){
	auto length = std::distance(first, last);
	if (length < 32){
		std::for_each(first, last, func);
	} else {
		
		int num_workers = std::thread::hardware_concurrency();
		auto length_per_thread = length / (num_workers-1);

		std::vector<std::future<void>> futures;

		for (auto i = 0; i < num_workers - 1; i++){
			auto beginning = std::next(first, i * length_per_thread);
			auto ending = std::next(first, (i+1) * length_per_thread);
			futures.push_back(std::async(std::launch::async, block_paral_for_each<Iterator, T>, beginning, ending, func));
		}

		std::for_each(std::next(first, (num_workers - 1) * length_per_thread), last, func);

		std::for_each(std::begin(futures), std::end(futures), std::mem_fun_ref(&std::future<void>::get));
	}

}


int main(){
	std::vector<int> sequence(100);
	std::iota(std::begin(sequence), std::end(sequence), 1);

	paral_for_each(std::begin(sequence), std::end(sequence), [](int& n){++n;});

	std::copy(std::begin(sequence), std::end(sequence), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl;



}