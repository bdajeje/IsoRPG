#include "file.hpp"

#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "utils/exception.hpp"

namespace utils {
namespace files {

std::string read( const std::string& filepath )
{
  std::ifstream file(filepath.c_str());
  if( !file.is_open() )
    throw utils::Exception("Cannot read file: " + filepath);

  // Get length of file
  file.seekg(0, file.end);
  const int length = file.tellg();
  file.seekg(0, file.beg);

  // If file content is empty, exit
  if( length < 1 )
    return {};

  // Read the file
  std::string result;
  result.resize( length );
  file.read(&result[0], length);

  // Close the file and return good read
  file.close();

  return result;
}

bool create( const std::string& filepath, const std::string& content, bool override )
{
  if( !override && exists(filepath) )
    return false;

  // Try to open the file
  std::ofstream new_file(filepath, std::ios::trunc);
  if( !new_file.is_open() )
    return false;

  // Write content into
  new_file << content;

  // Closing file
  new_file.close();

  return true;
}

std::string sanitize(const std::string& input)
{
  return std::regex_replace(input, std::regex{"[^a-z^A-Z^0-9]"}, "_");
}

std::vector<std::string> lines(const std::string& filepath, size_t nbr_lines)
{
  std::string content = read(filepath);
  std::vector<std::string> lines;
  lines.reserve(nbr_lines);
  boost::algorithm::split(lines, content, boost::is_any_of("\n"));
  return lines;
}

} // namespace files
} // namespace utils


