#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <map>
#include <memory>

#include "graphics/text.hpp"

// Include fonts here, so any include of this file (fontmanager.hpp) brings fonts.hpp too
#include "defines/fonts.hpp"

namespace font {

class FontManager final
{
  public:

    static void init(const std::string& font_directory);

    /* Get the unique instance */
    static FontManager& instance() { return *_instance; }

    static const sf::Font& get(const std::string& font_file_path);

  private:

    FontManager(const std::string& font_directory);

    const sf::Font& loadFont(const std::string& font_name);

  private:

    static std::unique_ptr<FontManager> _instance;

    /* Directory when to find resources */
    const std::string _directory;

    /* Cached textures */
    std::map<std::string, sf::Font> _fonts;
};

} // font

#endif // FONTMANAGER_HPP
