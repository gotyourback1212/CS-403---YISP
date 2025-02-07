#include "SExpr.h"
#include <iostream>

void Number::print() const {
    std::cout << value; 
}

void Symbol::print() const {
    std::cout << name;
}

void Nil::print() const {
        std::cout << "nil";
}

void Truth::print() const {
        std::cout << "true";
}

void List::print() const {
    std::cout << "(";
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        (*it)->print();
        if (std::next(it) != elements.end()) {
            std::cout << " ";
        }
    }
    std::cout << ")";
}

void String::print() const {
    std::cout << value;
}




/*
void ConsCell::print() const {
    std::cout << "(";
    if (car) car->print();
    std::cout << " . ";
    if (cdr) cdr->print();
    std::cout << ")";
}
*/