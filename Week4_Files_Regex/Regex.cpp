#include <iostream>
#include <regex>
#include <vector>
#include <iterator>
#include <fstream>


std::vector<std::string> search (const std::string& str, const std::regex& pattern){
	auto words_begin = std::sregex_iterator(std::begin(str), std::end(str), pattern);
	auto words_end = std::sregex_iterator();

	std::vector<std::string> res;

	std::transform(words_begin, words_end, std::back_inserter(res), [](auto el){return el.str();});

	return res;
}

template <typename A>
std::ostream& operator<< (std::ostream& out, std::vector<A> vec2print){
	for (auto i: vec2print){
		out << i << " ";
	}
	out << "\n";

	return out;
} 

int main(){

	std::regex pattern_data (R"((^|\s)[1-9]{1}[0-9]{0,3}\.((0[1-9]{1})|(1[0-2]{1})|([1-9]{1}))\.((0[1-9]{1})|([1-2]{1}[0-9]{1})|(3[0-1]{1})|([1-9]{1}))(\s|\.))");

	std::regex pattern_time (R"((^|\s)(([0-1]{1}[0-9]{1})|(2[0-3]{1}))\.[0-5]{1}[0-9]{1}\.[0-5]{1}[0-9]{1}(\s|\.))");
	
	std::string text = "The invention of the Internet in 1969.11.28 became an 12.45.16 important breakthrough of the XX century.\n" 
						"Since that time millions of people 968.01.20 are using the internet everyday and can’t imagine their lives without it.\n" 
						"This global 24.00.00 network provides 2002.13.01 huge opportunities for communication.\n";

	std::vector<std::string> time = search(text, pattern_time);

	std::vector<std::string> data = search(text, pattern_data);

	std::cout << "Found time: " << time;

	std::cout << "Found data: " << data;

	return 0;
}