#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "graphics/drawable.hpp"
#include "game/transformable.hpp"
#include "graphics/animations/animated_sprite.hpp"

namespace graphics {

class Sprite final : public Drawable
                   , public game::Transformable
{
  public:

    Sprite(float width, float height);

    sf::FloatRect getGlobalBounds() const { return _sprite->getGlobalBounds(); }    
    sf::FloatRect getLocalBounds() const { return _sprite->getLocalBounds(); }
    const sf::Texture* getTexture() const { return _sprite->getTexture(); }
    virtual const sf::Color getColor() const override { return _sprite->getColor(); }

    /*! Replace sprite current texture
     *  \param texture - to set
     *  \param width - ovewrite scaling with given value
     *  \param height - ovewrite scaling with given value
     */
    void setTexture(const sf::Texture& texture, bool keep_size = true);
    void setTextureRect(const sf::IntRect& rectangle);

    virtual void setColor(const sf::Color& color) override { _sprite->setColor(color); }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

  private:

    std::shared_ptr<sf::Sprite> _sprite;    
    float _width;
    float _height;
};

using SpriteSP = std::shared_ptr<Sprite>;

SpriteSP getSprite(const std::string& texture_file_path, float width, float height);
SpriteSP getSprite(const sf::Texture& texture, float width, float height);

}

#endif // SPRITE_HPP
