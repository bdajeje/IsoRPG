#include "combat_player_panel.hpp"
#include "managers/texture_manager.hpp"
#include "graphics/animations/fill_color.hpp"

namespace graphics {

namespace {
  constexpr float BACKGROUND_WIDTH = 804;
  constexpr float BACKGROUND_HEIGHT = 165;
  constexpr float FACE_WIDTH = 100;
  constexpr float FACE_HEIGHT = 100;
  constexpr float SKILL_WIDTH = 55;
  constexpr float SKILL_HEIGHT = 55;
  constexpr uint HEALTH_FONT_SIZE = 13;
  constexpr uint MANA_FONT_SIZE = 11;
  constexpr short MAX_ENERGY_POINTS = 5;
  constexpr short MAX_SKILLS = 7;
  constexpr short MAX_MOVEMENTS = 7;
  constexpr uint ENERGY_ANIMATION_TIME = 350;
}

CombatPlayerPanel::CombatPlayerPanel(const sf::Vector2f& pos, game::CombatModelSP model, graphics::TilesLayoutSP& tiles_layout)
  : _model {model}
  , _tiles_layout {tiles_layout}
  , _energy_default_color {sf::Color{255, 247, 112}}
{
  _background = getSprite("combats/ui_player_panel_background.png", BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
  _face = std::make_shared<Sprite>(FACE_WIDTH, FACE_HEIGHT);

  _health = getText("conversation.ttf", "", HEALTH_FONT_SIZE, sf::Color::White);
  _health->hide();
  _mana = getText("conversation.ttf", "", MANA_FONT_SIZE, sf::Color::White);
  _mana->hide();

  _health_bar = std::make_shared<FillBar>(0, 0, sf::Color::Red, sf::Color{0,0,0,0}, 597, 20);
  _health_bar->setBackgroundColor(sf::Color::Black);
  _mana_bar = std::make_shared<FillBar>(0, 0, sf::Color::Blue, sf::Color{0,0,0,0}, 597, 12);
  _mana_bar->setBackgroundColor(sf::Color::Black);

  addDrawable(_health_bar);
  addDrawable(_mana_bar);
  addDrawable(_background);
  addDrawable(_face);
  addDrawable(_health);
  addDrawable(_mana);

  addHoverable(_health_bar, [&](){_health->show();}, [&](){_health->hide();});
  addHoverable(_mana_bar, [&](){_mana->show();}, [&](){_mana->hide();});

  _energies.reserve(MAX_ENERGY_POINTS);
  for(short i = 0; i < MAX_ENERGY_POINTS; ++i)
  {
	RectangleSP energy_bar = std::make_shared<Rectangle>(69, 5, _energy_default_color);
	_energies.push_back(energy_bar);
	addDrawable(energy_bar);
  }

  _skills.reserve(MAX_SKILLS);
  _skill_highlights.reserve(MAX_SKILLS);
  _skill_shortcuts.reserve(MAX_SKILLS);
  for(size_t i = 0; i < MAX_SKILLS; ++i)
  {
	auto skill = std::make_shared<Sprite>(50, 50);
	_skills.push_back(skill);
	addDrawable(skill);

	auto skill_highlight = std::make_shared<Rectangle>(SKILL_WIDTH, SKILL_HEIGHT);
	skill_highlight->shape()->setFillColor(sf::Color{0,0,0,0});
	skill_highlight->shape()->setOutlineColor(sf::Color{30,200,30, 200});
	skill_highlight->shape()->setOutlineThickness(2);
	skill_highlight->hide();
	_skill_highlights.push_back(skill_highlight);
	addDrawable(skill_highlight);

	auto skill_shortcut = getText("conversation.ttf", std::to_string(i+1), 18, sf::Color::White);
	skill_shortcut->hide();
	_skill_shortcuts.push_back(skill_shortcut);
	addDrawable(skill_shortcut);

	addHoverable(skill_highlight, [=](){ skillHover(i); }, [=](){ skillUnhover(i); });
	addClickable(skill_highlight, [=](){ skillClicked(i); });
  }

  const sf::Color color {255, 255, 255};
  _movements.reserve(MAX_MOVEMENTS);
  for(auto i = 0; i < MAX_MOVEMENTS; ++i)
  {
	auto bar = std::make_shared<Rectangle>(50, 10, color);
	_movements.push_back(bar);
	addDrawable(bar);
  }

  setPosition(pos.x, pos.y);
}

void CombatPlayerPanel::skillHover(size_t i)
{
  if(!_character)
	return;

  const auto& character_skills = _character->combatSkills();
  if(i >= character_skills.size())
	return;

  const auto remaining_energy = _character->energy();
  if(remaining_energy <= 0)
	return;


  const auto& character_skill = character_skills.at(i);
  const auto end = std::max(remaining_energy, character_skill->energyCost()) - std::min(remaining_energy, character_skill->energyCost());
  for(short j = remaining_energy - 1; j >= end; --j)
  {
	auto& energy = _energies[j];
	energy->cancelAnimations();
	energy->addAnimation(std::make_shared<animations::FillColor>(energy->shape(), sf::Color{0, 0, 255}, sf::milliseconds(ENERGY_ANIMATION_TIME)));
	_skill_highlights.at(i)->show();
  }
}

void CombatPlayerPanel::skillUnhover(size_t i)
{
  for(auto i = _energies.size(); i > 0; --i)
  {
	auto& energy = _energies[i-1];
	if(!energy->hasAnimations())
	  break;

	energy->cancelAnimations();
	energy->addAnimation(std::make_shared<animations::FillColor>(energy->shape(), _energy_default_color, sf::milliseconds(ENERGY_ANIMATION_TIME)));
  }

  _skill_highlights.at(i)->hide();
}

void CombatPlayerPanel::skillClicked(size_t i)
{
  if(!_character)
	return;

  const auto& character_skills = _character->combatSkills();
  if(i >= character_skills.size())
	return;

  const auto remaining_energy = _character->energy();
  const auto& character_skill = character_skills.at(i);
  if(character_skill->energyCost() > remaining_energy)
	return;

  auto skill = character_skills.at(i);
  _tiles_layout->showSkillArea(skill, _character->mapPos());
  _model->setSelectedSkill(skill);
}

void CombatPlayerPanel::update(const sf::Time& time)
{
  updateHealth();
  updateMana();
  updateMovements();

  InteractibleScreen::update(time);
}

void CombatPlayerPanel::setCharacter(game::PlayableCharacterSP& character)
{
  if(character == _character)
	return;

  _character = character;
  updateSkills();
  _face->setTexture(texture::TextureManager::get(character->faceTextureName()));
}

void CombatPlayerPanel::updateMovements()
{
  if(!_character)
	return;

  const auto remaining_movements = _character->combatMovement();
  if(_remaining_movements == remaining_movements)
	return;

  _remaining_movements = remaining_movements;

  for(auto i = 0; i < MAX_MOVEMENTS; ++i)
  {
	if(i < _remaining_movements)
	  _movements[i]->show();
	else if(_movements[i]->isVisible())
	  _movements[i]->hide();
	else
	  break;
  }
}

void CombatPlayerPanel::updateHealth()
{
  if(!_character)
	return;

  const auto life = _character->life();
  const auto maxlife = _character->maxLife();

  if(life != _health_bar->value() || maxlife != _health_bar->maxValue())
  {
	_health_bar->setValues(life, maxlife);
	_health->setString(std::to_string(life) + "/" + std::to_string(maxlife));
  }
}

void CombatPlayerPanel::updateMana()
{
  if(!_character)
	return;

  const auto mana = _character->mana();
  const auto maxmana = _character->maxMana();

  if(mana != _mana_bar->value() || maxmana != _mana_bar->maxValue())
  {
	_mana->setString(std::to_string(mana) + "/" + std::to_string(maxmana));
	_mana_bar->setValues(mana, maxmana);
  }
}

void CombatPlayerPanel::updateSkills()
{
  if(!_character)
	return;

  const auto& skills = _character->combatSkills();
  const auto nbr_skills = skills.size();

  for(size_t i = 0; i < MAX_SKILLS; ++i)
  {
	if(i < nbr_skills)
	{
	  _skills[i]->setTexture(texture::TextureManager::get(skills[i]->icon()));
	  _skill_shortcuts[i]->show();
	}
	else
	{
	  _skills[i]->hide();
	  _skill_shortcuts[i]->hide();
	}
  }
}

void CombatPlayerPanel::setPosition(float x, float y)
{
  _background->setPosition(x, y);
  const auto bg_pos = _background->getPosition();

  _face->setPosition(bg_pos.x + 65, bg_pos.y + 25);
  _health_bar->setPosition(bg_pos.x + 180, bg_pos.y + 98);
  _mana_bar->setPosition(bg_pos.x + 164, bg_pos.y + 123);

  const auto& health_pos = _health_bar->getPosition();
  const auto& health_bounds = _health->getGlobalBounds();
  const auto& health_bar_bounds = _health_bar->getGlobalBounds();
  _health->setPosition(health_pos.x + (health_bar_bounds.width - health_bounds.width) / 2,
					   health_pos.y + (health_bar_bounds.height - health_bounds.height) / 2 - 10);

  const auto& mana_pos = _mana_bar->getPosition();
  const auto& mana_bounds = _mana->getGlobalBounds();
  const auto& mana_bar_bounds = _mana_bar->getGlobalBounds();
  _mana->setPosition(mana_pos.x + (mana_bar_bounds.width - mana_bounds.width) / 2,
					 mana_pos.y + (mana_bar_bounds.height - mana_bounds.height) / 2 - MANA_FONT_SIZE);

  float energy_pos_x = 356;
  for(auto& energy_bar : _energies)
  {
	energy_bar->setPosition(energy_pos_x, bg_pos.y + 11);
	energy_pos_x += energy_bar->getGlobalBounds().width + 10;
  }

  float skill_pos_x = 208;
  size_t i = 0;
  for(auto& skill : _skills)
  {
	skill->setPosition(skill_pos_x, bg_pos.y + 32);
	skill_pos_x += 80;

	const auto& skill_pos = skill->getPosition();
	_skill_highlights[i]->setPosition(skill_pos.x, skill_pos.y - 3);

	const auto& skill_shortcut = _skill_shortcuts[i];
	skill_shortcut->setPosition(skill_pos.x + (SKILL_WIDTH - skill_shortcut->getGlobalBounds().width) / 2, skill_pos.y + 40);

	i++;
  }

  i = 0;
  for(auto& bar : _movements)
  {
	bar->setPosition(bg_pos.x + 150 + i * 60, bg_pos.y + 145);
	i++;
  }
}

game::events::EventAction CombatPlayerPanel::handleEvents(const sf::Event& event)
{
  using namespace game::events;

  if(InteractibleScreen::handleEvents(event) == EventAction::Stop)
	return EventAction::Stop;

  switch(event.type)
  {
	case sf::Event::MouseButtonPressed:
	{
	  if(event.mouseButton.button == sf::Mouse::Button::Right)
	  {
		_model->unselectSkill();
		_tiles_layout->hideSkillArea();
		return EventAction::Stop;
	  }

	  break;
	}
	case sf::Event::KeyPressed:
	{
	  if(handleKeyPressed())
		return EventAction::Stop;

	  break;
	}
  }

  return EventAction::Continue;
}

bool CombatPlayerPanel::handleKeyPressed()
{
  if(_model->currentMode() == game::CombatModel::Mode::Placement)
	return false;

  static const std::array<sf::Keyboard::Key, MAX_SKILLS> key_skills {
	  utils::KeyBinding::key(KeyAction::CombatSelectSkill1),
	  utils::KeyBinding::key(KeyAction::CombatSelectSkill2),
	  utils::KeyBinding::key(KeyAction::CombatSelectSkill3),
	  utils::KeyBinding::key(KeyAction::CombatSelectSkill4),
	  utils::KeyBinding::key(KeyAction::CombatSelectSkill5)
  };

  size_t i = 0;
  for(const auto& key_skill : key_skills)
  {
	if(isKeyAllowed(key_skill))
	{
	  skillClicked(i);
	  return true;
	}

	i++;
  }

  return false;
}

}
