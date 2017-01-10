#ifndef MUSICMANAGER_HPP
#define MUSICMANAGER_HPP

#include <memory>

#include <SFML/Audio/Music.hpp>

namespace manager {

class MusicManager final
{
  public:

    static void init(const std::string& font_directory);

    /* Get the unique instance */
    static MusicManager& instance() { return *_instance; }

    void play(const std::string& music_name);
    void resume() { _music.play(); }
    void pause() { _music.pause(); }
    void stop() { _music.play(); }

    void setVolume(float volume) { _volume = volume; _music.setVolume(volume); }

    const std::string getDirectory() const { return _directory; }

    bool isStopped() const { return _music.getStatus() == sf::SoundSource::Stopped; }

  private:

    MusicManager(const std::string& font_directory);

  private:

    /*! Music volume */
    float _volume {50.f};

    /*! Current loaded music */
    sf::Music _music;
    std::string _name;

    /* Directory when to find resources */
    const std::string _directory;

    static std::unique_ptr<MusicManager> _instance;
};

}

#endif // MUSICMANAGER_HPP
