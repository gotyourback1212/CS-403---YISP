#ifndef PARSER_H
#define PARSER_H

#include "SExpr.h"
#include "Lexer.h"
#include <vector>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    SExprPtr parseExpr();

private:
    const std::vector<Token>& tokens;
    size_t current;

    Token peek() const;
    Token get();
    void expect(TokenType type);

    SExprPtr parseAtom();
    SExprPtr parseList();
};

#endif // PARSER_H