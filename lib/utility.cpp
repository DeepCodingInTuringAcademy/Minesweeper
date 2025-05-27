#include "utility.h"
#include <limits>
#include <sstream>
#include "iostream"


std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::filesystem::path getPath(const std::string &base_dir, const std::vector<std::string>& relative_path) {
    std::filesystem::path src_path = base_dir;
    std::filesystem::path res = src_path.parent_path();
    for (const auto& path: relative_path) {
        res /= path;
    }
    return res;
}

void clearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls"); // Windows
#else
    system("clear"); // Linux
#endif
}

void pauseScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    system("pause"); // 在Windows系统中暂停
#else
    system("read -p 'Press any key to continue...' -n 1 -s"); // 在Unix/Linux系统中暂停
#endif
}

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}