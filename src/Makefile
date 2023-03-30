CC = gcc
CFLAGS = -Wall -Wextra -std=c11 

LIBS = -lcheck


ifeq ($(shell uname), Linux)
	LINUX_LIBS=-lsubunit -lrt -lpthread -lm
endif

.PHONY: install uninstall build test dist dvi clean 
all: install tests

build:
	gcc -c $(CFLAGS) parser.c parser.h
	gcc -c $(CFLAGS) transformations.c transformations.h

tests: build
	gcc test.c $(CFLAGS) *.o -o out $(LIBS) $(LINUX_LIBS)
	./out


install:
	rm -rf build_3d
	mkdir build_3d
	cd build_3d/ && qmake ../3d && make
	

dvi:
	open READMI.md

uninstall: clean
	rm -rf build_3d

dist:
	rm -rf dist_3d
	mkdir dist_3d
	tar -cf dist_3d/3d.tar build_3d

gcov_report: test.c build
	clear
	gcc test.c *.o -o coverage.o $(LIBS) $(LINUX_LIBS) -fprofile-arcs -ftest-coverage  
	./coverage.o
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage
	open coverage/index.html

clean:
	- rm *.o *.h.gch
	- rm -rf *.gcda *.gcno *.info
	- rm -rf coverage 
	- rm -rf out
	- rm -rf dist_3d
	

leaks: all
	valgrind --leak-check=full  --track-origins=yes ./out