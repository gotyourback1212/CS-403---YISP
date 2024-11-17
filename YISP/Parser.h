#ifndef PARSER_H
#define PARSER_H

#include "SExpr.h"
#include "Token.h"
#include <list>

class Parser {
public:
    Parser(std::list<Token> tokens);

    SExprPtr parseExpr();
    SExprPtr parseAtom();

private:
    std::list<Token> tokens;

    Token peek() const;
    Token get();
    void expect(TokenType type);
};

#endif // PARSER_H





//SExprPtr parseList();