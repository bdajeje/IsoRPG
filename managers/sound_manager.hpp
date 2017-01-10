#ifndef MANAGERS_SOUND_MANAGER_HPP
#define MANAGERS_SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>

#include <map>
#include <memory>

namespace sound {

class SoundManager final
{
  public:

    static void init(const std::string& sound_directory);
    static void play(const std::string& name);
    static void setVolume(float value);

  private:

    SoundManager(const std::string& sound_directory, float volume);

    sf::Sound& get(const std::string& sound_file_path);
    sf::Sound& loadSound(const std::string& sound);

  private:

    static std::unique_ptr<SoundManager> _instance;    

    /* Directory when to find resources */
    const std::string _directory;

    /*! Volume of all sounds */
    float _volume;

    /* Cached sounds and buffers */
    std::map<std::string, sf::SoundBuffer> _buffers;
    std::map<std::string, sf::Sound> _sounds;
};

} // sound

#endif // MANAGERS_SOUND_MANAGER_HPP
