# Directories
PRJ_DIR := .
BIN_DIR := $(PRJ_DIR)/bin
OBJ_DIR := $(PRJ_DIR)/obj
INC_DIR := $(PRJ_DIR)/inc
SRC_DIR := $(PRJ_DIR)/src
LIB_DIR := $(PRJ_DIR)/lib
STATIC_DIR := $(LIB_DIR)/static
SHARED_DIR := $(LIB_DIR)/shared

# Header files 
INC_FILES := $(wildcard $(INC_DIR)/*)
INC_LIST := $(notdir $(INC_FILES))

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*)
SRC_LIST := $(notdir $(SRC_FILES))

# Object files (based on source files, in the obj directory)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_LIST := $(notdir $(OBJ_FILES))

# Main source code
MAIN_SRC := main
MAIN_SRC := $(MAIN_SRC:%=$(OBJ_DIR)/%.o)

# Default target
all: build_obj
	@mkdir -p $(BIN_DIR)
	gcc $(OBJ_FILES) -o $(BIN_DIR)/main

# Rule to create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc -fPIC -c -I $(INC_DIR) $< -o $@

# build object files
build_obj: $(OBJ_FILES)

# Rule to create static lib
build_static_lib:
	@mkdir -p $(STATIC_DIR)
	ar rcs $(STATIC_DIR)/libhello.a $(filter-out $(MAIN_SRC),$(OBJ_FILES))

# Rule to create shared lib
build_dynamic_lib:
	@mkdir -p $(SHARED_DIR)
	gcc -shared $(filter-out $(MAIN_SRC),$(OBJ_FILES)) -o $(SHARED_DIR)/libhello.so

# clean
clean:
	rm -rf $(BIN_DIR)/*
	rm -rf $(OBJ_DIR)/*
	rm -rf $(STATIC_DIR)/*
	rm -rf $(SHARED_DIR)/*

# Print variables 
print-%:
	@echo $($*)