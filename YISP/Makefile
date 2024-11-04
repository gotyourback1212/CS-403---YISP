CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: main

main: main.cpp Lexer.cpp Parser.cpp SExpr.cpp
	$(CXX) $(CXXFLAGS) -o lisp_interpreter main.cpp Lexer.cpp Parser.cpp SExpr.cpp

clean:
	rm -f lisp_interpreter