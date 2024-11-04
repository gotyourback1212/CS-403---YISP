#include "Parser.h"
#include <stdexcept>
#include <iostream> 

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::get() {
    return tokens[current++];
}

void Parser::expect(TokenType type) {
    if (peek().type != type) {
        throw std::runtime_error("Unexpected token: " + peek().text);
    }
    ++current;
}

SExprPtr Parser::parseExpr() {
    Token token = peek();
    if (token.type == TokenType::NUMBER || token.type == TokenType::SYMBOL) {
        std::cout << "Is atom" << std::endl; 
        return parseAtom();
    } else if (token.type == TokenType::LPAREN) {
        std::cout << "Is list" << std::endl;
        return parseList();
    } else {
        throw std::runtime_error("Unexpected token: " + token.text);
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