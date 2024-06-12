# Compiler & Linker
CXX				= g++

# Directory
OUTPUT_FOLDER   = bin
SOURCE_FOLDER	= src
PROGRAM_NAME	= main

# Flags
WARNING_CFLAG	=
DEBUG_CFLAG		= -ggdb
OBJECT_CFLAG	= -c
CPP_VERSION		= -std=c++17
CFLAGS			= $(CPP_VERSION) $(OBJECT_CFLAG) $(DEBUG_CFLAG) $(WARNING_CFLAG) -I$(SOURCE_FOLDER)

# Commands
ifeq ($(OS), Windows_NT)
	RM_O	  = for %%f in ($(OUTPUT_FOLDER)\*.o) do del /Q %%f
	EXT       = .exe
	CLEAR     = cls
else
	RM_O	  = rm -f $(OUTPUT_FOLDER)/*.o
	EXT	      =
	CLEAR     = clear
endif


# Makefile commands
build:
	@$(CXX) $(CFLAGS) $(SOURCE_FOLDER)/main.cpp -o $(OUTPUT_FOLDER)/main.o
	@$(CXX) $(CFLAGS) $(SOURCE_FOLDER)/Graph.cpp -o $(OUTPUT_FOLDER)/Graph.o
	@$(CXX) $(CFLAGS) $(SOURCE_FOLDER)/DFS.cpp -o $(OUTPUT_FOLDER)/DFS.o
	@$(CXX) $(CFLAGS) $(SOURCE_FOLDER)/NFA.cpp -o $(OUTPUT_FOLDER)/NFA.o
	@$(CXX) $(CFLAGS) $(SOURCE_FOLDER)/Program.cpp -o $(OUTPUT_FOLDER)/Program.o
	@$(CXX) $(OUTPUT_FOLDER)/*.o -o $(OUTPUT_FOLDER)/$(PROGRAM_NAME)
	@$(RM_O)
run:
	@$(CLEAR)
	@$(OUTPUT_FOLDER)/$(PROGRAM_NAME)$(EXT)
all: build run
