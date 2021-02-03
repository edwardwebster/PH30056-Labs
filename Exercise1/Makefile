# ====================================================================================== #
#                                   From the Author                                      #
# ====================================================================================== #
# ! The purpose of this Makefile is to build the Exercise1 C++ Files
# ! Each .cpp file is a separate target
# ! Created by Edward Webster

# ====================================================================================== #
#                                 Variables of the Makefile                              #
# ====================================================================================== #

CXX     = clang++

CXXFLAGS = -Wall -Wextra -g -O0

IFLAGS = -I/usr/local/include -I/usr/include

LFLAGS = -L/usr/local/lib -lm -framework OpenGL -framework GLUT

# ------------------------------------------
# FOR GENERIC MAKEFILE:
# 1 - Binary directory
# 2 - Source directory
# 3 - Executable name
# 4 - Sources names
# 5 - Dependencies names
# ------------------------------------------
BIN = .
SOURCE = .
EXEC = ./run
SOURCES = $(wildcard $(SOURCE)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# ====================================================================================== #
#                                   Targets of the Makefile                              #
# target_name : dependency                                                               #
# <tabulation> command                                                                   #
# ====================================================================================== #

# ------------------------------------------
# ! - all : Compiles everything
# ! - help : Shows this help
# ! - clean : erases all object files *.o
# !           and all binary executables
# ------------------------------------------
run : $(BIN)/run

help :
	@grep -E "^# !" Makefile | sed -e 's/# !/ /g'

reset:
	rm -f $(EXEC) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

# ------------------------------------------
# Executable for files
# ------------------------------------------

#main:
#	$(CXX) $@.cpp -o $(EXEC) $(IFLAGS) $(LFLAGS)

$(SOURCES:.cpp=)/%:
	$(CXX) $@.cpp -o $(EXEC) $(IFLAGS) $(LFLAGS)
