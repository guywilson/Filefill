###############################################################################
#                                                                             #
# MAKEFILE for Cloak application                                              #
#                                                                             #
# � Guy Wilson 2012                                                           #
#                                                                             #
# Build using Visual Studio C++                                               #
# Use 'nmake' to build with this makefile, 'nmake -a' to rebuild all          #
#                                                                             #
###############################################################################

# Source directory
SOURCE=src

# Build output directory
BUILD=build

# What is our target
TARGET=ff

# C compiler
C=gcc

# Linker
LINKER=gcc

DBG=-g

# C compiler flags
CFLAGS_REL=-c -Wall
CFLAGS_DBG=-c -Wall $(DBG)

CFLAGS=$(CFLAGS_REL)

#Linker flags
LFLAGS_REL=-lstdc++
LFLAGS_DBG=-lstdc++ $(DBG)

LFLAGS=$(LFLAGS_REL)

# Object files (in linker ',' seperated format)
OBJFILES=$(BUILD)/filefill.o

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/filefill.o: $(SOURCE)/filefill.c
	$(C) $(CFLAGS) -o $(BUILD)/filefill.o $(SOURCE)/filefill.c

$(TARGET): $(OBJFILES)
	$(LINKER) $(LFLAGS) -o $(TARGET) $(OBJFILES)
