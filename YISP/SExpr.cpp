#include "SExpr.h"
#include <iostream>

void Number::print() const {
    std::cout << value; 
}

void Symbol::print() const {
    std::cout << name;
}


void List::print() const {
    std::cout << "(";
    for (size_t i = 0; i < elements.size(); ++i) {
        elements[i]->print();
        if (i != elements.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << ")";
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