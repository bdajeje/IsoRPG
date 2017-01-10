#include "sound_manager.hpp"

#include "utils/directory.hpp"
#include "utils/settings.hpp"

namespace sound {

std::unique_ptr<SoundManager> SoundManager::_instance;

void SoundManager::init(const std::string& sound_directory)
{
  if( _instance )
    return;

  _instance.reset(new SoundManager(sound_directory, utils::Settings::instance()->get<float>("sound_volume", 50.f)));
}

SoundManager::SoundManager(const std::string& sound_directory, float volume)
  : _directory { utils::ensureDirectoryEnd(sound_directory) }
  , _volume {volume}
{}

sf::Sound& SoundManager::get(const std::string& sound_file_path)
{
  // Find asset
  auto found_it = _sounds.find(sound_file_path);

  // Found, return it
  if( found_it != _sounds.end() )
    return found_it->second;

  // Not already loaded, so load it then return it
  return loadSound(sound_file_path);
}

sf::Sound& SoundManager::loadSound(const std::string& sound_file_path)
{
  // Load buffer
  sf::SoundBuffer& buffer = _buffers[sound_file_path];
  if( !buffer.loadFromFile( _directory + sound_file_path ) )
    throw std::invalid_argument {"Can't load sound: " + sound_file_path};

  // Create sound
  sf::Sound& sound = _sounds[sound_file_path];
  sound.setBuffer(buffer);
  sound.setVolume(_volume);

  return sound;
}

void SoundManager::play(const std::string& name)
{
  sf::Sound& sound = _instance->get(name);
  sound.setVolume(_instance->_volume);
  sound.play();
}

void SoundManager::setVolume(float value)
{
  _instance->_volume = value;
}

} // sound
