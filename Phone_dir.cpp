#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <iterator>

void print_map(const std::map<std::string, int>& m)
{
  for (const auto& n : m) {
      std::cout << n.first << "  " << n.second << "; ";
  }
}

std::string random_name(std::size_t length)
{
    const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_name;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_name += CHARACTERS[distribution(generator)];
    }

    return random_name;
}

int random_number()
{

    std::random_device random_device;
    std::mt19937 generator(random_device());
    auto distribution = std::uniform_int_distribution<>(0, 99999);
	
    return distribution(generator) + 8900000;
}

int main(){
	std::vector<int> number;
	std::map<std::string, int> m; 
	std::string i_name;
	std::string search_name;
	int i_number;

	for (auto i = 0; i < 5; ++i){
		i_name = random_name(10);
		i_number = random_number();
		number.push_back(i_number);
		m.insert(std::make_pair(i_name, i_number));	
	}
	
	std::cout << "1) Sorted by name directory: ";
	print_map(m);
	std::cout << std::endl;
	std::cout << "2) Random number: " << number[rand() % 10]; 
	std::cout << std::endl; 
	std::cout << "Enter the name: ";
	std::cin >> search_name;
	std::cout << "3) He's number: " << m[search_name] << std::endl;	
		
}
