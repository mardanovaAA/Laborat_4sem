#include <iostream>
#include <map>
#include <string>
#include <random>


class Phone_directory{
	private:
		std::multimap<std::string, std::string> data;

	public:
		Phone_directory(): data(){};

		Phone_directory(std::string name, std::string number){
			data.insert(std::make_pair(name, number));
		};

		friend std::ostream& operator<< (std::ostream& out, const Phone_directory& Dir);

		void add_person(std::string name, std::string number){
			data.insert(std::make_pair(name, number));
		};

		void delete_person(std::string name, std::string number){
			auto range = data.equal_range(name);

			for (auto i = range.first; i != range.second;){
				if (i->second == number){
					i = data.erase(i);
				} else {
					++i;
				}
			}
		};

		void display_name(std::string name){
			auto range = data.equal_range(name);

			for (auto i = range.first; i != range.second; ++i){
				std::cout << i->first << " " << i->second << "\n";
			}
		};

		void delete_name(std::string name){
			data.erase(name);
		};


		std::pair<std::string, std::string> random_person(){
			if (data.size() >= 1){
				std::random_device rd;
				std::mt19937 gen(rd()); 
	 			std::uniform_int_distribution<> distribution(0, data.size());

	 			return *std::next(std::begin(data), distribution(gen));
	 		} else {
	 			return std::make_pair<std::string, std::string>("Empty", "Empty");
	 		}

		}; 

		void display_n_random_people (int N){
			if (data.size() >= 1){
				std::random_device rd;
				std::mt19937 gen(rd()); 
		 		std::uniform_int_distribution<> distribution(0, data.size());

				for (int i = 1; i <= N; i++){
		 			auto pair = std::next(std::begin(data), distribution(gen));

		 			std::cout << pair->first << " " << pair->second << std::endl;
		 		}

	 		} else {
	 			std::cout << "Empty\n";
	 		}
		}




};

std::ostream& operator<< (std::ostream& out, const Phone_directory& Dir){
		for (const auto& [name, number]: Dir.data){
			out << name << " " << number << "\n";
		}
	return out;
};

int main(){

	Phone_directory dir;

	dir.add_person("A", "1234");
	dir.add_person("D", "564");
	dir.add_person("A", "2143");
	dir.add_person("A", "1234");

	dir.display_n_random_people(3);


	return 0;
}