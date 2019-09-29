CFLAGS = -O3
LDFLAGS =
appname = main

all: $(appname)
clean:
	rm -f $(appname) *.o

rb: 
	rm -f $(appname) *.o
	make all
.PHONY: all clean

sdl_cflags := $(shell sdl2-config --cflags)
sdl_libs := $(shell sdl2-config --libs) -lSDL2_image
override CFLAGS += $(sdl_cflags)
override LIBS += $(sdl_libs)

$(appname): main.o
	    $(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
