#include "entity.hpp"
#include <cmath>
#include <cstring>
#include <syslog.h>
#include <sstream>

char **default_pattern(size_t height, size_t width)
{
	char *c = (char *)malloc(height*width*sizeof(char));
	char **pattern = (char **)malloc(sizeof(char *)*height);
	for (size_t i = 0; i < height; i++) {
		pattern[i] = c + width*i;
	}

	memset(c, '#', height*width);

	return pattern;
}

Entity::Entity(Field *field, EntityProperties props): field(field) 
{
	this->x = props.x;
	this->y = props.y;

	this->height = props.height;
	this->width = props.width;

	this->x = std::min(this->x, this->field->getMaxX() - this->width);
	this->y = std::min(this->y, this->field->getMaxY() - this->height);
	
	if (props.pattern != NULL)
		this->pattern = props.pattern;
	else 
		this->pattern = default_pattern(height, width);

	this->xMovable = props.xMovable;
	this->yMovable = props.yMovable;
	

	std::stringstream ss;
	ss << "Created Entity with coords " << x << ' ' << y << ' ' << " And sizes " << width << ' ' << height;
	syslog(LOG_NOTICE, ss.str().c_str());

}

Entity::~Entity()
{
	field->delete_entity(field_idx);
}

void Entity::init()
{
	this->field_idx = (field->register_entity(this->collision_callback, this)).idx;

	ct_rectangle pos = {x, width, y, height};

	if (field->set_position(this->field_idx, ctrecToNorm(pos))) {
		fprintf(stderr, "Unable to claim position! x: %f width: %f y: %f height: %f", x, width, y, height);
		exit(1);
	}
}


void Entity::refresh()
{
	field->refresh();
}


void Entity::collision_action(CollisionSide collision)
{
	return;
}

void Entity::move(vec2i coords, bool force)
{
	coords_t x = coords.x;
	x = std::min(std::max(x, (coords_t)field->getMinX()), (coords_t)field->getMaxX() - width + 1);

	coords_t y = coords.y;
	y = std::min(std::max(y, (coords_t)field->getMinY()), (coords_t)field->getMaxY() - height + 1);

	ct_rectangle pos = {x, width, y, height};


	if (!force){
		CollisionSide collision = field->update_position(
			field_idx, 
			ctrecToNorm(pos)
		);
		if (collision != CollisionSide::NONE) {
			return this->collision_action(collision);
		}
	}

	this->x = x;
	this->y = y;

	this->refresh();
}

void Entity::set_x(coords_t x)
{
	if (!xMovable) return;

	move({x, y});
}


void Entity::set_y(coords_t y)
{
	if (!yMovable) return;
	move({x, y});
}

coords_t Entity::get_x() { return this->x; }
coords_t Entity::get_y() { return this->y; }

void Entity::move_up(coords_t n) 
{
	this->set_y(this->y-n);
}


void Entity::move_down(coords_t n) 
{
	this->set_y(this->y+n);
}

void Entity::move_left(coords_t n) 
{
	this->set_x(this->x-n);
}

void Entity::move_right(coords_t n) 
{
	this->set_x(this->x+n);
}

vec2i Entity::get_coords()
{
	return {x, y};
}

void Entity::collision_callback(void *e)
{
	Entity *entity = (Entity *)e; 

	fprintf(stderr, "Collision detected: %d", entity->field_idx);
}

rectangle ctrecToNorm(ct_rectangle t)
{
	return {
		(size_t)t.x,
		(size_t)t.width,
		(size_t)t.y,
		(size_t)t.height
	};
}
