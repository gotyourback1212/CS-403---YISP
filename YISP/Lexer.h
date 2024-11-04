#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    NUMBER,
    SYMBOL,
    LPAREN,
    RPAREN,
    END
};

struct Token {
    TokenType type;
    std::string text;
};

std::vector<Token> tokenize(const std::string& input);

#endif // LEXER_H