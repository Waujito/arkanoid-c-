#include "menu.h"
#include "player.h"
#include "ball.h"
#include "field.h"
#include "keycontroller.h"
#include <unistd.h>


Menu::Menu(Terminal *term): term(term)
{}

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

	int status = 0;
	while (!status) {
		status = controller->awaitAction();
		ball->refresh();

		usleep(200);
	}

	field->~Field();
}
