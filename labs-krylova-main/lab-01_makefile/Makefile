.PHONY: all prepare compile link clean
CFLAGS = -c -Wall -Werror -Wextra

INCLUDES = -Iinclude
CC = gcc

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi


compile: obj/main.o obj/io.o obj/algorithm.o obj/util.o

obj/main.o : src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) src/main.c -o obj/main.o

obj/io.o : src/io.c
	$(CC) $(CFLAGS) $(INCLUDES) src/io.c -o obj/io.o

obj/algorithm.o : src/algorithm.c
	$(CC) $(CFLAGS) $(INCLUDES) src/algorithm.c -o obj/algorithm.o

obj/util.o : src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) src/util.c -o obj/util.o

link: lab-01_makefile

lab-01_makefile: obj/main.o obj/io.o obj/algorithm.o obj/util.o
	$(CC) obj/*.o -o lab-01_makefile

clean :
	rm -rf obj/*.o lab-01_makefile



