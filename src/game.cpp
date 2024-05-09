#include "game.h"
#include "player.h"
#include "ball.h"
#include "keycontroller.h"
#include <unistd.h>
#include <syslog.h>
#include <sstream>

void run(Field *field)
{
	
	Player *player = new Player(field);
	Ball *ball = new Ball(field);

	KeyController *controller = new KeyController(field, player);

	field->refresh();

	player->init();
	ball->init();

	while (1) {
		controller->awaitAction();
		ball->refresh();


		usleep(200);
	}

}
