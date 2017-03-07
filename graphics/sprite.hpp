#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "graphics/drawable.hpp"

namespace graphics {

class Sprite final : public Drawable
{
  public:

    Sprite(float width, float height);

    sf::FloatRect getGlobalBounds() const { return _sprite->getGlobalBounds(); }
    sf::FloatRect getLocalBounds() const { return _sprite->getLocalBounds(); }
    const sf::Texture* getTexture() const { return _sprite->getTexture(); }
    const sf::IntRect& getTextureRect() const { return _sprite->getTextureRect(); }
    virtual const sf::Color getColor() const override { return _sprite->getColor(); }

    /*! Replace sprite current texture
     *  \param texture - to set
     *  \param width - ovewrite scaling with given value
     *  \param height - ovewrite scaling with given value
     */
    void setTexture(const sf::Texture& texture, bool resetRect = false);
    void setTextureRect(const sf::IntRect& rectangle);

    virtual void setColor(const sf::Color& color) override { _sprite->setColor(color); }
    void verticalFlip();
    void horizontalFlip();

    std::shared_ptr<sf::Sprite> sprite() { return _sprite; }

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
