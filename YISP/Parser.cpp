#include "Parser.h"
#include "Token.h"
#include <stdexcept>
#include <iostream> 

Parser::Parser(std::list<Token>& tokens) : tokens(tokens) {}

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
   if (tokens.empty()) { //Makes sure expression is not empty
        throw std::runtime_error("Unexpected end of input while parsing expression");
    }

    const Token token = get();
    if (token.type == TokenType::LPAREN) {
        // Parse a list

        if (peek().type == TokenType::RPAREN) {
            // If the next token is a closing parenthesis, it's an empty list
            get(); // Consume the RPAREN
            return NIL; // Return the global NIL object
        }

        std::list<SExprPtr> elements;
        while (peek().type != TokenType::RPAREN) {
            elements.push_back(parseExpr());
            if (tokens.empty()) {
                throw std::runtime_error("Mismatched parentheses: missing ')'");
            }
        }
        // Consume the closing RPAREN
        expect(TokenType::RPAREN);

        return std::make_shared<List>(elements);
    } else if (token.type == TokenType::NUMBER || token.type == TokenType::SYMBOL || token.type == TokenType::STRING) {
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
        //std::cout << "Parsing number" << std::endl;
        return std::make_shared<Number>(std::stoi(token.text));
    } else if (token.type == TokenType::STRING) {
        //std::cout << "Parsing string" << std::endl;
        return std::make_shared<String>(token.text);
    } else if (token.type == TokenType::SYMBOL) {
        //std::cout << "Parsing symbol" << std::endl;
        if (token.text == "nil") {
            return NIL; 
        } else if (token.text == "#T") {
            return TRUTH; 
        } else {
            return std::make_shared<Symbol>(token.text);
        }
    } else {
        throw std::runtime_error("Invalid atom: " + token.text);
    }
}

