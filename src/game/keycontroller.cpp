#include <cstdlib>
#include "keycontroller.hpp"
#include <ncurses.h>

KeyController::KeyController(Terminal *term, Player *player): term(term), player(player)
{
}

int KeyController::awaitAction() {
	int in_char = term->awaitInput();
	
	switch(in_char) {
	case 'q':
		return 1;
		break;
	case KEY_UP:
	case 'w':
		player->move_up();
		break;
	case KEY_DOWN:
	case 's':
		player->move_down();
		break;
	case KEY_LEFT:
	case 'a':
		player->move_left(2);
		break;
	case KEY_RIGHT:
	case 'd':
		player->move_right(2);
		break;
	default:
		break;
	}

	return 0;
}
