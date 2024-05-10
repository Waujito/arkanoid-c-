PATH_DIFF := $(shell realpath -m --relative-to="$(SRC_DIR)" -- $(CURDIR))

ROBJ_DIR := $(OBJ_DIR)
OBJ_DIR := $(OBJ_DIR)/$(PATH_DIFF)

APP := $(BIN_DIR)/app

SRCS := $(shell find . -name '*.c' -type f -printf '%P\n' -o -name '*.cpp' -type f -printf '%P\n')
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

LDFLAGS := -lncurses


.PHONY: all prepare
all: prepare $(APP)

prepare:
	@mkdir -p $(OBJ_DIR)

$(APP): $(OBJS)
	$(CXX) $(OBJS) -o $(APP) $(LDFLAGS) 
	@echo 'LD $(APP)'


$(OBJ_DIR)/%.c.o: %.c
	@echo 'CC $@'
	@$(CC) -c $(CC_FLAGS) $^ -o $@

$(OBJ_DIR)/%.cpp.o: %.cpp
	@echo 'CXX $@'
	@$(CXX) -c $(CXX_FLAGS) $^ -o $@
