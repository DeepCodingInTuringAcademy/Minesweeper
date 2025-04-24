#include <sstream>
#include "../include/utility.h"


std::vector<std::string> split(const std::string &str) {
    std::istringstream iss(str);
    std::vector<std::string> res;
    std::string cur;
    while (iss >> cur){
        res.emplace_back(cur);
    }
    return res;
}
