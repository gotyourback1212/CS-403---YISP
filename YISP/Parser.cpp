#include "Parser.h"
#include "Token.h"
#include <stdexcept>
#include <iostream> 

Parser::Parser(std::list<Token> tokens) : tokens(tokens) {}

Token Parser::peek() const {
    if (tokens.empty()) {
        throw std::runtime_error("No more tokens");
    }
    return tokens.front();
}

Token Parser::get() {
   if (tokens.empty()) {
        throw std::runtime_error("No more tokens");
    }
    Token token = tokens.front();
    tokens.pop_front();
    return token;
}

void Parser::expect(TokenType type) {
    if (peek().type != type) {
        throw std::runtime_error("Unexpected token: " + peek().text);
    }
    get();
}

SExprPtr Parser::parseExpr() {
   const Token token = get();
    if (token.type == TokenType::LPAREN) {
        // Parse a list
        std::list<SExprPtr> elements;
        while (peek().type != TokenType::RPAREN) {
            elements.push_back(parseExpr());
        }
        // Consume the closing RPAREN
        expect(TokenType::RPAREN);
        return std::make_shared<List>(elements);
    } else if (token.type == TokenType::NUMBER || token.type == TokenType::SYMBOL) {
        // Parse an atom
        tokens.push_front(token); // Put the token back for parseAtom
        return parseAtom();
    } else {
        throw std::runtime_error("Unexpected token in expression: " + token.text);
    }

}

SExprPtr Parser::parseAtom() {
    Token token = get();
    if (token.type == TokenType::NUMBER) {
        std::cout << "Parsing number" << std::endl;
        return std::make_shared<Number>(std::stoi(token.text));
    } else if (token.type == TokenType::SYMBOL) {
        std::cout << "Parsing symbol" << std::endl;
        return std::make_shared<Symbol>(token.text);
    } else {
        throw std::runtime_error("Invalid atom: " + token.text);
    }
}





/*
SExprPtr Parser::parseList() {
    expect(TokenType::LPAREN);
    std::vector<SExprPtr> elements;

    std::cout << "Parsing List" << std::endl;
    while (peek().type != TokenType::RPAREN) {
        elements.push_back(parseExpr());
    }
    expect(TokenType::RPAREN);
    return std::make_shared<List>(elements);
}
*/ 