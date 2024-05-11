#pragma once

#include "terminal.hpp"

class Menu {
private:
	Terminal *const term;
public:
	Menu(Terminal *term);

	void run_game();
	void run();
};
