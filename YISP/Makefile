CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: main

main: main.cpp Environment.cpp Eval.cpp Parser.cpp SExpr.cpp Token.cpp  
	$(CXX) $(CXXFLAGS) -o lisp_interpreter main.cpp Environment.cpp Eval.cpp Parser.cpp SExpr.cpp Token.cpp  

clean:
	rm -f lisp_interpreter