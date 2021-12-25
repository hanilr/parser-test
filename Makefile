# ANSI-C MAKEFILE #

CC = gcc
ansi = -std=c89

file = src/file.c
util = src/util.c
parser = src/parser.c
com = src/command.c
lib = $(file) $(util) $(parser) $(com)
main = src/main.c

ifeq ($(OS),Windows_NT)
	output = acc.exe
	debug = debug.exe
	delete = del
else
	output = acc
	debug = debug
	delete = rm
endif

.PHONY: run clean debug cleand

run: $(main) $(lib)
	$(CC) $(main) $(lib) -o $(output)

clean: $(output)
	$(delete) $(output)

debug: $(main) $(lib)
	$(CC) -g $(main) $(lib) -o $(debug)

cleand: $(debug)
	$(delete) $(debug)

# MADE BY @hanilr #