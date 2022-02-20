#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

#define TYPE(N) std::forward_list<int>


 int main(){

 	std::ofstream out;
 	out.open("forward_list.txt");

 	std::mt19937 gen; //with the fixed seed. 
 	std::uniform_int_distribution<> distribution(1, 500);


 	{
 		TYPE(10) container {};

 		int size = 10;

 		std::generate_n(std::front_inserter(container), size, [&distribution, &gen](){return distribution(gen);});

 		auto start = std::chrono::steady_clock::now();

 		container.sort();

 		out << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << " " << size << "\n";

 	}

 	{
 		TYPE(100) container {};

 		int size = 100;

 		std::generate_n(std::front_inserter(container), size, [&distribution, &gen](){return distribution(gen);});

 		auto start = std::chrono::steady_clock::now();

 		container.sort();

 		out << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << " " << size << "\n";

 	}

 	{
 		TYPE(1000) container {};

 		int size = 1000;

 		std::generate_n(std::front_inserter(container), size, [&distribution, &gen](){return distribution(gen);});

 		auto start = std::chrono::steady_clock::now();

 		container.sort();

 		out << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << " " << size << "\n";

 	}

 	{
 		TYPE(10000) container {};

 		int size = 10000;

 		std::generate_n(std::front_inserter(container), size, [&distribution, &gen](){return distribution(gen);});

 		auto start = std::chrono::steady_clock::now();

 		container.sort();

 		out << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << " " << size << "\n";

 	}

 	{
 		TYPE(100000) container {};

 		int size = 100000;

 		std::generate_n(std::front_inserter(container), size, [&distribution, &gen](){return distribution(gen);});

 		auto start = std::chrono::steady_clock::now();

 		container.sort();

 		out << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << " " << size << "\n";

 	}


 	out.close();





 	return 0;
 }

