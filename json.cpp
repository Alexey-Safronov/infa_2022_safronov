#include <iostream>
#include "json.hpp"
#include <string>
#include <filesystem>
#include <fstream>

using nlohmann::json;
namespace fs = std::filesystem;

class Human
{
	public:
	 std::string name;
	 int height;
	 double weight;
 
	friend std::istream& operator>>(std::istream &, Human&);
};

std::istream& operator>>(std::istream &in, Human& h)
{
	in >> h.name >> h.height >> h.weight;
	return in;
}

int main() {
	Human h1, h2;
	std::string s1;
	std::cin >> h1 >> h2;
	json j1,j2;
    j1["Name"] = h1.name;
	j1["Height"] = h1.height;
	j1["Weight"] = h1.weight;
	j2["Name"] = h2.name;
	j2["Height"] = h2.height;
	j2["Weight"] = h2.weight;
	fs::path path{ "C:\\TestingFolder" }; 
	fs::create_directory(path/ "1");
	fs::path path_1 = path/ "1";
    path_1 /= j1["Name"]; 
	std::ofstream ofs_1(path_1); 
	ofs_1 << j1.dump(4);
	fs::create_directory(path/ "2");
	fs::path path_2 = path/ "2";
    path_2 /= j2["Name"]; 
	std::ofstream ofs_2(path_2); 
	ofs_2 << j2.dump(4);
	ofs_1.close(); 
	ofs_2.close();
}
	
