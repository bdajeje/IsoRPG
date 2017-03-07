#include "treasure_interaction.hpp"
#include "managers/sound_manager.hpp"
#include "managers/texture_manager.hpp"
#include "game/game.hpp"
#include "game/screens/treasure_screen.hpp"
#include "graphics/animations/animated_sprite.hpp"
#include "graphics/mouse.hpp"

namespace game {

TreasureInteraction::TreasureInteraction(const json& data, const graphics::SpriteSP& sprite)
  : Interaction (data, InteractionType::OpenTreasure)
  , _sprite {sprite}
  , _model {std::make_shared<InventoryModel>(data)}
{

}

void TreasureInteraction::exec()
{
  if(_data[0].find("open_animation") == _data[0].end())
  {
    std::cerr << "TreasureInteraction with no open_animation: " << _data.dump() << std::endl;
    return;
  }

  const auto& data = _data[0]["open_animation"];
  if(data.find("sound") != data.end())
    sound::SoundManager::play(data["sound"]);

  if(!_animation && !_already_executed)
  {
    _animation = std::make_shared<graphics::animations::AnimatedSprite>(_sprite, data);
    _sprite->addAnimation(_animation);
  }

  TreasureInteractionSP interaction = shared_from_this();
  Game::waitForAnimation(_animation, [interaction]() {
    Game::show(std::make_shared<screen::TreasureScreen>(interaction));
  });

  _already_executed = true;
}

json TreasureInteraction::save()
{
  json data = _data;

  data["inventory"]["items"].clear();
  for(const auto& item : _model->items())
    _data["inventory"]["items"].push_back(item->save());

  return data;
}

void TreasureInteraction::setItems(const std::vector<game::PortableItemSP>& items)
{
  _model->setItems(items);
}

void TreasureInteraction::mouseHover()
{
  graphics::Mouse::setStatus(graphics::Mouse::Status::Loot);
}

}
