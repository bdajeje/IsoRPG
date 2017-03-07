#ifndef INTERACTIBLEFILLBAR_HPP
#define INTERACTIBLEFILLBAR_HPP

#include "graphics/models/fill_bar.hpp"

using namespace game;

namespace graphics {

class InteractibleFillBar final : public FillBar
{
  public:

    InteractibleFillBar(uint value, uint max_value, const sf::Color& fill_color, const sf::Color& outer_color, const sf::Color& hover_outer_color, float width, float height);

    virtual void hover() override;
    virtual void unhover() override;
    virtual void clicked(int x, int y) override;

  private:

    sf::Color _hover_outer_color;
    sf::Color _default_outer_color;
};

}

#endif // INTERACTIBLEFILLBAR_HPP
