#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include <list>

enum class TokenType {
    NUMBER,
    SYMBOL,
    LPAREN,
    RPAREN,
    STRING,
    END
};

struct Token {
    TokenType type;
    std::string text;
};

std::list<Token> tokenize(const std::string& input);

#endif // TOKEN_H