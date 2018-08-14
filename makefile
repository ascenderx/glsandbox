LFLAGS = -lGL -lglfw
MFLAGS = -framework OpenGL -lglfw
CFLAGS = -Wall

linux: obj/one.o obj/draw.o
	gcc -o bin/one obj/* $(LFLAGS)

macos: obj/one.o obj/draw.o
	gcc -o bin/one obj/* $(MFLAGS)

obj/one.o: src/one.c
	gcc -c -o obj/one.o src/one.c $(CFLAGS)

obj/draw.o: src/draw.c src/draw.h
	gcc -c -o obj/draw.o src/draw.c $(CFLAGS)

clean:
	rm bin/*
	rm obj/*

