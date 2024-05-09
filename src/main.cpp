#include "game.h"

int main() {
	Field *field = new Field();

	int status = field->init();
	if (status != 0)
		return status;

	run(field);

	field->~Field();
	return 0;
}
