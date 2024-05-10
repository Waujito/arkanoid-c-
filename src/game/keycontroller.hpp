#pragma once 

#include "player.hpp"
#include "terminal.hpp"

class KeyController {
private:
	Terminal *term;
	Player *player;
public:
	KeyController(Terminal *term, Player *player);

	int awaitAction();
};
