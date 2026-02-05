# Define compilator and flags
CC = g++
CFLAGS = -std=c++20 -Wall -pedantic -g -pthread -ftree-vectorize -march=native -DDEBUG # old
# CFLAGS = -std=c++20 -Wall -Wextra -Wshadow -Wconversion -g3 -fsanitize=address -fno-omit-frame-pointer -pthread -DDEBUG # Debugging
# CFLAGS = -std=c++20 -O2 -flto -funroll-loops -march=native -Wall -Wextra -pthread -DRELEASE # Release
CFLAGS += -DFT_STATIC_LIBRARY
CFLAGS += -gdwarf-2
SHARED = -shared
NO_WIN = -mwindows
EXTENSION_EXE = exe

# Name
ENGINE_NAME = Amber

# Remove function
RM = del /Q

# Directories
DIR_SRC = src
DIR_INC = inc
DIR_BUILD = build
DIR_TEST = test
DIR_LIB = $(DIR_BUILD)/lib
DIR_BIN = $(DIR_BUILD)/bin
DIR_OBJ = $(DIR_BUILD)/obj
DIR_EXT = $(DIR_INC)/External

LIBRARY = -L $(DIR_LIB) -l$(ENGINE_NAME) -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lfreetype # ATTENTION A L'ORDRE DES INCLUSION DES LIBRAIRIES
INCLUDES = -I $(DIR_INC) -I $(DIR_EXT)

# Gald
GLAD_SRC = $(DIR_SRC)/glad/glad.c
GLAD_OBJ = $(DIR_OBJ)/glad/glad.o
GLAD_INC = -I $(DIR_INC)

# Subdirectories for all the modules
SUBDIRECTORIES = $(wildcard $(DIR_SRC)/*/)

# Files
SRC = $(wildcard $(DIR_SRC)/**/*.cpp) $(wildcard $(DIR_SRC)/*.cpp)
OBJ := $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o, $(SRC))

TEST_SRC := $(wildcard $(DIR_TEST)/*.cpp)
TEST_EXE := $(patsubst $(DIR_TEST)/%.cpp,$(DIR_BIN)/%.$(EXTENSION_EXE),$(TEST_SRC))

# Define new line command
define \n


endef

all: $(DIR_LIB)/$(ENGINE_NAME).lib $(DIR_BIN)/$(ENGINE_NAME).dll

show:
	@echo $(GLAD_SRC)

glad:
	@echo "Building GLAD..."
	$(CC) $(CFLAGS) -c $(GLAD_SRC) -o $(GLAD_OBJ) $(GLAD_INC)

# Setup project, create folders if they do not exist
setup:
	@if not exist $(DIR_BUILD) (mkdir $(subst /,\,$(DIR_BUILD)))
	@if not exist $(DIR_BIN) (mkdir $(subst /,\,$(DIR_BIN)))
	@if not exist $(DIR_LIB) (mkdir $(subst /,\,$(DIR_LIB)))
	@if not exist $(DIR_OBJ) (mkdir $(subst /,\,$(DIR_OBJ)))
	$(foreach D, $(patsubst $(DIR_SRC)/%, $(DIR_OBJ)/%,$(SUBDIRECTORIES)), @if not exist $(D) (mkdir $(subst /,\,$(D)))$(\n) ) 

# Shared library
$(DIR_BIN)/$(ENGINE_NAME).dll: $(OBJ)
	@echo "Building shared library..."
	$(CC) $(CFLAGS) $(SHARED) $^ -o $@ $(GLAD_SRC) $(INCLUDES) $(LIBRARY)

# Static library
$(DIR_LIB)/$(ENGINE_NAME).lib: $(OBJ)
	@echo "Building static library..."
	ar rcs $@ $^ $(GLAD_OBJ)

# Build object files
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) $(LIBRARY)

# Build each test executable
$(DIR_BIN)/%.$(EXTENSION_EXE): $(DIR_TEST)/%.cpp
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDES) $(LIBRARY)

# Compile all tests
tests: $(TEST_EXE)

# Help command
help:
	@echo Makefile commands:
	@echo -------------------
	@echo  setup        		: Create the build folders if they do not exist.
	@echo  all          		: Compile object files, static and dynamic libraries.
	@echo  clean        		: Remove all compiled files (libraries, object files, executables).
	@echo  clean_tests  		: Remove all compiled test executables.
	@echo  help         		: Display this help message.
	@echo  tests         		: Compile all the test files in the test folder.
	@echo  glad         		: Compile GLAD library (to do before compiling library or tests).
	@echo  build/bin/test.exe 	: Replace test by the actual test file name to compile a test file. List of the tests:
	$(foreach T,$(TEST_EXE), @echo    + $(T)${\n})

# Clean project
clean:
	-$(RM) $(subst /,\,$(DIR_BIN)/$(ENGINE_NAME).dll)
	-$(RM) $(subst /,\,$(DIR_LIB)/$(ENGINE_NAME).lib)
	-$(RM) $(subst /,\,$(OBJ))
	-$(RM) $(subst /,\,$(DIR_BIN)/*.exe)
	-$(RM) $(subst /,\,$(GLAD_OBJ))

# Clean test files
clean_tests:
	-$(RM) $(subst /,\,$(DIR_BIN)/*.exe)