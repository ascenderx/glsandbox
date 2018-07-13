LFLAGS = -lglfw -framework OpenGL -framework Cocoa

all: one

one: one.c draw.h makefile
	clang -o one one.c $(LFLAGS)

clean:
	if [ -f one ]; then rm one; fi