# Define compilator and flags
CC = g++
CFLAGS = -std=c++20 -Wall -pedantic -g -pthread -O2 -ftree-vectorize -march=native -DDEBUG
SHARED = -shared
NO_WIN = -mwindows
EXTENSION_EXE = exe

# Name
ENGINE_NAME = Ember

# Remove function
RM     = del /Q
NULLDEV = NUL
fixpath = $(subst /,\,$1)

# Directories
DIR_SRC = src
DIR_INC = inc
DIR_BUILD = build
DIR_TEST = test
DIR_LIB = $(DIR_BUILD)/lib
DIR_BIN = $(DIR_BUILD)/bin
DIR_OBJ = $(DIR_BUILD)/obj
DIR_EXT = $(DIR_INC)/External

LIBRARY = -L $(DIR_LIB) -lEmber -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lfreetype # ATTENTION A L'ORDRE DES INCLUSION DES LIBRAIRIES
INCLUDES = -I $(DIR_INC) -I $(DIR_EXT)

# Gald
GLAD_SRC = $(DIR_SRC)/glad/glad.c

# Files
SRC = $(wildcard $(DIR_SRC)/**/*.cpp) $(wildcard $(DIR_SRC)/*.cpp)
OBJ := $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o, $(SRC))

TEST_SRC := $(wildcard $(DIR_TEST)/*.cpp)
TEST_EXE := $(patsubst $(DIR_TEST)/%.cpp,$(DIR_BIN)/%.$(EXTENSION_EXE),$(TEST_SRC))

# Define new line command
define \n


endef

all: $(DIR_LIB)/$(ENGINE_NAME).lib $(DIR_BIN)/$(ENGINE_NAME).dll

# Shared library
$(DIR_BIN)/$(ENGINE_NAME).dll: $(OBJ)
	@echo "Building shared library..."
	$(CC) $(CFLAGS) $(SHARED) $^ -o $@ $(GLAD_SRC) $(INCLUDES) $(LIBRARY)

# Static library
$(DIR_LIB)/$(ENGINE_NAME).lib: $(OBJ)
	@echo "Building static library..."
	ar rcs $@ $^

# Build object files
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) $(LIBRARY)

# Build each test executable
$(DIR_BIN)/%.$(EXTENSION_EXE): $(DIR_TEST)/%.cpp
	$(CC) $(CFLAGS) $< -o $@ $(GLAD_SRC) $(INCLUDES) $(LIBRARY)

# Compile all tests
test: $(TEST_EXE)

# Help command
help:
	@echo Run "mingw32-make" to compile static and dynamic libraries.
	@echo Run "mingw32-make build/bin/test.exe" (replace test by the actual test file name) to compile a test file. List of the tests:
	$(foreach T,$(TEST_EXE), @echo    - mingw32-make $(T)${\n})

# Clean project
clean:
	-$(RM) $(call fixpath,$(DIR_BIN)/$(ENGINE_NAME).dll) > $(NULLDEV) 2>&1
	-$(RM) $(call fixpath,$(DIR_LIB)/$(ENGINE_NAME).lib) > $(NULLDEV) 2>&1
	-$(RM) $(call fixpath,$(OBJ)) > $(NULLDEV) 2>&1
	-$(RM) $(call fixpath,$(DIR_BIN)/*.exe) > $(NULLDEV) 2>&1