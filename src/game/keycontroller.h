#pragma once 

#include "player.h"
#include "terminal.h"

class KeyController {
private:
	Terminal *term;
	Player *player;
public:
	KeyController(Terminal *term, Player *player);

	int awaitAction();
};
