#pragma once 

#ifndef SEXPR_H
#define SEXPR_H

#include <string>
#include <memory>
#include <list>
#include <variant>

class SExpr {
public:
    virtual ~SExpr() {}
    virtual void print() const = 0;
    virtual bool isTruthy() const = 0;
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
            bool isTruthy() const override { return value != 0; }
    };

    // Symbol Atom
    class Symbol : public Atom {
        public:
            std::string name;
            Symbol(const std::string& n) : name(n) {}
            void print() const override;
            bool isTruthy() const override { return name != "nil"; }
    };

    // String Atom FOR TESTING PURPOSES ONLY 
    class String : public Atom {
    public:
        std::string value;
        String(const std::string& val) : value(val) {}
        void print() const override;
        bool isTruthy() const override { return !value.empty(); }
    };


class List : public SExpr {
    public:
        std::list<SExprPtr> elements;
        List(const std::list<SExprPtr>& elems) : elements(elems) {}
        void print() const override;
        bool isTruthy() const override { return !elements.empty(); }
};

class Nil : public SExpr { 
    public: 
        void print() const override;
        bool isTruthy() const override { return false; }
}; 

class Truth : public SExpr { 
    public: 
        void print() const override;
        bool isTruthy() const override { return true; }
}; 

const SExprPtr NIL = std::make_shared<Nil>();
const SExprPtr TRUTH = std::make_shared<Truth>();

#endif // SXPR_H

