#include "jukebox.hpp"

#include <algorithm>

#include "utils/directory.hpp"
#include "managers/music_manager.hpp"

namespace audio {

Jukebox::Jukebox()
{
  // List all .ogg files under given directory
  _music_files = utils::listFiles(manager::MusicManager::instance().getDirectory(), ".*\\.ogg", false);

  // Then construct a randomly sorted list of those musics
  std::random_shuffle( _music_files.begin(), _music_files.end() );
}

Jukebox::~Jukebox()
{
  // Wait for underlying thread to exit
  _ask_to_stop = true;
  if(_thread)
    _thread->join();
}

void Jukebox::play()
{
  if(_music_files.empty())
    return;

  // Set some kind of "callback" which will auto play next music when current one is finished
  _thread.reset( new std::thread(std::bind(&Jukebox::playNextMusic, this)) );
}

void Jukebox::resume()
{
  manager::MusicManager::instance().resume();
}

void Jukebox::pause()
{
  manager::MusicManager::instance().pause();
}

void Jukebox::playNextMusic()
{
  manager::MusicManager& music_manager = manager::MusicManager::instance();

  // Wake up from time to time to check if music has ended
  while(!_ask_to_stop)
  {
    if(music_manager.isStopped())
    {
      // Raise offset
      _current_music_offset++;
      if( _current_music_offset >= _music_files.size() )
        _current_music_offset = 0;

      // Start next music
      music_manager.play( _music_files.at(_current_music_offset) );
    }
    else
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

}
