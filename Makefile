# Compiler
CC = g++

# Directories
LIB_DIR = ./lib
INCLUDE_DIR = ./include
SHADER_DIR = ./shaders
BUILD_DIR = ./build

# Compiler flags for build types
CFLAGS_DEBUG = -g
CFLAGS_PRO = -O3 -march=native

# Library and include flags
LIB_FLAGS = -L$(LIB_DIR) -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lglad
INCLUDE_FLAGS = -I$(INCLUDE_DIR)

# Source files
SRCS = main.cpp  # Add more source files as needed

# Executable name
EXEC = MyApp

# Standard build
build:
	mkdir -p $(BUILD_DIR)
	cp -r $(SHADER_DIR) $(BUILD_DIR)/
	$(CC) $(SRCS) $(INCLUDE_FLAGS) $(LIB_FLAGS) -o $(BUILD_DIR)/$(EXEC)

# Debug build
build_debug:
	mkdir -p $(BUILD_DIR)
	cp -r $(SHADER_DIR) $(BUILD_DIR)/
	$(CC) $(SRCS) $(INCLUDE_FLAGS) $(LIB_FLAGS) $(CFLAGS_DEBUG) -o $(BUILD_DIR)/$(EXEC)

# Production build
build_pro:
	mkdir -p $(BUILD_DIR)
	cp -r $(SHADER_DIR) $(BUILD_DIR)/
	$(CC) $(SRCS) $(INCLUDE_FLAGS) $(LIB_FLAGS) $(CFLAGS_PRO) -o $(BUILD_DIR)/$(EXEC)