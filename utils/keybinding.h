#ifndef KEYBINDING_H
#define KEYBINDING_H

#include <memory>
#include <SFML/Window/Keyboard.hpp>
#include "utils/json.hpp"

enum class KeyAction {
	CombatSelectSkill1,
	CombatSelectSkill2,
	CombatSelectSkill3,
	CombatSelectSkill4,
	CombatSelectSkill5,
	MapOpenInventory,
	ConversationFocusPreviousAnswer,
	ConversationFocusNextAnswer,
	ConversationSkip,
	ConversationSelect,
	ConversationSelect1,
	ConversationSelect2,
	ConversationSelect3,
	ConversationSelect4,
	ConversationSelect5,
	ExitScreen,
	ShowGameMenu
};

namespace utils {

struct KeyStruct {
    KeyStruct(std::string title, std::string key)
      : title {title}
      , key {key}
    {}

    std::string title;
    std::string key;
};

class KeyBinding final
{
	public:

		static void init(const json& data);
		static sf::Keyboard::Key key(KeyAction action);

    /* \Warning: This method creates the result for each call in order to save memory usage. Call it carefully. */
    static std::map<std::string, std::vector<KeyStruct>> categories();
//    static const std::string& action(KeyAction action);

	private:

		KeyBinding(const json& data);

	private:

		std::map<KeyAction, sf::Keyboard::Key> _bindings;    
//    json _data;
		static std::unique_ptr<KeyBinding> _instance;
};

}

#endif // KEYBINDING_H
