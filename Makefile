export 
ROOT_DIR := $(PWD)
CXX := g++
CC := gcc

CXX_FLAGS := -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare -pedantic -Ofast -std=c++23
CC_FLAGS := -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare -pedantic -Ofast -std=c23

SRC_DIR := $(shell realpath src)
BIN_DIR := $(shell realpath bin)
LIBS_DIR := $(BIN_DIR)/libs
OBJ_DIR := $(shell realpath obj)

.PHONY: all 
all: build 

run: build
	$(BIN_DIR)/app

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIBS_DIR)

	@$(MAKE) -C $(SRC_DIR)/lxdialog 
	@$(MAKE) -C $(SRC_DIR)/game 


.PHONY: clean
clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
