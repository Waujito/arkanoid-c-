#ifndef BALL_H
#define BALL_H
#include "entity.h"

struct BallProperties{
	coords_t velocity = 1;
	double angle = 0;

	coords_t x = -1;
	coords_t y = -1;
};


class Ball : public Entity {
private:
	coords_t velocity;
	double angle;

	void update_coords(bool force = false);
public:
	Ball(Field *field);
	Ball(Field *field, BallProperties props);

	void refresh(bool force = false);
	CollisionSide detectBorderCollision(vec2i coords);
	void move(vec2i coords, bool force = false);
	void mirrorAngle(CollisionSide side);
	virtual void collision_action(CollisionSide collision) override;

	void setAngle(double angle);
	void setVelocity(coords_t velocity);
};

#endif
