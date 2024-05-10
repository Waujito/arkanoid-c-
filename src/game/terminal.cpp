#include "terminal.h"

Terminal::Terminal() {}


Terminal::~Terminal()
{
	close();
}

int Terminal::init() 
{
	if (this->initialized) return 0;
	this->initialized = true;

	wnd = initscr();
	cbreak();
	noecho();
	clear();
	refresh();

	keypad(wnd, true);
	nodelay(wnd, true);
	curs_set(0);

	if (!has_colors()) {
		endwin();
		printf("Terminal does not support colors.\n");
		return 1;
	}

	start_color();
	use_default_colors();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	wbkgd(wnd, COLOR_PAIR(1));

	attron(A_BOLD);
	box(wnd, 0, 0);
	attroff(A_BOLD);
	
	int height, width;
	getmaxyx(wnd, height, width);
	
	this->height = height;
	this->width = width;
	this->min_x = 1;
	this->min_y = 1;
	this->max_x = width - 2;
	this->max_y = height - 2;

	this->refresh();

	return 0;
}

void Terminal::close()
{
	if (!this->initialized) return;

	endwin();
	this->wnd = NULL;
}

void Terminal::refresh()
{
	::refresh();
}

int Terminal::awaitInput()
{
	return ::wgetch(this->wnd);
}

bool Terminal::isInitialized()
{
	return this->initialized;
}

size_t Terminal::getWidth() 
{
	return this->width;
}
size_t Terminal::getMinX()
{
	return this->min_x;
}

size_t Terminal::getMaxX()
{
	return this->max_x;
}


size_t Terminal::getHeight()
{
	return this->height;
}

size_t Terminal::getMinY()
{
	return this->min_y;
}

size_t Terminal::getMaxY()
{
	return this->max_y;
}

