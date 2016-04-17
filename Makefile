########################################################################
#                                                                       
#               Main Makefile for STOPWATCH project                     
#                                                                       
########################################################################
PROJECT     = stopwatch
INCLUDE_DIR = $(PWD)/include
OBJS        = $(patsubst %.cpp,%.o,$(sort $(wildcard src/*.cpp)))

CC          = @g++
STRIP       = @strip
MAKE        = @make -j1 --no-print-directory
ECHO        = @echo
CLEAN       = @rm -f

NORMAL      = "\033[0m"
PURPLE      = "\033[1;35m"
YELLOW      = "\033[0;33m"
GREEN       = "\033[0;32m"
CYAN        = "\033[1;36m"
RED         = "\033[1;31m"

LDFLAGS     = -static-libstdc++ \
              -static-libgcc    \
              -lsfml-graphics   \
              -lsfml-window     \
              -lsfml-system     \
              -ljansson         \
              -lm

CFLAGS      = -Wall                 \
              -Wextra               \
              -std=c++11            \
              -I$(INCLUDE_DIR)


all: info
	$(MAKE) $(PROJECT)


info:
	$(ECHO)
	$(ECHO) $(RED) "C  flags:" $(YELLOW) $(CFLAGS)  $(NORMAL)
	$(ECHO) $(RED) "LD flags:" $(YELLOW) $(LDFLAGS) $(NORMAL)
	$(ECHO) $(PURPLE) "Building: $(PROJECT)" $(NORMAL)
	$(ECHO)


$(PROJECT): $(OBJS)
	$(ECHO)
	$(ECHO) $(CYAN) Linking $(PROJECT) $(NORMAL)
	$(CC) $(OBJS) -o $(PROJECT) $(LDFLAGS)

	$(ECHO) $(CYAN) Stripping $(PROJECT) $(NORMAL)
	$(STRIP) $(PROJECT)


.cpp.o:
	$(ECHO) $(GREEN) "  Compiling: $(*F)" $(NORMAL)
	$(CC) $(CFLAGS) -o $@ -c $<


clean:
	$(ECHO) $(YELLOW) $(OBJS) $(PROJECT) $(NORMAL)
	$(CLEAN) $(OBJS) $(PROJECT)
