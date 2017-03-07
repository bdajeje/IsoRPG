#ifndef SETTINGSSCREEN_HPP
#define SETTINGSSCREEN_HPP

#include "game/interactible_screen.hpp"
#include "graphics/models/container.hpp"
#include "graphics/models/scrollable_container.hpp"

namespace game {
namespace screen {

class SettingsScreen final : public InteractibleScreen
{
  public:

    SettingsScreen();
    ~SettingsScreen();

    virtual void update(const sf::Time&elapsed_time) override;
    virtual events::EventAction handleEvents(const sf::Event& event) override;

  private:

    void showAudioSettings();
    void showKeysSettings();

  private:

    graphics::ContainerSP _audio_container;
    graphics::ScrollableContainerSP _keys_container;
};

}
}

#endif // SETTINGSSCREEN_HPP
