#include "brick.hpp"
#include <sstream>
#include <syslog.h>

Brick::Brick(Field *field, int x, int y, int width, int height): Entity(
	field, 
	{.x = (coords_t)x, .y = (coords_t)y, .height=(coords_t)height, .width=(coords_t)width}
) {
}


collision_callback Brick::getCollisionCallback()
{
	return brickCollisionCallback;
}

void brickCollisionCallback(void *e, entity_description ed)
{
	Brick *brick = (Brick *)e;
	brick->~Brick();
}
