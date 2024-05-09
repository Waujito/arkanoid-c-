#include "player.h"


Player::Player(Field *field) : Entity(field, { 
	.x=1, // (term->getMaxX() - term->getMinX())/2
	.y=(coords_t)field->getMaxY() - 1,
	.yMovable = false, .height = 2, .width = 3})
{
}
