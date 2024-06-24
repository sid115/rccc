# Define the compiler and the flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lm

# Define the output executable name
OUTPUT = rccc

# Define the source files
SRC = rccc.c

# Determine the platform
UNAME_S := $(shell uname -s)

# Platform-specific settings
ifeq ($(UNAME_S), Linux)
	EXE := $(OUTPUT)
	RM := rm -f
	INSTALL_DIR := /usr/local/bin
else ifeq ($(UNAME_S), Darwin)
	EXE := $(OUTPUT)
	RM := rm -f
	INSTALL_DIR := /usr/local/bin
else ifeq ($(OS), Windows_NT)
	EXE := $(OUTPUT).exe
	RM := del /F /Q
	INSTALL_DIR := C:\Program Files\$(OUTPUT)
else
	$(error Unsupported platform)
endif

# Default target
all: $(EXE)

# Build the executable
$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Install target
install: $(EXE)
ifeq ($(OS), Windows_NT)
	if not exist "$(INSTALL_DIR)" mkdir "$(INSTALL_DIR)"
	copy "$(EXE)" "$(INSTALL_DIR)\$(EXE)"
else
	install -D $(EXE) $(INSTALL_DIR)/$(EXE)
endif

# Clean target
clean:
	$(RM) $(EXE)

.PHONY: all clean install
