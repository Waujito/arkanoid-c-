#include "field.hpp"
#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <ncurses.h>
#include <syslog.h>
#include <sstream>

Field::Field(Terminal *term): 
	term(term), 
	width(term->getWidth()), height(term->getHeight())
{
}

Field::~Field()
{
	free(this->matrix);
	this->matrix = NULL;
}

int Field::init()
{
	this->registered_entities.push_back({});

	int *matarr = (int *)calloc(width*height, sizeof(int));
	int **matrix = (int **)calloc(height, sizeof(int *));

	for (size_t i = 0; i < height; i++)
	{
		matrix[i] = matarr + i*width;
	}

	this->matrix = matrix;

	std::stringstream ss;
	ss << width << ' ' << height;
	syslog(LOG_NOTICE, ss.str().c_str());

	return 0;
}

entity_description Field::register_entity(collision_callback callback, void *entity)
{
	entity_description desc = {
		.idx = entity_idx++,
		.position = {},
		.callback = callback,
		.entity = entity,
	};

	registered_entities.push_back(desc);

	return desc;
}

void Field::delete_entity(int idx)
{
	if (idx == -1) return;

	entity_description desc = registered_entities[idx];
	rectangle position = desc.position;

	for (size_t i = position.y; i < position.y + position.height; i++) {
		for (size_t j = position.x; j < position.x + position.width; j++) {
			if (matrix[i][j] == idx) matrix[i][j] = 0;
		}
	}

	registered_entities[idx] = {};
}

void Field::remove_from_screen(int idx)
{
	rectangle position = registered_entities[idx].position;

	for (size_t i = position.y; i < position.y + position.height; i++) {
		for (size_t j = position.x; j < position.x + position.width; j++) {
			if (matrix[i][j] == idx)
				mvaddch(i, j, ' ');
		}
	}
}

void Field::display_on_screen(int idx)
{
	rectangle position = registered_entities[idx].position;

	for (size_t i = position.y; i < position.y + position.height; i++) {
		for (size_t j = position.x; j < position.x + position.width; j++) {
			if (matrix[i][j] == idx)
				mvaddch(i, j, '#');
		}
	}
}


int Field::set_position(int idx, rectangle new_pos)
{
	if (idx == -1) return -1;

	rectangle old_pos = registered_entities[idx].position;

	remove_from_screen(idx);
	// Fill old position with zeroes
	for (size_t i = old_pos.y; i < old_pos.y + old_pos.height; i++) {
		for (size_t j = old_pos.x; j < old_pos.x + old_pos.width; j++) {
			if (matrix[i][j] == idx) matrix[i][j] = 0;
		}
	}

	// Check new position to be free
	for (size_t i = new_pos.y; i < new_pos.y + new_pos.height; i++) {
		for (size_t j = new_pos.x; j < new_pos.x + new_pos.width; j++) {
			if (matrix[i][j] != 0) return -1;
		}
	}

	// If everything is okey, claim new position
	for (size_t i = new_pos.y; i < new_pos.y + new_pos.height; i++) {
		for (size_t j = new_pos.x; j < new_pos.x + new_pos.width; j++) {
			matrix[i][j] = idx;
		}
	}

	registered_entities[idx].position = new_pos;
	display_on_screen(idx);


	this->refresh();


	return 0;
}

CollisionSide Field::update_position(int idx, rectangle new_pos)
{
	if (idx == -1) return CollisionSide::NONE;
	
	size_t xld = new_pos.x;
	size_t yld = new_pos.y;

	size_t ylu = new_pos.y+new_pos.height;

	size_t xrd = new_pos.x+new_pos.width;


	size_t up_col = 0, down_col = 0, left_col = 0, right_col = 0;
	for (size_t j = xld; j <=xrd; j++) {
		if (yld >= 1 && matrix[yld - 1][j] != 0 && matrix[yld - 1][j] != idx)
			up_col++;

		if (ylu + 1 < height && matrix[ylu + 1][j] != 0 && matrix[ylu + 1][j] != idx)
			down_col++;
	}

	for (size_t i = yld; i <=ylu; i++) {
		if (xld >= 1 && matrix[i][xld - 1] != 0 && matrix[i][xld - 1] != idx)
			left_col++;

		if (xrd + 1 < width && matrix[i][xrd + 1] != 0 && matrix[i][xrd+1] != idx)
			right_col++;
	}

	CollisionSide collision = CollisionSide::NONE;
	if (up_col != 0 && up_col >= down_col && up_col >= left_col && up_col >=right_col)
		collision = CollisionSide::UP;
	else if (down_col != 0 && down_col >= up_col && down_col >=left_col && down_col >= right_col)
		collision = CollisionSide::DOWN;
	else if (left_col != 0 && left_col >= up_col && left_col >=down_col && left_col >= right_col)
		collision = CollisionSide::LEFT;
	else if (right_col != 0) collision = CollisionSide::RIGHT;

	if (collision != CollisionSide::NONE) {
		std::stringstream ss;
		ss << "Collision detected! " << up_col << ' ' << down_col << ' ' << left_col << ' ' << right_col;
		syslog(LOG_NOTICE, ss.str().c_str());

		return collision;
	}
	
	this->set_position(idx, new_pos);

	return CollisionSide::NONE;
}

void Field::refresh()
{
	term->refresh();
}

size_t Field::getWidth() 
{
	return this->width;
}
size_t Field::getMinX()
{
	return term->getMinX();
}

size_t Field::getMaxX()
{
	return term->getMaxX();
}


size_t Field::getHeight()
{
	return this->height;
}

size_t Field::getMinY()
{
	return term->getMinY();
}

size_t Field::getMaxY()
{
	return term->getMaxY();
}

