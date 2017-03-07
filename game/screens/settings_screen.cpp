#include "settings_screen.hpp"

#include "graphics/text.hpp"
#include "graphics/models/button.hpp"
#include "graphics/models/interactible_fill_bar.hpp"
#include "utils/keybinding.h"
#include "utils/settings.hpp"
#include "managers/window.hpp"
#include "managers/music_manager.hpp"
#include "managers/sound_manager.hpp"
#include "utils/sounds.hpp"

namespace game {
namespace screen {

namespace {
  constexpr float WIDTH = 600;
  constexpr float HEIGHT = 600;
  constexpr float KEYS_CATEGORY_X_OFFSET = 280;
  constexpr float ACTION_CATEGORY_X_OFFSET = 270;
  constexpr float KEY_CATEGORY_X_OFFSET = 100;
  constexpr float ACTION_BTN_CATEGORY_X_OFFSET = 70;
  constexpr float BAR_WIDTH = 200;
  constexpr float BAR_HEIGHT = 50;
  constexpr float AUDIO_SETTING_Y_OFFSET = 20;
  constexpr float CONTAINER_WIDTH = 600;
  constexpr float CONTAINER_HEIGHT = 500;
  constexpr float AUDIO_Y_OFFSET = 100;
}

SettingsScreen::SettingsScreen()
{
  const auto window_size = mgr::Window::instance()->getSize();
  graphics::TextProperties btn_txt_props {sf::Color::White, "conversation.ttf", 25};

  auto audio_btn = std::make_shared<graphics::Button>("AUDIO", btn_txt_props);
  audio_btn->setPosition((window_size.x - audio_btn->getGlobalBounds().width) / 2 - audio_btn->getGlobalBounds().width, 150);
  addDrawable(audio_btn);

  auto keys_btn = std::make_shared<graphics::Button>("KEYS", btn_txt_props);
  keys_btn->setPosition((window_size.x - keys_btn->getGlobalBounds().width) / 2 + keys_btn->getGlobalBounds().width, audio_btn->getPosition().y);
  addDrawable(keys_btn);

  auto music_volume_text = graphics::getText("conversation.ttf", "Music volume", 20, sf::Color::White);
  auto music_volume_bar = std::make_shared<graphics::InteractibleFillBar>(utils::Settings::instance()->get<uint>("music_volume", 0), 100, sf::Color::Blue, sf::Color::White, sf::Color::Green, BAR_WIDTH, BAR_HEIGHT);
  auto sound_volume_text = graphics::getText("conversation.ttf", "Sound volume", 20, sf::Color::White);
  auto sound_volume_bar = std::make_shared<graphics::InteractibleFillBar>(utils::Settings::instance()->get<uint>("sound_volume", 0), 100, sf::Color::Blue, sf::Color::White, sf::Color::Green, BAR_WIDTH, BAR_HEIGHT);

  const sf::Vector2f music_volume_pos {(CONTAINER_WIDTH - music_volume_text->getGlobalBounds().width) / 2, (CONTAINER_HEIGHT - music_volume_text->getGlobalBounds().height) / 2 - AUDIO_Y_OFFSET};
  const sf::Vector2f music_volume_bar_pos {(CONTAINER_WIDTH - music_volume_bar->getGlobalBounds().width) / 2, music_volume_pos.y + music_volume_text->getGlobalBounds().height + AUDIO_SETTING_Y_OFFSET};
  const sf::Vector2f sound_volume_pos {(CONTAINER_WIDTH - sound_volume_text->getGlobalBounds().width) / 2, (CONTAINER_HEIGHT - sound_volume_text->getGlobalBounds().height) / 2 + AUDIO_Y_OFFSET / 2};
  const sf::Vector2f sound_volume_bar_pos {(CONTAINER_WIDTH - sound_volume_bar->getGlobalBounds().width) / 2, sound_volume_pos.y + sound_volume_text->getGlobalBounds().height + AUDIO_SETTING_Y_OFFSET};
  const sf::Vector2f container_pos {(window_size.x - CONTAINER_WIDTH) / 2, (window_size.y - CONTAINER_HEIGHT) / 2};

  // Audio container and elements
  _audio_container = std::make_shared<graphics::Container>(CONTAINER_WIDTH, CONTAINER_HEIGHT, container_pos);
  _audio_container->addDrawable(music_volume_text, music_volume_pos);
  _audio_container->addDrawable(music_volume_bar, music_volume_bar_pos);
  _audio_container->addDrawable(sound_volume_text, sound_volume_pos);
  _audio_container->addDrawable(sound_volume_bar, sound_volume_bar_pos);

  // keys container and elements
  btn_txt_props.size = 18;
  _keys_container = std::make_shared<graphics::ScrollableContainer>(CONTAINER_WIDTH, CONTAINER_HEIGHT, container_pos);
  float y = 15;
  for(const auto category_it : utils::KeyBinding::categories())
  {
    auto category_text = graphics::getText("conversation.ttf", category_it.first, 20, sf::Color::White);
    _keys_container->addDrawable(category_text, sf::Vector2f{CONTAINER_WIDTH / 2 - KEYS_CATEGORY_X_OFFSET, y});
    y += 40;

    for(const auto action : category_it.second)
    {
      auto action_text = graphics::getText("conversation.ttf", action.title, 15, sf::Color::White);
      _keys_container->addDrawable(action_text, sf::Vector2f{CONTAINER_WIDTH / 2 - ACTION_CATEGORY_X_OFFSET, y});

      auto key_text = graphics::getText("conversation.ttf", action.key, 15, sf::Color::White);
      _keys_container->addDrawable(key_text, sf::Vector2f{CONTAINER_WIDTH / 2 - KEY_CATEGORY_X_OFFSET, y});

      auto key_btn = std::make_shared<graphics::Button>("UPDATE", btn_txt_props);
      _keys_container->addDrawable(key_btn, sf::Vector2f{CONTAINER_WIDTH / 2 + ACTION_BTN_CATEGORY_X_OFFSET, y});
      addHoverable(keys_btn);

      y += 40;
    }

    y += 30;
  }

  _keys_container->updateTexture();
  addEventHandler(_keys_container);

  addDrawable(_audio_container);
  addDrawable(_keys_container);

  addHoverable(audio_btn);
  addHoverable(keys_btn);
  addHoverable(music_volume_bar);
  addHoverable(sound_volume_bar);

  addClickable(audio_btn, [=]() { showAudioSettings(); });
  addClickable(keys_btn, [=]() { showKeysSettings(); });
  addClickable(music_volume_bar, [=]() {
    const auto value = music_volume_bar->value();
    manager::MusicManager::instance().setVolume(value);
    utils::Settings::instance()->set<uint>(utils::Settings::MusicVolume, value);
  });
  addClickable(sound_volume_bar, [=]() {
    const auto value = sound_volume_bar->value();
    sound::SoundManager::setVolume(value);
    sound::SoundManager::play(sounds::UI_Interaction);
    utils::Settings::instance()->set<uint>(utils::Settings::SoundVolume, value);
  });

  showAudioSettings();
//  showKeysSettings();
}

SettingsScreen::~SettingsScreen()
{
  utils::Settings::instance()->save();
}

void SettingsScreen::showAudioSettings()
{
  _audio_container->show();
  _keys_container->hide();
}

void SettingsScreen::showKeysSettings()
{
  _audio_container->hide();
  _keys_container->show();
}

void SettingsScreen::update(const sf::Time& /*elapsed_time*/)
{

}

events::EventAction SettingsScreen::handleEvents(const sf::Event& event)
{
  const events::EventAction action = InteractibleScreen::handleEvents(event);
  if(action != events::EventAction::Continue)
    return action;

  return events::EventAction::Continue;
}

}
}
