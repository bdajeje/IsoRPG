#ifndef JENGINE_DIRECTORY_HPP
#define JENGINE_DIRECTORY_HPP

#include <string>
#include <vector>

namespace utils {

// Ensure '/' and the end of directory string
std::string ensureDirectoryEnd(const std::string& path);

/*! List files under directory */
std::vector<std::string> listFiles(const std::string& directory_path, const std::string& regex_str, bool sort = true);
std::vector<std::string> listDirs(const std::string& directory_path, const std::string& regex_str, bool sort = true);

std::string dir(const std::string& filepath);

void mkdir(const std::string& path);

}

#endif // JENGINE_DIRECTORY_HPP
