#include "utility.h"
#include <limits>
#include <sstream>
#include "iostream"


std::vector<std::string> split(const std::string &str)
{
    std::istringstream iss(str);
    std::vector<std::string> res;
    std::string cur;
    while (iss >> cur)
    {
        res.emplace_back(cur);
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