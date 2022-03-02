#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iterator>

std::ostream& operator<<(std::ostream& out, std::vector<int> vec){
	std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<int>(out, " "));
	return out;
}

int main(){

	std::vector<int> sequence_1 (10);

	//Creating sequence 1 of numbers from 1 to 10;
	std::iota(std::begin(sequence_1), std::end(sequence_1), 1);


	//Add some numbers to the end of sequence_1 from cin;
	std::cout << "How many numbers do you want to enter?\n";

	{
		int N;
		std::cin >> N;
		for (int i = 0; i != N; i++){
			int number;
			std::cin >> number;
			sequence_1.push_back(number);
		}
	}

	
	//Mix elements of sequence_1 randomly;	
	std::random_device rd;
	std::mt19937 gen(rd());

	std::shuffle(std::begin(sequence_1), std::end(sequence_1), gen);


	//Delete duplicates from sequence_1;
	std::sort(std::begin(sequence_1), std::end(sequence_1));
	auto it = std::unique(std::begin(sequence_1), std::end(sequence_1));
	sequence_1.erase(it, std::end(sequence_1));

	//Count the number of odd numbers in sequence_1;
	int odd_number = std::count_if(std::begin(sequence_1), std::end(sequence_1), [](int num){return (num % 2 == 1);});
	std::cout << "The number of odd elements: " << odd_number << std::endl;

	//Determine the minimum and maximum values in sequence_1;
	auto min_elem_iter = std::min_element(std::begin(sequence_1), std::end(sequence_1));
	auto max_elem_iter = std::max_element(std::begin(sequence_1), std::end(sequence_1));
	std::cout << "Max element is " << *max_elem_iter << "\nMin element is " << *min_elem_iter << std::endl;

	//Find at least one prime number in sequence_1;
	auto is_prime = [](int number){
		bool flag = true;
		for (int i = 2; i <= (int)(sqrt(number)); i++){
			if (number % i == 0) flag = false;
		}
		return (number > 1) ? flag : false;
	};
	auto prime_number = std::find_if(std::begin(sequence_1), std::end(sequence_1), is_prime);
	if (prime_number != std::end(sequence_1)){
		std::cout << "One prime number from sequence_1: " << *prime_number << std::endl;
	} else {
		std::cout << "No prime numbers\n";
	}

	//Replace all the numbers in sequnce_1 with their squares;
	std::transform(std::begin(sequence_1), std::end(sequence_1), std::begin(sequence_1), [](int number){return number*number;});

	//Create a sequence_2 of (size(sequence_1)) random numbers;
	std::uniform_int_distribution<> distribution (1, 150);
	std::vector<int> sequence_2;
	std::generate_n(std::back_inserter(sequence_2), sequence_1.size(), [&distribution, &gen](){return distribution(gen);});

	//Calculate the sum of the numbers in sequence_2;
	int sum = std::accumulate(std::begin(sequence_2), std::end(sequence_2), 0);
	std::cout << "The sum of sequence_2 is " << sum << std::endl;

	//Replace the first 3 numbers in sequence_2 with the 1;
	std::fill_n(std::begin(sequence_2), 3, 1);

	//Create a sequence_3 as the difference between sequence_1 and sequence_2;
	std::vector<int> sequence_3;
	std::transform(std::begin(sequence_1), std::end(sequence_1), std::begin(sequence_2), std::back_inserter(sequence_3), 
					[](int first, int second){return first - second;});

	for (auto i: sequence_3){
		std::cout << i << " ";
	}
	std::cout << std::endl;

	//Replace each negative element in the sequence_3 with 0;
	std::transform(std::begin(sequence_3), std::end(sequence_3), std::begin(sequence_3), 
					[](int number){return (number < 0)? 0 : number;});

	//Delete all null elements from the sequence_3;
	auto it_nulls = std::remove(std::begin(sequence_3), std::end(sequence_3), 0);
	sequence_3.erase(it_nulls, std::end(sequence_3));

	//Change the order of the elements in the sequence_3 to reverse;
	std::reverse(sequence_3.begin(), sequence_3.end());

	//Determine the top 3 largest elements in the PP;
	if (sequence_3.size() >= 1){
		std::nth_element(sequence_3.begin(), std::prev(sequence_3.end()), sequence_3.end());
		std::cout << "The greatest element is " << *std::prev(sequence_3.end()) << std::endl;
		if (sequence_3.size() >= 2){
			std::nth_element(sequence_3.begin(), std::prev(sequence_3.end(), 2), sequence_3.end());
			std::cout << "The second greatest element is " << *std::prev(sequence_3.end(), 2) << std::endl;
			if (sequence_3.size() >= 3){
				std::nth_element(sequence_3.begin(), std::prev(sequence_3.end(), 3), sequence_3.end());
				std::cout << "The third greatest element is " << *std::prev(sequence_3.end(), 3) << std::endl;
			}
		}
	}

	//Sort sequence_1 and sequence_2;
	std::sort(std::begin(sequence_1), std::end(sequence_1));
	std::sort(std::begin(sequence_2), std::end(sequence_2));

	//Create a sequence_4 as a merge of sequence_1 and sequence_2;
	std::vector<int> sequence_4;
	std::merge(std::begin(sequence_1), std::end(sequence_1), std::begin(sequence_2), std::end(sequence_2), std::back_inserter(sequence_4));

	//Determine the range for the insertion of 1 in sequence_4;
	auto pair_it = std::equal_range(sequence_4.begin(), sequence_4.end(), 1);
	std::cout << "You can insert 1 to sequence_4 on the place from " <<
		std::distance(std::begin(sequence_4), pair_it.first) << " to " << std::distance(std::begin(sequence_4), pair_it.second) << std::endl;


	//Output all sequences in cout;
	std::cout << "sequence_1: " << sequence_1 << std::endl;
	std::cout << "sequence_2: " << sequence_2 << std::endl;
	std::cout << "sequence_3: " << sequence_3 << std::endl;
	std::cout << "sequence_4: " << sequence_4 << std::endl;

	return 0;
}