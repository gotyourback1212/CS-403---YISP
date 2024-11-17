#ifndef PARSER_H
#define PARSER_H

#include "SExpr.h"
#include "Token.h"
#include <list>

class Parser {
public:
    Parser(std::list<Token> tokens);

    std::list<Token> tokens;

    Token peek() const;
    Token get();
    void expect(TokenType type);

    SExprPtr parseExpr();
    SExprPtr parseAtom();

    void parsePrint(const std::list<SExprPtr>& elements);
};

#endif // PARSER_H





//SExprPtr parseList();