#include "keybinding.h"

namespace utils {

std::unique_ptr<KeyBinding> KeyBinding::_instance;

namespace {
  const std::map<std::string, sf::Keyboard::Key> StrToKeys = {
    {"Num0", sf::Keyboard::Num0},
    {"Num1", sf::Keyboard::Num1},
    {"Num2", sf::Keyboard::Num2},
    {"Num3", sf::Keyboard::Num3},
    {"Num4", sf::Keyboard::Num4},
    {"Num5", sf::Keyboard::Num5},
    {"Num6", sf::Keyboard::Num6},
    {"Num7", sf::Keyboard::Num7},
    {"Num8", sf::Keyboard::Num8},
    {"Num9", sf::Keyboard::Num9},
    {"q", sf::Keyboard::Q},
    {"w", sf::Keyboard::W},
    {"e", sf::Keyboard::E},
    {"r", sf::Keyboard::R},
    {"t", sf::Keyboard::T},
    {"y", sf::Keyboard::Y},
    {"u", sf::Keyboard::U},
    {"i", sf::Keyboard::I},
    {"o", sf::Keyboard::O},
    {"p", sf::Keyboard::P},
    {"a", sf::Keyboard::A},
    {"s", sf::Keyboard::S},
    {"d", sf::Keyboard::D},
    {"f", sf::Keyboard::F},
    {"g", sf::Keyboard::G},
    {"h", sf::Keyboard::H},
    {"j", sf::Keyboard::J},
    {"k", sf::Keyboard::K},
    {"l", sf::Keyboard::L},
    {"z", sf::Keyboard::Z},
    {"x", sf::Keyboard::X},
    {"c", sf::Keyboard::C},
    {"v", sf::Keyboard::V},
    {"b", sf::Keyboard::B},
    {"n", sf::Keyboard::N},
    {"m", sf::Keyboard::M},
    {"escape", sf::Keyboard::Escape},
    {"space", sf::Keyboard::Space},
    {"return", sf::Keyboard::Return},
    {"backspace", sf::Keyboard::BackSpace},
    {"tab", sf::Keyboard::Tab},
    {"pageup", sf::Keyboard::PageUp},
    {"pagedown", sf::Keyboard::PageDown},
    {"left", sf::Keyboard::Left},
    {"right", sf::Keyboard::Right},
    {"up", sf::Keyboard::Up},
    {"down", sf::Keyboard::Down},
    {"f1", sf::Keyboard::F1},
    {"f2", sf::Keyboard::F2},
    {"f3", sf::Keyboard::F3},
    {"f4", sf::Keyboard::F4},
    {"f5", sf::Keyboard::F5},
    {"f6", sf::Keyboard::F6},
    {"f7", sf::Keyboard::F7},
    {"f8", sf::Keyboard::F8},
    {"f9", sf::Keyboard::F9},
    {"f10", sf::Keyboard::F10},
    {"f11", sf::Keyboard::F11},
    {"f12", sf::Keyboard::F12}
  };

  const std::map<sf::Keyboard::Key, std::string> KeyToString = {
    {sf::Keyboard::Num0, "Num0"},
    {sf::Keyboard::Num1, "Num1"},
    {sf::Keyboard::Num2, "Num2"},
    {sf::Keyboard::Num3, "Num3"},
    {sf::Keyboard::Num4, "Num4"},
    {sf::Keyboard::Num5, "Num5"},
    {sf::Keyboard::Num6, "Num6"},
    {sf::Keyboard::Num7, "Num7"},
    {sf::Keyboard::Num8, "Num8"},
    {sf::Keyboard::Num9, "Num9"},
    {sf::Keyboard::Q, "q"},
    {sf::Keyboard::W, "w"},
    {sf::Keyboard::E, "e"},
    {sf::Keyboard::R, "r"},
    {sf::Keyboard::T, "t"},
    {sf::Keyboard::Y, "y"},
    {sf::Keyboard::U, "u"},
    {sf::Keyboard::I, "i"},
    {sf::Keyboard::O, "o"},
    {sf::Keyboard::P, "p"},
    {sf::Keyboard::A, "a"},
    {sf::Keyboard::S, "s"},
    {sf::Keyboard::D, "d"},
    {sf::Keyboard::F, "f"},
    {sf::Keyboard::G, "g"},
    {sf::Keyboard::H, "h"},
    {sf::Keyboard::J, "j"},
    {sf::Keyboard::K, "k"},
    {sf::Keyboard::L, "l"},
    {sf::Keyboard::Z, "z"},
    {sf::Keyboard::X, "x"},
    {sf::Keyboard::C, "c"},
    {sf::Keyboard::V, "v"},
    {sf::Keyboard::B, "b"},
    {sf::Keyboard::N, "n"},
    {sf::Keyboard::M, "m"},
    {sf::Keyboard::Escape, "escape"},
    {sf::Keyboard::Space, "space"},
    {sf::Keyboard::Return, "return"},
    {sf::Keyboard::BackSpace, "backspace"},
    {sf::Keyboard::Tab, "tab"},
    {sf::Keyboard::PageUp, "pageup"},
    {sf::Keyboard::PageDown, "pagedown"},
    {sf::Keyboard::Left, "left"},
    {sf::Keyboard::Right, "right"},
    {sf::Keyboard::Up, "up"},
    {sf::Keyboard::Down, "down"},
    {sf::Keyboard::F1, "f1"},
    {sf::Keyboard::F2, "f2"},
    {sf::Keyboard::F3, "f3"},
    {sf::Keyboard::F4, "f4"},
    {sf::Keyboard::F5, "f5"},
    {sf::Keyboard::F6, "f6"},
    {sf::Keyboard::F7, "f7"},
    {sf::Keyboard::F8, "f8"},
    {sf::Keyboard::F9, "f9"},
    {sf::Keyboard::F10, "f10"},
    {sf::Keyboard::F11, "f11"},
    {sf::Keyboard::F12, "f12"}
  };

	// This method is not really optimized, but we don't care,
	// it is executed only during KeyBinding initialization, only once in the program lifetime.
  sf::Keyboard::Key toKey(const std::string& input)
	{
    auto found = StrToKeys.find(input);
    if(found == StrToKeys.end())
    {
      std::cerr << "Unkown key: " << input << std::endl;
      assert(false);
      return sf::Keyboard::Unknown;
    }

    return found->second;
	}
}

void KeyBinding::init(const json& data)
{
	_instance.reset(new KeyBinding(data));
}

KeyBinding::KeyBinding(const json& data)
{
  _bindings[KeyAction::CombatSelectSkill1] = toKey(data["combat_action_bar"]["select_skill_1"]["key"]);
  _bindings[KeyAction::CombatSelectSkill2] = toKey(data["combat_action_bar"]["select_skill_2"]["key"]);
  _bindings[KeyAction::CombatSelectSkill3] = toKey(data["combat_action_bar"]["select_skill_3"]["key"]);
  _bindings[KeyAction::CombatSelectSkill4] = toKey(data["combat_action_bar"]["select_skill_4"]["key"]);
  _bindings[KeyAction::CombatSelectSkill5] = toKey(data["combat_action_bar"]["select_skill_5"]["key"]);

  _bindings[KeyAction::ConversationFocusPreviousAnswer] = toKey(data["conversation"]["focus_previous_answer"]["key"]);
  _bindings[KeyAction::ConversationFocusNextAnswer] = toKey(data["conversation"]["focus_next_answer"]["key"]);
  _bindings[KeyAction::ConversationSkip] = toKey(data["conversation"]["skip"]["key"]);
  _bindings[KeyAction::ConversationSelect] = toKey(data["conversation"]["select"]["key"]);
  _bindings[KeyAction::ConversationSelect1] = toKey(data["conversation"]["select_1"]["key"]);
  _bindings[KeyAction::ConversationSelect2] = toKey(data["conversation"]["select_2"]["key"]);
  _bindings[KeyAction::ConversationSelect3] = toKey(data["conversation"]["select_3"]["key"]);
  _bindings[KeyAction::ConversationSelect4] = toKey(data["conversation"]["select_4"]["key"]);
  _bindings[KeyAction::ConversationSelect5] = toKey(data["conversation"]["select_5"]["key"]);

  _bindings[KeyAction::MapOpenInventory] = toKey(data["map"]["open_inventory"]["key"]);
  _bindings[KeyAction::ShowGameMenu] = toKey(data["general"]["show_game_menu"]["key"]);
  _bindings[KeyAction::ExitScreen] = toKey(data["screen"]["exit"]["key"]);

  assert(StrToKeys.size() == KeyToString.size());
}

sf::Keyboard::Key KeyBinding::key(KeyAction action)
{
	return _instance->_bindings[action];
}

std::map<std::string, std::vector<KeyStruct>> KeyBinding::categories()
{
  std::map<std::string, std::vector<KeyStruct>> results;

  results["Combat Action Bar"].emplace_back("Select Skill 1", KeyToString.at(_instance->_bindings[KeyAction::CombatSelectSkill1]));
  results["Combat Action Bar"].emplace_back("Select Skill 2", KeyToString.at(_instance->_bindings[KeyAction::CombatSelectSkill2]));
  results["Combat Action Bar"].emplace_back("Select Skill 3", KeyToString.at(_instance->_bindings[KeyAction::CombatSelectSkill3]));
  results["Combat Action Bar"].emplace_back("Select Skill 4", KeyToString.at(_instance->_bindings[KeyAction::CombatSelectSkill4]));
  results["Combat Action Bar"].emplace_back("Select Skill 5", KeyToString.at(_instance->_bindings[KeyAction::CombatSelectSkill5]));

  results["Map"].emplace_back("Open Inventory", KeyToString.at(_instance->_bindings[KeyAction::MapOpenInventory]));
  results["Map"].emplace_back("Open Game Menu", KeyToString.at(_instance->_bindings[KeyAction::ShowGameMenu]));

  results["General"].emplace_back("Exit Current Screen", KeyToString.at(_instance->_bindings[KeyAction::ExitScreen]));

  results["Conversation"].emplace_back("Select action", KeyToString.at(_instance->_bindings[KeyAction::ConversationSelect]));
  results["Conversation"].emplace_back("Skip", KeyToString.at(_instance->_bindings[KeyAction::ConversationSkip]));
  results["Conversation"].emplace_back("Focus previous answer", KeyToString.at(_instance->_bindings[KeyAction::ConversationFocusPreviousAnswer]));
  results["Conversation"].emplace_back("Focus next answer", KeyToString.at(_instance->_bindings[KeyAction::ConversationFocusNextAnswer]));
  results["Conversation"].emplace_back("Select first answer", KeyToString.at(_instance->_bindings[KeyAction::ConversationSelect1]));
  results["Conversation"].emplace_back("Select second answer", KeyToString.at(_instance->_bindings[KeyAction::ConversationSelect2]));
  results["Conversation"].emplace_back("Select thrid answer", KeyToString.at(_instance->_bindings[KeyAction::ConversationSelect3]));
  results["Conversation"].emplace_back("Select forth answer", KeyToString.at(_instance->_bindings[KeyAction::ConversationSelect4]));
  results["Conversation"].emplace_back("Select fifth answer", KeyToString.at(_instance->_bindings[KeyAction::ConversationSelect5]));

  return results;
}

}
