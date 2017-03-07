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

struct ShownSkill
{
  MapPos map_pos;
  game::CombatSkillSP skill;
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
    void tileHovered(const MapPos& map_pos, bool show_grid);
    void tileHovered(int pos_x, int pos_y, bool show_grid);
    float tileHeight() const noexcept { return _tile_height; }
    std::vector<graphics::TileSP> getTilesAround(const MapPos& map_pos, int radius) const;

    bool isValidPoint(const MapPos& point) const;
    bool isInteractible(const MapPos& point) const { return _interactibles.find(std::make_pair(point.x, point.y)) != _interactibles.end(); }
    bool isWalkable(const MapPos& dest) const;
    bool isWalkable(int x, int y) const;
    bool isInside(const MapPos& center_map_pos, int radius, const MapPos& map_pos) const;
    size_t pathContains(const graphics::Path& path, const MapPos& map_pos);

    Path pathFinding(const MapPos& start, const MapPos& dest);
    MapPos mapPosFromMousePos(int x_pos, int y_pos) const noexcept;
    void toggleShowGrid() noexcept;

    void triggerInteraction(const MapPos& map_pos);
    void triggerTileHovered(const MapPos& map_pos);

    void startCombat(game::CombatModelSP& model);
    void addCharacter(game::CharacterSP character) { position(character->sprite(), character->mapPos()) ; _characters.push_back(character); }

    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return {}; }

    void enlightPath(const Path& path, int show_limit = -1);
    void enlightTile(const MapPos& map_pos);
    void unEnlightedTiles();
    void setPath(const Path& path) { _player_path = path; }
    graphics::Path& playerPath() { return _player_path; }

    void showSkillArea(const game::CombatSkillSP& skill, const MapPos& map_pos);
    void hideSkillArea();

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
    void addEnnemy(game::EnnemyCharacterSP& ennemy);

  private:

    std::vector<std::vector<graphics::TileSP>> _tiles;
    std::map<std::pair<int, int>, MapInteractibleSP> _interactibles;
    std::vector<std::vector<bool>> _walkables;
    graphics::TileSP _previous_selected_tile;
    MapPos _previous_hovered_map_pos;
    float _tile_width;
    float _tile_height;
    std::vector<TextSP> _texts_pos;
    sf::Vector2f _tiles_transformation;
    std::vector<TileSP> _enlighted_tiles;
    bool _show_grid {false};
    game::CombatModelSP _combat_model;
    std::vector<game::CharacterSP> _characters;
    graphics::Path _player_path;
    ShownSkill _shown_skill;
};

using TilesLayoutSP = std::shared_ptr<TilesLayout>;

}

#endif // TILESLAYOUT_HPP
