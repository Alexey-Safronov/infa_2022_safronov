#include <iostream>
#include <iterator>
#include <regex>
#include <vector>

std::vector<std::string> search(const std::regex& pattern,
                                const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text),
                                      std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x){
        return x.str();
    });
    return results;
}

int main() {
	// format: YYYY.MM.DD 
	std::regex pattern(R"([0-9]{4}\.([0][1-9]|[0][0-2])\.([0][1-9]|[1-2][0-9]|[3][0-1]))");
	std::string test_sequence = "4125.01.30"
								  "2022.03.08"
								  "2003.02.26"
								  "1999.13.22";
    auto result = search(pattern, test_sequence);
    std::copy(std::begin(result), std::end(result), std::ostream_iterator<std::string>(std::cout, " "));
}
