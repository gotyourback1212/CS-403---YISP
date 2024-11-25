#include "Token.h"
#include <cctype>
#include <list>
#include <string>
#include <iostream> 

std::list<Token> tokenize(const std::string& input) {
    std::list<Token> tokens;
    size_t i = 0;

    while (i < input.length()) {
        // Skip whitespace
        if (std::isspace(input[i])) {
            ++i;
        }
        // Skip comments
        else if (input[i] == ';') {
            while (i < input.length() && input[i] != '\n') {
                ++i;
            }
        }
        // Left parenthesis
        else if (input[i] == '(') {
            tokens.push_back({TokenType::LPAREN, "("});
            ++i;
        }
        // Right parenthesis
        else if (input[i] == ')') {
            tokens.push_back({TokenType::RPAREN, ")"});
            ++i;
        }
        // Alphanumeric or symbol token
        else {
            size_t start = i;
            while (i < input.length() && 
                   !std::isspace(input[i]) && 
                   input[i] != '(' && 
                   input[i] != ')' && 
                   input[i] != ';') {
                ++i;
            }
            std::string token = input.substr(start, i - start);

            // Recognize special constants
            if (token == "#T") {
                tokens.push_back({TokenType::SYMBOL, "#T"});
            } else if (token == "nil") {
                tokens.push_back({TokenType::SYMBOL, "nil"});
            } else {
                // Determine if the token is a number
                bool isNumber = true;
                for (char c : token) {
                    if (!std::isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }

                if (isNumber) {
                    tokens.push_back({TokenType::NUMBER, token});
                } else {
                    tokens.push_back({TokenType::SYMBOL, token});
                }
            }
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}