#pragma once

#include <vector>
#include "terminal.hpp"

struct entity_description;
typedef void (*collision_callback)(void *, entity_description);

struct rectangle {
	size_t x;
	size_t width = 0;

	size_t y;
	size_t height = 0;
};

struct entity_description {
	int idx;
	rectangle position;
	collision_callback callback;
	void *entity;
};

enum CollisionSide {
	DOWN = -2,
	UP = -1,
	NONE = 0,
	LEFT = 1,
	RIGHT = 2
};

class Field {
private:
	int **matrix;
	std::vector<entity_description> registered_entities;
	int entity_idx = 1;

	void remove_from_screen(int idx);
	void display_on_screen(int idx);

	Terminal *const term;
	const size_t width, height;

public:
	Field(Terminal *term);
	~Field();

	int init();

	entity_description register_entity(collision_callback callback, void *entity);
	void delete_entity(int idx);

	CollisionSide update_position(int idx, rectangle new_pos);
	int set_position(int idx, rectangle new_pos);

	void refresh();

	size_t getWidth();
	size_t getMinX();
	size_t getMaxX();

	size_t getHeight();
	size_t getMinY();
	size_t getMaxY();


};
