#include "terminal.hpp"
#include "menu.hpp"

int main() {
	Terminal *term = new Terminal();

	int status = term->init();
	if (status != 0)
		return status;

	Menu *menu = new Menu(term);
	// menu->run_game();
	menu->run();

	term->~Terminal();
	return 0;
}
