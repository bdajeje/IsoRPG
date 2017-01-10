#include "music_manager.hpp"

#include <iostream>

#include "utils/directory.hpp"
#include "utils/settings.hpp"

namespace manager {

std::unique_ptr<MusicManager> MusicManager::_instance;

void MusicManager::init(const std::string& font_directory)
{
  if( _instance )
    return;

  _instance.reset( new MusicManager(font_directory) );
}

MusicManager::MusicManager(const std::string& font_directory)
  : _directory { utils::ensureDirectoryEnd(font_directory) }
  , _volume { utils::Settings::instance()->get<float>("music_volume", 50.f) }
{}

void MusicManager::play(const std::string& music_name)
{
  // If same music already playing, let it play
  if(music_name == _name)
    return;

  _name = music_name;
  _music.stop();

  // Open new music file
  if(!_music.openFromFile( _directory + music_name ))
  {
    std::cout << "Can't open music file: " << _directory << music_name << std::endl;
    return;
  }

  // Set correct volume
  _music.setVolume(_volume);

  // Start music
  _music.play();
}

}
