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

        // Parse the expression
        Parser parser(tokens);
        SExprPtr expr = parser.parseExpr();

        // Evaluate the expression
        if (expr) {
            SExprPtr result = eval.evaluate(expr);
            
            // Only print the result if it's not a `print` function, as `print` already handles output
            auto list = std::dynamic_pointer_cast<List>(expr);
            if (!list || !std::dynamic_pointer_cast<Symbol>(list->elements.front()) ||
                std::dynamic_pointer_cast<Symbol>(list->elements.front())->name != "print") {
                if (result) {
                    result->print();
                    std::cout << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void repl(const std::string& filename = "") {
    EnvironmentPtr env = std::make_shared<Environment>();
    FunctionEnvironmentPtr funcEnv = std::make_shared<FunctionEnvironment>();
    
    Eval eval (env, funcEnv);
    
    if (!filename.empty()) {
        // Read expressions from the file
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        std::string input;
        std::string line;
        int parenCount = 0;

        while (std::getline(file, line)) {
            input += line + " ";  // Accumulate the line in the input buffer

            // Update parentheses count
            for (char c : line) {
                if (c == '(') {
                    ++parenCount;
                } else if (c == ')') {
                    --parenCount;
                }
            }

            // If all parentheses are closed, process the input
            if (parenCount == 0 && !input.empty()) {
                processLine(input, eval);
                input.clear();  // Clear input after successful processing
            }
        }

        // In case there is remaining input after the file ends
        if (parenCount != 0) {
            std::cerr << "Error: Unmatched parentheses in input" << std::endl;
        }

    } else {
        // Interactive REPL
        std::cout << "Lisp Interpreter REPL. Type 'exit' to quit.\n";
        std::string input;
        int parenCount = 0;

        while (true) {
            std::cout << ((parenCount > 0) ? "... " : ">>> ");
            std::string line;
            if (!std::getline(std::cin, line)) {
                break;
            }
            if (line == "exit") {
                break;
            }

            input += line + " ";  // Add the line to the input buffer

            // Update parentheses count
            for (char c : line) {
                if (c == '(') {
                    ++parenCount;
                } else if (c == ')') {
                    --parenCount;
                }
            }

            // If all parentheses are closed, process the input
            if (parenCount == 0 && !input.empty()) {
                processLine(input, eval);
                input.clear();  // Clear input after successful processing
            }
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
