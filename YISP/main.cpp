#include "Token.h"
#include "Parser.h"
#include "Eval.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>

void processLine(const std::string& line, Eval& eval) {
   try {
        // Tokenize the input line
        std::list<Token> tokens = tokenize(line);

        // Skip empty lines or lines with no meaningful tokens
        if (tokens.size() <= 1) { // Only contains `END` token
            return;
        }

        // Parse and evaluate the expression
        Parser parser(tokens);
        SExprPtr expr = parser.parseExpr();
        if (expr) {
            eval.evaluate(expr); // Evaluate the parsed expression
            std::cout << std::endl; 
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void repl(const std::string& filename = "") {
    EnvironmentPtr env = std::make_shared<Environment>();
    Eval eval(env);
    
    if (!filename.empty()) {
        // Read expressions from the file
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            processLine(line, eval);
        }
    } else {
        // Interactive REPL
        std::cout << "Lisp Interpreter REPL. Type 'exit' to quit.\n";
        std::string line;
        while (true) {
            std::cout << ">>> ";
            if (!std::getline(std::cin, line)) {
                break;
            }
            if (line == "exit") {
                break;
            }
            processLine(line, eval);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        // File mode
        repl(argv[1]);
    } else {
        // Interactive REPL
        repl();
    }
    return 0;
}