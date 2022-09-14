CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include


all : bin/c_compiler bin/compiler

bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

bin/compiler : src/compiler.cpp src/parser.tab.o src/lexer.yy.o   
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y 
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex
clean :
	rm -f src/*.o
	rm -rf bin/*
	rm -f src/parser.tab.*
	rm -f src/lexer.yy.*
	rm -f *.o
	rm -f *.s