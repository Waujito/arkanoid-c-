#pragma once

#include "entity.hpp"

class Brick: public Entity {
public:
	Brick(Field *field, int x, int y, int width, int height);
	// ~Brick();

	virtual collision_callback getCollisionCallback() override;
};
void brickCollisionCallback(void *e, entity_description ed);
