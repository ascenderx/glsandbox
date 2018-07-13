LFLAGS = -lGL -lglfw
CFLAGS = -Wall

all: bin/one

bin/one: obj/one.o obj/draw.o
	gcc -o bin/one obj/* $(LFLAGS)

obj/one.o: src/one.c
	gcc -c -o obj/one.o src/one.c $(CFLAGS)

obj/draw.o: src/draw.c src/draw.h
	gcc -c -o obj/draw.o src/draw.c $(CFLAGS)

clean:
	rm bin/*
	rm obj/*

