#pragma once 

#ifndef SEXPR_H
#define SEXPR_H

#include <string>
#include <memory>
#include <vector>
#include <variant>

class SExpr {
public:
    virtual ~SExpr() {}
    virtual void print() const = 0;
};

using SExprPtr = std::shared_ptr<SExpr>;

// Atom base class
class Atom : public SExpr {};

    // Number Atom
    class Number : public Atom {
    public:
        int value; 
        Number(int val) : value(val) {} 
        void print() const override;
    };

    // Symbol Atom
    class Symbol : public Atom {
    public:
        std::string name;
        Symbol(const std::string& n) : name(n) {}
        void print() const override;
    };

// List (for convenience)
class List : public SExpr {
public:
    std::vector<SExprPtr> elements;
    List(const std::vector<SExprPtr>& elems) : elements(elems) {}
    void print() const override;
};

#endif // SXPR_H



/*
// ConsCell
class ConsCell : public SExpr {
public:
    SExprPtr car;
    SExprPtr cdr;
    ConsCell(SExprPtr a, SExprPtr d) : car(a), cdr(d) {}
    void print() const override;
};

*/

