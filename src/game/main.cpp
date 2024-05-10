#include "terminal.h"
#include "menu.h"

int main() {
	Terminal *term = new Terminal();

	int status = term->init();
	if (status != 0)
		return status;

	Menu *menu = new Menu(term);
	menu->run_game();

	term->~Terminal();
	return 0;
}
