#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include <filesystem>

using nlohmann::json;

struct Person{
	std::string name;
	std::string surname;
	int age;
	int height;
	int weight;

	friend std::istream& operator>> (std::istream& in, const Person& pers); 
};

json create_object(Person& pers){
	json object;
	object["Name"] = pers.name;
	object["Surname"] = pers.surname;
	object["Age"] = pers.age;
	object["Height"] = pers.height;
	object["Weight"] = pers.weight;

	return object;
}


std::istream& operator>> (std::istream& in, Person& pers){
	std::cout << "Enter personal information about the person: \nName Surname \nAge \nHeight \nWeight \n";
	in >> pers.name;
	in >> pers.surname;
	in >> pers.age;
	in >> pers.height;
	in >> pers.weight;

	return in;
};


int main(){

	std::filesystem::create_directory("People");

	std::filesystem::path directory_path (std::filesystem::current_path()/"People");

	std::cout << "How many people do you want to enter?" << std::endl;
	int N;
	std::cin >> N; 

	for (int i = 0; i < N; i++){
		Person pers;
		std::cin >> pers;
		json Obj = create_object(pers);

		std::filesystem::path file_path = directory_path / (pers.name + "_" + pers.surname + ".txt");
		std::ofstream out;
		out.open(file_path);
		file_path.clear();

		out << Obj.dump(4);

		out.close(); 
	
	}

	return 0;
}