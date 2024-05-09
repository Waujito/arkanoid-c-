#include <cmath>
#include "ball.h"
#include <syslog.h>
#include <sstream>

Ball::Ball(Field *field) : Entity(field, (EntityProperties){
		.x=(((coords_t)field->getMaxX() - (coords_t)field->getMinX()) / 2),
		.y=(((coords_t)field->getMaxY() - (coords_t)field->getMinY()) / 2),
		.height=2, .width=3
	})
{
	this->velocity = 0.02;
	this->angle = M_PI/24;
}

Ball::Ball(Field *field, BallProperties props) : Ball(field)
{
	this->velocity = props.velocity;
	this->angle = props.angle;
	
	coords_t x = props.x;
	coords_t y = props.y;

	if (x != -1)
		set_x(x);
	if (y != -1)
		set_y(y);
}


void Ball::update_coords(bool force)
{
	coords_t vx = velocity * cos(angle);
	coords_t vy = velocity * sin(angle);

	// Uses vectors operations. x' = x + v_x*cos(phi).
	// Subtracts y coordinate because terminal has inversed y: bigger coordinate = lower position
	move({get_x() + vx, get_y() - vy}, force);
}

void Ball::refresh(bool force)
{
	this->update_coords(force);
	Entity::refresh();
}

CollisionSide Ball::detectBorderCollision(vec2i coords)
{
	coords_t x = coords.x;
	coords_t y = coords.y;


	if (x < field->getMinX())
		return CollisionSide::LEFT;
	else if (x > field->getMaxX() - width + 1)
		return CollisionSide::RIGHT;
	else if (y < field->getMinY())
		return CollisionSide::UP;
	else if (y > field->getMaxY() - height + 1)
		return CollisionSide::DOWN;
	else 
		return CollisionSide::NONE;
}

void Ball::collision_action(CollisionSide collision)
{
	syslog(LOG_NOTICE, "COLLISION FIXED (Or Not?)");
	mirrorAngle(collision);
}

void Ball::mirrorAngle(CollisionSide side) 
{
	std::stringstream ss;
	ss << "Collision on: ";
	switch(side) {
		case CollisionSide::UP:
			ss << "UP";
			break;
		case CollisionSide::DOWN:
			ss << "DOWN";
			break;
		case CollisionSide::LEFT:
			ss << "LEFT";
			break;
		case CollisionSide::RIGHT:
			ss << "RIGHT";
			break;
		default:
			ss << "NONE";
			break;
	}

	if ((side == CollisionSide::DOWN && sin(angle) < 0) || 
		(side == CollisionSide::UP && sin(angle) > 0)) {
		angle = - angle;
	} else if ((side == CollisionSide::LEFT && cos(angle) < 0) ||
		(side == CollisionSide::RIGHT && cos(angle) > 0)) {
		angle = M_PI - angle;
	}

	ss << ' ' << angle << ' ' << x << ' ' << y;
	syslog(LOG_NOTICE, ss.str().c_str());
	refresh(true);
}

void Ball::move(vec2i coords, bool force)
{
	CollisionSide collision = detectBorderCollision(coords);

	if (collision != 0) {
		Entity::move(coords, force);
		mirrorAngle(collision);
	} else {
		Entity::move(coords, force);
	}
}

void Ball::setAngle(double angle)
{
	this->angle = angle;
}

void Ball::setVelocity(coords_t velocity)
{
	this->velocity = velocity;
}
