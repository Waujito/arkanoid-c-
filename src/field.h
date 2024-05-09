#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "terminal.h"

typedef void (*collision_callback)(void *);

struct rectangle{
	size_t x;
	size_t width = 0;

	size_t y;
	size_t height = 0;
};

struct entity_description{
	int idx;
	rectangle position;
	collision_callback callback;
	void *entity;
};

enum CollisionSide{
	DOWN = -2,
	UP = -1,
	NONE = 0,
	LEFT = 1,
	RIGHT = 2
};

class Field: public Terminal {
private:
	int **matrix;
	std::vector<entity_description> registered_entities;
	int entity_idx = 1;

	void remove_from_screen(int idx);
	void display_on_screen(int idx);
public:
	Field();
	~Field();

	virtual int init() override;

	entity_description register_entity(collision_callback callback, void *entity);
	void delete_entity(int idx);

	CollisionSide update_position(int idx, rectangle new_pos);
	int set_position(int idx, rectangle new_pos);
};

#endif
