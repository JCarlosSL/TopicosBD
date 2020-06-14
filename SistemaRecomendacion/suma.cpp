#include <numeric>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main()
{
    const std::map<std::string,int> bla = {{"a", 1}, {"b", 3},{"c",4}};
    const int result = std::accumulate(bla.begin(), bla.end(),1,
					[](const int previous, const auto & p) 
					{return previous * p.second; });
    std::cout << result << "\n";
}
