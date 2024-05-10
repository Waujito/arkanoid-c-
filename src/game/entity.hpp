#pragma once

#include "field.hpp"

typedef double coords_t;

struct vec2i {
	coords_t x;
	coords_t y;
};

struct ct_rectangle {
	coords_t x;
	coords_t width;

	coords_t y;
	coords_t height;
};

rectangle ctrecToNorm(ct_rectangle t);

struct EntityProperties{
	coords_t x = -1;
	coords_t y = -1;

	bool xMovable = true;
	bool yMovable = true;

	char **pattern = NULL;
	coords_t height = 2;
	coords_t width = 8;

};

class Entity {
protected:
	coords_t x, y;
	coords_t height, width;
	char **pattern;

	bool xMovable, yMovable;

	Field *field;

	int field_idx = -1;
public:
	Entity(Field *field, EntityProperties props);

	~Entity();

	void init();
	
	vec2i get_coords();
	void set_coords(vec2i coords);

	coords_t get_x();
	coords_t get_y();

	void set_x(coords_t x);
	void set_y(coords_t y);
	void move(vec2i coords, bool force = false);

	virtual void collision_action(CollisionSide collision);

	void move_up(coords_t n = 1);
	void move_down(coords_t n = 1);
	void move_left(coords_t n = 1);
	void move_right(coords_t n = 1);

	void refresh();

	static void collision_callback(void * e);
};
