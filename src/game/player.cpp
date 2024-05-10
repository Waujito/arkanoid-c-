#include "player.hpp"


Player::Player(Field *field) : Entity(field, { 
	.x=((coords_t)field->getMaxX() - (coords_t)field->getMinX())/2,
	.y=(coords_t)field->getMaxY() - 1,
	.yMovable = false, .height = 1, .width = 12})
{
}
