#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>
#include <filesystem>

std::vector<std::string> split(const std::string &str, char delimiter = ' ');
std::filesystem::path  getPath(const std::string& base_dir, const std::vector<std::string>& relative_path);
std::string getExecutableDir();
void clearScreen();
void pauseScreen();
void clearInputBuffer();

#endif // UTILITY_H
