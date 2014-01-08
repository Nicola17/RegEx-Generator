#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> 

std::string generateRegExp_Recursive(const std::vector<std::string>& items, int charAt, int begin, int end){
	std::stringstream ss;

	bool optional(false);
	int nChar(0);

	int b = begin;
	while(b < end){
		if(items[b].size() <= charAt){
			++b;
			optional = true;
			continue;
		}

		const char c(items[b][charAt]);
		if(nChar > 0)
			ss << "|";
		ss << c;
		nChar++;

		int e(b+1);
		while(e < end && items[e][charAt] == c)
			e++;

		ss << generateRegExp_Recursive(items,charAt+1,b,e);
		b = e;
	}

	std::stringstream final_ss;
	if(nChar > 0){
		if(optional)
			final_ss << "(" << ss.str() << ")+";
		else{
			if(nChar == 1)
				return ss.str();
			final_ss << "(" << ss.str() << ")";
		}
	}

	return final_ss.str();
}

std::string generateRegExp(const std::vector<std::string>& items){
	return generateRegExp_Recursive(items, 0, 0, items.size());
}

int main(int argc, char *argv[]){
	if(argc!=2){
        std::cout << "Wrong number of parameters";
        return 1;
    }

	std::ifstream file(argv[1]);

	std::string line;
	std::vector<std::string> items;

	while(std::getline(file, line))
		items.push_back(line);
	
	std::sort(items.begin(), items.end()); 

	std::cout << generateRegExp(items);
	return 0;
}
