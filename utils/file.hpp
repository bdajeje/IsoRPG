#ifndef UTILS_FILE_HPP
#define UTILS_FILE_HPP

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

namespace utils {
namespace files {

/*! Read a file
 *  \param filepath to access the file
 *  \param result   [out] where to store content of the read file
 *  \return true if everything was ok, false otherwise
 *  \warning the content of the result will be override
 */
std::string read(const std::string& filepath);

/*! Tests if a file exists
 *  \param filepath Complete path of the file to test
 *  \return True if a file with the given filepath exists
 */
inline bool exists(const std::string& filepath) { return boost::filesystem::exists(filepath); }

/*! Create a file with a given content
 *  \param filepath a the file to create
 *  \param content  to add to the file
 *  \param override if a file is already existing at the given location ovveride it or not
 *  \return true if the file has been successfully created
 */
bool create( const std::string& filepath, const std::string& content, bool override = true );

/*! Sanitize a string to be a valid filename (replace any character which is not a letter or digit by an underscore) */
std::string sanitize(const std::string& input);

/*! Read file and return lines */
std::vector<std::string> lines(const std::string& filepath, size_t nbr_lines = 0);

}
}

#endif // UTILS_FILE_HPP
