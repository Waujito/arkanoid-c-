#pragma once

#include "entity.h"
#include <cmath>

struct BallProperties{
	coords_t velocity = 0.02;
	double angle = M_PI/24;

	coords_t x = -1;
	coords_t y = -1;
};


class Ball : public Entity {
private:
	coords_t velocity;
	double angle;

	void update_coords(bool force = false);
public:
	Ball(Field *field, BallProperties props);

	void refresh(bool force = false);
	CollisionSide detectBorderCollision(vec2i coords);
	void move(vec2i coords, bool force = false);
	void mirrorAngle(CollisionSide side);
	virtual void collision_action(CollisionSide collision) override;

	void setAngle(double angle);
	void setVelocity(coords_t velocity);
};
