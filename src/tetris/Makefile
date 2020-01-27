CC := gcc
CFLAGS := -Wall
DFLAGS := -g
RFLAGS := -O2
TARGET := bin
NAME := tetris
SRC := src/tetris.c src/termio.c

all: debug

debug: 
	$(CC) $(CFLAGS) $(DFLAGS) -o $(TARGET)/$(NAME) $(SRC)

release: 
	$(CC) $(CFLAGS) $(RFLAGS) -o $(TARGET)/$(NAME) $(SRC)

clean: 
	rm $(TARGET)/*
