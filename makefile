CXX=g++
CXXFLAGS=-O2 -Wall -fdiagnostics-color=always -std=c++11

CC=gcc
CFLAGS=-O2 -Wall -fdiagnostics-color=always -std=c11

OBJ = tv_parser.*
OBJ_C = tv_parser_c.*

all: tv_parser tv_parser_c

tv_parser.o: tv_parser.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

tv_parser_c.o: tv_parser_c.c
	$(CC) -c -o $@ $< $(CFLAGS)

tv_parser: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

tv_parser_c: $(OBJ_C)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ tv_parser tv_parser_c