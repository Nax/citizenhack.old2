#include <hack/action_move.h>

ActionMove::ActionMove(DungeonLevel& level, Actor& actor, Vector2i delta)
: _level(level), _actor(actor), _delta(delta)
{

}

int ActionMove::perform()
{
    Vector2i target;
    Vector2i pos;
    TileID tile_id;

    pos = _actor.pos();
    target.x = pos.x + _delta.x;
    target.y = pos.y + _delta.y;
    tile_id = _level.at(target);
    const TileData& tile_data = TileData::from_id(tile_id);
    if (tile_data.solid)
        return -1;
    _actor.move(target.x, target.y);
    return 1000;
}
