# Author: Edson Alves - edsonalves@unb.br
# Date: 21/12/2012

# Library description
lib_LTLIBRARIES = 

# Programs excluded from instalation
bin_PROGRAMS = ninjasiege

# Library flags
# libitem_la_LDFLAGS = -static

# Library sources
# libitem_la_SOURCES = 

# Libraries needed to build our library
# libitem_la_LIBADD = 

# Program description
ninjasiege_SOURCES = game.cpp main.cpp sound.cpp environment.cpp event.cpp screen.cpp button.cpp \
game_processInputs.cpp
#ninjasiege_SOURCES = *.cpp

# Libraries needed to build program
ninjasiege_LDADD = -lSDL -lSDL_ttf -lSDL_image -lm

# Include flags
INCLUDES = -I../include -Wall -Wno-long-long -W -pedantic -ansi

