
#ifndef TERMINAL_H
#define TERMINAL_H
#include <ncurses.h>
#include <cstdint>

#define size_t uint_fast16_t

class Terminal {
protected:
	WINDOW* wnd = NULL;

	size_t width;
	size_t min_x;
	size_t max_x;

	size_t height;
	size_t min_y;
	size_t max_y;

	bool initialized;
public:
	Terminal();
	~Terminal();

	virtual int init();	
	bool isInitialized();

	void close();

	size_t getWidth();
	size_t getMinX();
	size_t getMaxX();


	size_t getHeight();
	size_t getMinY();
	size_t getMaxY();

	void refresh();

	int awaitInput();
};

#endif
