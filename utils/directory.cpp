#include "directory.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "utils/exception.hpp"

namespace utils {

std::string ensureDirectoryEnd(const std::string& path)
{
  if(!boost::algorithm::ends_with(path, "/"))
    return path + '/';

  return path;
}

std::vector<std::string> listFiles(const std::string& directory_path, const std::string& regex_str, bool sort)
{
  namespace fs = boost::filesystem;

  std::vector<std::string> results;

  // Check given path
  if( !fs::exists( directory_path ) ||
      !fs::is_directory( directory_path ) )
    return results;

  // Create regex
  const boost::regex regex {regex_str};

  // List files
  fs::directory_iterator end_iter;
  for( fs::directory_iterator dir_itr( directory_path ); dir_itr != end_iter; ++dir_itr )
  {
    if( fs::is_regular_file( dir_itr->status() ) &&
        boost::regex_match( dir_itr->path().filename().string(), regex ))
      results.emplace_back( dir_itr->path().filename().string() );
  }

  // Alphabetically sort
  if(sort)
    std::sort( results.begin(), results.end() );

  return results;
}

std::vector<std::string> listDirs(const std::string& directory_path, const std::string& regex_str, bool sort)
{
  namespace fs = boost::filesystem;

  std::vector<std::string> results;

  // Check given path
  if( !fs::exists( directory_path ) ||
      !fs::is_directory( directory_path ) )
    return results;

  // Create regex
  const boost::regex regex {regex_str};

  // List files
  fs::directory_iterator end_iter;
  for( fs::directory_iterator dir_itr( directory_path ); dir_itr != end_iter; ++dir_itr )
  {
    if( fs::is_directory( dir_itr->status() ) &&
        boost::regex_match( dir_itr->path().filename().string(), regex ))
      results.emplace_back( dir_itr->path().filename().string() );
  }

  // Alphabetically sort
  if(sort)
    std::sort( results.begin(), results.end() );

  return results;
}

std::string dir(const std::string& filepath)
{
  const size_t index = filepath.find_last_of('/');
  if(index == std::string::npos)
    return {};

  return filepath.substr(0, index);
}

void mkdir(const std::string& path)
{
  boost::filesystem::path dir(path);

  if(boost::filesystem::is_directory(path))
    return;

  if(!boost::filesystem::create_directory(dir))
    throw utils::Exception("Can't mkdir: " + path);
}

} // utils
