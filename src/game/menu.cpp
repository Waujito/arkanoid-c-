#include "menu.hpp"
#include "player.hpp"
#include "ball.hpp"
#include "field.hpp"
#include "keycontroller.hpp"
#include <unistd.h>
#include "brick.hpp"

Menu::Menu(Terminal *term): term(term)
{}


void Menu::run()
{
	this->run_game();
}
void Menu::run_game()
{
	Field *field = new Field(term);
	field->init();

	Player *player = new Player(field);
	Ball *ball = new Ball(field, {});

	KeyController *controller = new KeyController(term, player);

	field->refresh();

	player->init();
	ball->init();

	int brick_width = 4;
      	int brick_height = 2;
	int bricks_in_row = (field->getMaxX() - field->getMinX()) / brick_width;
	int bricks_in_col = 5;

	for (int i = 0; i < bricks_in_col; i++) {
		for (int j = 0; j < bricks_in_row; j++) {
			Brick *brick = new Brick(field, j*brick_width + field->getMinX(), i*brick_height + field->getMinY(), brick_width, brick_height);
			brick->init();
		}
	}

	int status = 0;
	while (!status) {
		status = controller->awaitAction();
		ball->refresh();

		usleep(200);
	}

	field->~Field();
}
