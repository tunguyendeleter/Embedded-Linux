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
INC_FILES := $(wildcard $(INC_DIR)/*.h)
INC_LIST := $(notdir $(INC_FILES))

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_LIST := $(notdir $(SRC_FILES))

# Object files (based on source files, in the obj directory)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_LIST := $(notdir $(OBJ_FILES))

# Main source files (executables)
MAIN_SRC := chat
MAIN_LIST := $(MAIN_SRC)
MAIN_SRC := $(MAIN_SRC:%=$(OBJ_DIR)/%.o)

# GCC flags
CFLAGS := -pthread

# Default target (compiles everything)
all: build_obj
	@mkdir -p $(BIN_DIR)
	$(foreach file, $(MAIN_LIST), \
		gcc $(filter-out $(MAIN_SRC), $(OBJ_FILES)) $(OBJ_DIR)/$(file).o $(CFLAGS) -o $(BIN_DIR)/$(file);)

# Rule to create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@mkdir -p $(OBJ_DIR)
	gcc -fPIC -c -I $(INC_DIR) $(CFLAGS) $< -o $@

# Build object files
build_obj: $(OBJ_FILES)

# Rule to create static lib
build_static_lib:
	@mkdir -p $(STATIC_DIR)
	ar rcs $(STATIC_DIR)/libhello.a $(filter-out $(MAIN_SRC:%=$(OBJ_DIR)/%.o),$(OBJ_FILES))

# Rule to create shared lib
build_dynamic_lib:
	@mkdir -p $(SHARED_DIR)
	gcc -shared $(filter-out $(MAIN_SRC:%=$(OBJ_DIR)/%.o),$(OBJ_FILES)) -o $(SHARED_DIR)/libhello.so

# Clean build files
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(STATIC_DIR) $(SHARED_DIR)

# Print Makefile variables
print-%:
	@echo $($*)
