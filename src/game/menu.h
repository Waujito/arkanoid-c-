#pragma once

#include "terminal.h"

class Menu {
private:
	Terminal *const term;
public:
	Menu(Terminal *term);

	void run_game();
};
