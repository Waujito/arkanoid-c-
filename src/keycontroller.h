#ifndef KEYCONTROLLER_H
#define KEYCONTROLLER_H

#include "player.h"
#include "terminal.h"

class KeyController {
private:
	Terminal *term;
	Player *player;
public:
	KeyController(Terminal *term, Player *player);

	void awaitAction();
};

#endif
