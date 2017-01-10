#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <array>
#include <map>
#include <memory>
#include <string>

#include <boost/lexical_cast.hpp>

namespace utils {

class Settings final
{
  public:

    static std::unique_ptr<Settings>& init(const std::string filepath);
    static std::unique_ptr<Settings>& instance();

    /*! Get a setting by its key
     *  \param key           - to retrieve
     *  \param default_value - default value to return if wanted value can't be returned
     */
    template <class T>
    T get(const std::string& key, T default_value) const
    {
      try
      {
        return boost::lexical_cast<T>(_setting_values.at(key));
      }
      catch(...)
      {
        return default_value;
      }
    }

    /*! Set a setting to a given value
     *  \param key   - key of the setting to change
     *  \param value - new value for the setting
     */
    void set(const std::string& key, const std::string& value);

    /*! Save settings */
    bool save();

  private:

    /*! Load settings from file */
    void load();

    /*! Constructor
     *  \params filepath - file path to settings file
     */
    Settings(const std::string& filepath);

  public:

    /*! Available settings to retrieve */
    static const std::string SoundVolume;
    static const std::string MusicVolume;
    static const std::string WindowWidth;
    static const std::string WindowHeight;
    static const std::string LastPlayer;

  private:

    std::string _filepath;
    std::map<std::string, std::string> _setting_values;

    static const std::array<std::string, 5> s_setting_keys;
    static std::unique_ptr<Settings> _instance;
};

}

#endif // SETTINGS_HPP
