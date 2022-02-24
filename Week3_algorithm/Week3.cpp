#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <deque>

template <typename A>
std::ostream& operator<< (std::ostream& out, const std::vector<A>& container){
	out << "[";
	std::copy(std::begin(container), std::prev(std::end(container)), std::ostream_iterator<A>(out, ", "));
	out << *std::prev(std::end(container)) << "]\n";
	return out;
}

template <typename A>
std::ostream& operator<< (std::ostream& out, const std::deque<A>& container){
	out << "[";
	std::copy(std::begin(container), std::prev(std::end(container)), std::ostream_iterator<A>(out, ", "));
	out << *std::prev(std::end(container)) << "]\n";
	return out;
}

#define RANGE(container) std::begin(container), std::end(container)


int main(){
	// std::vector<int> source {42, 33, 255, -54};
	// std::vector<int> dest;

	// std::copy(std::begin(source), std::end(source), std::back_inserter(dest));
	
	// std::copy(std::begin(dest), std::end(dest), std::ostream_iterator<int>(std::cout, " "));
	// std::cout << std::endl;

	// auto gcd = std::gcd(45, 25);
	// auto lcm = std::lcm(45, 25);

	// std::cout << gcd << std::endl;
	// std::cout << lcm << std::endl;

	// std::cout << std::boolalpha << (gcd * lcm == 45 * 25) << std::endl;

	// std::vector<int> sequence (10);
	// std::iota(std::begin(sequence), std::end(sequence), 12);
	// std::cout << sequence;

	// auto sum = std::accumulate(std::begin(sequence), std::end(sequence), 0);
	// auto product = std::accumulate(std::begin(sequence), std::end(sequence), 1, [](auto lhs, auto rhs){ return lhs * rhs;});
	// std::cout << "Sum: " << sum << std::endl;
	// std::cout << "Product: " << product << std::endl;

	// std::vector<int> reversed_sequence;
	// std::reverse_copy(std::begin(sequence), std::end(sequence), std::back_inserter(reversed_sequence));

	// auto inner_product = std::inner_product(std::begin(sequence), std::end(sequence), std::begin(reversed_sequence), 0);

	// std::cout << reversed_sequence;
	// std::cout << inner_product << std::endl;

	// std::reverse(std::begin(reversed_sequence), std::end(reversed_sequence));
	// std::cout << "sequence reversed reversed " << reversed_sequence;

	// std::vector<int> transformed;
	// std::transform(std::begin(sequence), std::end(sequence), std::back_inserter(transformed), [](auto el){return el*el;});
	// std::cout << "The square is " << transformed;

	// std::vector<int> products;

	// std::transform(std::begin(sequence), std::end(sequence), std::begin(reversed_sequence), std::back_inserter(products), 
	// 				[](auto lhs, auto rhs){return rhs * lhs;});
	// std::cout << products;

	// auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
	// // auto generator = std::default_random_engine(seed);
	// auto generator = std::mt19937(seed); //mersenne twister;
	// auto distribution = std::uniform_int_distribution<int>(1, 10);

	// for (auto i = 0; i < 10; i++){
	// 	std::cout << distribution(generator) << " ";
	// }
	// std::cout << std::endl;

	// std::deque<int> random_numbers;
	// std::generate_n(std::front_inserter(random_numbers), 10, [&generator, &distribution](){return distribution(generator);});
	// std::cout << random_numbers;

	// auto nth_iter = std::next(std::begin(random_numbers), random_numbers.size() / 2);
	// std::nth_element(std::begin(random_numbers), nth_iter, std::end(random_numbers));

	// std::cout << random_numbers;

	// std::nth_element(std::begin(random_numbers), std::next(std::begin(random_numbers)), std::end(random_numbers), 
	// 	[](auto lhs, auto rhs){return lhs > rhs;});
	// std::cout << random_numbers;

	std::vector<int> same_numbers {1, 1, 3, 42, 1, 3, 5, 3, 1};
	auto to_delete = std::unique(RANGE(same_numbers));
	same_numbers.erase(to_delete, std::end(same_numbers));
	std::cout << same_numbers << std::endl;

	std::vector<int> copied;
	std::copy_if(RANGE(same_numbers), std::back_inserter((copied)), [](auto elem){ return elem > 4;});

	std::cout << copied;

	return 0;

}