#ifndef TILESLAYOUT_HPP
#define TILESLAYOUT_HPP

#include <list>

#include "graphics/drawable.hpp"
#include "graphics/models/tile.hpp"
#include "graphics/text.hpp"
#include "graphics/sprite.hpp"
#include "graphics/animation.hpp"
#include "utils/json.hpp"
#include "game/models/map_pos.hpp"
#include "game/interaction.hpp"
#include "game/models/combat_model.hpp"
#include "utils/serializable.hpp"

namespace graphics {

struct MapInteractible
{
    MapInteractible(DrawableSP drawable, bool blocking, bool is_combat_hidden)
      : _drawable {drawable}
      , _blocking {blocking}
      , _is_combat_hidden {is_combat_hidden}
    {}

    DrawableSP _drawable;
    bool _blocking;
    bool _is_combat_hidden;
    std::vector<game::InteractionSP> _interactions;    
};

using MapInteractibleSP = std::shared_ptr<MapInteractible>;
using Path = std::list<MapPos>;

class TilesLayout final : public Drawable
                        , public utils::Serializable
{
  public:

    TilesLayout(const json& data);

    virtual void update(const sf::Time& elapsed_time) override;
    virtual json save() override;
    virtual sf::FloatRect getGlobalBounds() const override;

    void position(SpriteSP transformable, MapPos pos) const noexcept;

    TileSP tileClicked(const MapPos& map_pos);
    graphics::TileSP tileAtMapPos(const MapPos& map_pos) noexcept;
    graphics::TileSP tileHovered(int x_pos, int y_pos);
    float tileHeight() const noexcept { return _tile_height; }
    std::vector<graphics::TileSP> getTilesAround(const MapPos& map_pos, int radius) const;

    bool isValidPoint(const MapPos& point) const;
    bool isInteractible(const MapPos& point) const { return _interactibles.find(std::make_pair(point.x, point.y)) != _interactibles.end(); }
    bool isWalkable(const MapPos& dest) const;
    bool isInside(const MapPos& center_map_pos, int radius, const MapPos& map_pos) const;

    Path pathFinding(const MapPos& start, const MapPos& dest);
    MapPos mapPosFromMousePos(int x_pos, int y_pos) const noexcept;
    void toggleShowGrid() noexcept;

    void triggerInteraction(const MapPos& map_pos);
    void triggerTileHovered(const MapPos& map_pos);

    void startCombat(game::CombatModelSP& model);
    void addCharacter(game::CharacterSP character) { _characters.push_back(character); }

    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return {}; }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;
    TileSP tileAtMousePos(int x_pos, int y_pos) noexcept;
    MapPos tilePosAtMousePos(int x_pos, int y_pos) const noexcept;
    sf::Vector2f tileToCartesian(size_t x, size_t y) const noexcept;
    void showTilesNumber();
    void createTiles(const json& data);
    void createInteractibles(const json& data);

    /*! \param path - must never be empty */
    std::vector<MapPos> findNeighours(std::vector<std::vector<bool> >& visited_points, const Path& path) const;
    Path findPath(const MapPos& start, const MapPos& dest) const;
    void enlightPath(const Path& path);
    void unEnlightedTiles();
    void addEnnemy(game::EnnemyCharacterSP& ennemy);

  private:

    std::vector<std::vector<graphics::TileSP>> _tiles;
    std::map<std::pair<int, int>, MapInteractibleSP> _interactibles;
    std::vector<std::vector<bool>> _walkables;
    graphics::TileSP _previous_selected_tile;
    graphics::TileSP _previous_hovered_tile;
    float _tile_width;
    float _tile_height;
    std::vector<TextSP> _texts_pos;
    sf::Vector2f _tiles_transformation;
    std::vector<AnimationSP> _animations;
    std::vector<TileSP> _enlighted_tiles;
    std::vector<AnimationSP> _enlighted_tile_animations;
    bool _show_grid {false};
    game::CombatModelSP _combat_model;
    std::vector<game::CharacterSP> _characters;
};

using TilesLayoutSP = std::shared_ptr<TilesLayout>;

}

#endif // TILESLAYOUT_HPP
