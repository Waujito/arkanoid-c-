#! THANKS LINUX FOR MENUCONFIG :)

PATH_DIFF := $(shell realpath -m --relative-to="$(SRC_DIR)" -- $(CURDIR))

ROBJ_DIR := $(OBJ_DIR)
OBJ_DIR := $(OBJ_DIR)/$(PATH_DIFF)

LIB := $(LIBS_DIR)/lxdialog.a

SRCS := $(shell find . -name '*.c' -type f -printf '%P\n' -o -name '*.cpp' -type f -printf '%P\n')
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

.PHONY: all prepare
all: prepare $(LIB)

prepare:
	@mkdir -p $(OBJ_DIR)

$(LIB): $(OBJS)
	@echo 'AR $(LIB)'
	@ar rcs $(LIB) $^


$(OBJ_DIR)/%.c.o: %.c
	@echo 'CC $@'
	@$(CC) -c $(CC_FLAGS) $^ -o $@

$(OBJ_DIR)/%.cpp.o: %.cpp
	@echo 'CXX $@'
	@$(CXX) -c $(CXX_FLAGS) $^ -o $@
