CFLAGS = -O3
LDFLAGS =
appname = main

all: $(appname)
clean:
	rm -f $(appname) *.o
.PHONY: all clean

sdl_cflags := $(shell sdl2-config --cflags)
sdl_libs := $(shell sdl2-config --libs)
override CFLAGS += $(sdl_cflags)
override LIBS += $(sdl_libs)

$(appname): main.o
	    $(CC) $(LDFLAGS) -o $@ $^ $(LIBS) -lSDL2_image
