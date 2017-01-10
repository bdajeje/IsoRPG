#ifndef JUKEBOX_HPP
#define JUKEBOX_HPP

#include <thread>
#include <memory>
#include <vector>

namespace audio {

class Jukebox final
{
  public:

    Jukebox();

    ~Jukebox();

    /*! Start jukebox
     *  \returns true if a music has been started, false otherwise
     */
    void play();

    void resume();
    void pause();

  private:

    void playNextMusic();

  protected:

    std::vector<std::string> _music_files;
    std::unique_ptr<std::thread> _thread; // Thread responsibled for playing next music when ones is finished
    size_t _current_music_offset {0};
    bool _ask_to_stop {false};
};

}

#endif // JUKEBOX_HPP
