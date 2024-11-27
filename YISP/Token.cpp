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
            // Skip until the end of the line or input
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
        // Negative numbers or alphanumeric tokens
        else if (std::isdigit(input[i]) || (input[i] == '-' && i + 1 < input.length() && std::isdigit(input[i + 1]))) {
            // Handle numbers including negative numbers
            size_t start = i;
            if (input[i] == '-') {
                ++i; // Move past the negative sign
            }
            while (i < input.length() && std::isdigit(input[i])) {
                ++i;
            }
            tokens.push_back({TokenType::NUMBER, input.substr(start, i - start)});
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
            tokens.push_back({TokenType::SYMBOL, token});
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}