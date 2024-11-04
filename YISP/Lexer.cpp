#include "Lexer.h"
#include <cctype>

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
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
        } else if (std::isdigit(input[i])) {
            size_t start = i;
            while (i < input.length() && std::isdigit(input[i])) {
                ++i;
            }
            tokens.push_back({TokenType::NUMBER, input.substr(start, i - start)});
        } else {
            size_t start = i;
            while (i < input.length() && !std::isspace(input[i]) && input[i] != '(' && input[i] != ')' && input[i] != '.') {
                ++i;
            }
            tokens.push_back({TokenType::SYMBOL, input.substr(start, i - start)});
        }
    }
    tokens.push_back({TokenType::END, ""});
    return tokens;
}