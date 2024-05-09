# Compilation
CC=g++
CC_FLAGS=-Wall 

# dirs
SRC_DIR=src
BIN_DIR=bin

SOURCES=$(SRC_DIR)/*.cpp

TARGET=app

DEL_FILE	= rm -f
LIBS_DIRS	= -I./include/
LIBS		= $(LIBS_DIRS) -lncursesw


.PHONY: clean build
all: clean build

build: $(SOURCE)
	$(CC) $(CC_FLAGS) $(LIBS) $(SOURCES) -o $(BIN_DIR)/$(TARGET)

run:
	./$(BIN_DIR)/$(TARGET)

clean:
	$(DEL_FILE) $(BIN_DIR)/*
