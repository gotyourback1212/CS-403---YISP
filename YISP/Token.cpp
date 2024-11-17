#include "Token.h"
#include <cctype>
#include <list>

std::list<Token> tokenize(const std::string& input) {
    std::list<Token> tokens;
    size_t i = 0;
    while (i < input.length()) {
        if (std::isspace(input[i])) {
            ++i;
        } else if (input[i] == '(') {
            tokens.push_back({TokenType::LPAREN, "("});
            ++i;
        } else if (input[i] == ')') {
            tokens.push_back({TokenType::RPAREN, ")"});
            ++i;
        } else {
            // Alphanumeric or symbol token
            size_t start = i;
            while (i < input.length() && 
                   !std::isspace(input[i]) && 
                   input[i] != '(' && 
                   input[i] != ')') {
                ++i;
            }
            std::string token = input.substr(start, i - start);

            // Treat any token with non-digit characters as a SYMBOL
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

    tokens.push_back({TokenType::END, ""});
    return tokens;
}