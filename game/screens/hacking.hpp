//#ifndef HACKING_HPP
//#define HACKING_HPP

//#include "game/interactible_screen.hpp"
//#include "graphics/animations/move.hpp"
//#include "utils/key_limitor.hpp"

//namespace game {
//namespace screen {

//class Hacking final : public InteractibleScreen
//{
//  enum class Direction {
//    Left, Right
//  };

//  public:

//    Hacking();

//    events::EventAction handleEvents(const sf::Event& event) override;

//    virtual void update(const sf::Time& elapsed_time) override;

//  private:

//    bool rotate(Direction direction) noexcept;
//    bool isReady() const noexcept;
//    void updateLevels() noexcept;
//    void setTexture(graphics::SpriteSP& sprite, const sf::Texture& texture) const noexcept;

//  private:

//    const sf::Texture& _neutral_texture;
//    const sf::Texture& _error_texture;
//    const sf::Texture& _success_texture;
//    std::map<const sf::Texture*, std::string> _texture_sounds;
//    std::shared_ptr<graphics::animations::Move> _intro_animation;
//    utils::KeyLimitor _limitor;
//    std::vector<graphics::SpriteSP> _right_btns;
//    std::vector<graphics::SpriteSP> _wrong_btns;
//    graphics::SpriteSP _rotor;
//    float _angle {0};
//    float _target_angle {0};
//    ushort _failure_percentage {0};
//    int _target_proximity;
//};

//}
//}

//#endif // HACKING_HPP
