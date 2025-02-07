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

        // Handle quoted strings
        else if (input[i] == '"') {
            ++i; // Move past the opening quote
            std::string strValue;

            while (i < input.length() && input[i] != '"') {
                strValue += input[i];
                ++i;
            }

            if (i < input.length() && input[i] == '"') {
                ++i; // Include the closing quote
                tokens.push_back({TokenType::STRING, strValue});
            } else {
                throw std::runtime_error("Unterminated string literal");
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

        // Negative numbers (standalone)
        else if (input[i] == '-' && i + 1 < input.length() && std::isdigit(input[i + 1])) {
            // Handle negative numbers
            size_t start = i;
            ++i; // Move past the negative sign
            while (i < input.length() && std::isdigit(input[i])) {
                ++i;
            }
            tokens.push_back({TokenType::NUMBER, input.substr(start, i - start)});
        }

        // Alphanumeric or symbol token (including symbols starting with digits)
        else {
            size_t start = i;
            while (i < input.length() &&
                   !std::isspace(input[i]) &&
                   input[i] != '(' &&
                   input[i] != ')' &&
                   input[i] != ';' &&
                   input[i] != '"') {
                ++i;
            }

            std::string token = input.substr(start, i - start);
            
            // Determine if the token is a number or symbol
            bool isNumber = true;
            for (char c : token) {
                if (!std::isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            // If the token is purely numeric, treat it as a number; otherwise, treat it as a symbol
            if (isNumber) {
                tokens.push_back({TokenType::NUMBER, token});
            } else {
                tokens.push_back({TokenType::SYMBOL, token});
            }
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}