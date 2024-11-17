#include "Eval.h"
#include <stdexcept>
#include <iostream>
#include <memory>

// Evaluate the expression
SExprPtr Eval::evaluate(const SExprPtr& expr) {
    std::cout << "Eval expression" << std::endl; 
    if (!expr) {
            throw std::runtime_error("Null expression during evaluation");
        }

        // Handle Nil
        if (std::dynamic_pointer_cast<Nil>(expr)) {
            return expr; // Return NIL
        }

        // Handle List
        if (auto list = std::dynamic_pointer_cast<List>(expr)) {
            if (list->elements.empty()) {
                throw std::runtime_error("Cannot evaluate an empty list");
            }

            // The first element should be a symbol
            auto first = list->elements.front();
            auto symbol = std::dynamic_pointer_cast<Symbol>(first);
            if (!symbol) {
                throw std::runtime_error("Expected a symbol as the first element of a list");
            }

            // Handle special forms
            if (symbol->name == "print") {
                return evalPrint(*list); // Return the result of print
            } else if (symbol->name == "NIL?") {
                return evalIsNil(*list); // Return TRUTH or NIL
            } else if (symbol->name == "SYM?") {
                return evalIsSym(*list); // Return TRUTH or NIL
            } else if (symbol->name == "NUM?") {
                return evalIsNum(*list); // Return TRUTH or NIL
            } else if (symbol->name == "LIST?") {
                return evalIsList(*list); // Return TRUTH or NIL
            } else if(symbol->name == "cons"){
                return evalCons(*list); //Return the results of cons
            } else if(symbol->name == "car"){
                return evalCar(*list); //Return the results of cons
            } else if(symbol->name == "cdr"){
                return evalCdr(*list); //Return the results of cons
            } else {
                throw std::runtime_error("Unknown function: " + symbol->name);
            }
        }

    // Atomic values (Symbol, Number, etc.) evaluate to themselves
    return expr;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Evaluate `print` function
SExprPtr Eval::evalPrint(const List& list) {
    std::cout << "Eval print function" << std::endl; 
    if (list.elements.size() < 2) {
        throw std::runtime_error("print expects at least one argument");
    }

    SExprPtr lastResult = NIL; // Default to NIL if no arguments

    // Iterate through all arguments, evaluate them, and print results
    auto it = std::next(list.elements.begin()); // Skip the "print" symbol
    for (; it != list.elements.end(); ++it) {
        lastResult = evaluate(*it); // Fully evaluate the result
        lastResult->print();        // Print the evaluated result
        if (std::next(it) != list.elements.end()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl; // Add newline after printing all arguments

    return lastResult; // Return the last evaluated result
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Evaluate 'cons' funciton
SExprPtr Eval::evalCons(const List& list) {
    std::cout << "Eval cons function" << std::endl; 
    if (list.elements.size() != 3) {
        throw std::runtime_error("cons expects exactly two arguments");
    }

    // Evaluate the first argument (head of the list)
    auto head = evaluate(*std::next(list.elements.begin()));

    // Evaluate the second argument (tail of the list)
    auto tail = evaluate(*std::next(list.elements.begin(), 2));

    // Ensure the tail is a list or NIL
    auto tailList = std::dynamic_pointer_cast<List>(tail);
    if (!tailList && !std::dynamic_pointer_cast<Nil>(tail)) {
        throw std::runtime_error("The second argument to cons must be a list or NIL");
    }

    // Create the new list
    std::list<SExprPtr> newElements = {head};
    if (tailList) {
        newElements.insert(newElements.end(), tailList->elements.begin(), tailList->elements.end());
    }

    return std::make_shared<List>(newElements);
}

//Evaluate 'car' function
SExprPtr Eval::evalCar(const List& list) {
    std::cout << "Eval cdr function" << std::endl; 
    if (list.elements.size() != 2) {
        throw std::runtime_error("car expects exactly one argument");
    }

    // Evaluate the argument
    auto it = std::next(list.elements.begin()); // Skip the "car" symbol
    SExprPtr argument = evaluate(*it);          // Fully evaluate the argument

    // Ensure the argument is a list
    auto argList = std::dynamic_pointer_cast<List>(argument);
    if (!argList) {
        throw std::runtime_error("The argument to car must be a list");
    }

    // Ensure the list is not empty
    if (argList->elements.empty()) {
        throw std::runtime_error("Cannot take car of an empty list");
    }

    return argList->elements.front(); // Return the first element
}

//Evaluate 'cdr' function
SExprPtr Eval::evalCdr(const List& list) {
    std::cout << "Eval cdr function" << std::endl; 
    if (list.elements.size() != 2) {
        throw std::runtime_error("cdr expects exactly one argument");
    }

    // Evaluate the argument
    auto it = std::next(list.elements.begin()); // Skip the "cdr" symbol
    SExprPtr argument = evaluate(*it);          // Fully evaluate the argument

    // Ensure the argument is a list
    auto argList = std::dynamic_pointer_cast<List>(argument);
    if (!argList) {
        throw std::runtime_error("The argument to cdr must be a list");
    }

    // Ensure the list is not empty
    if (argList->elements.empty()) {
        throw std::runtime_error("Cannot take cdr of an empty list");
    }

    // Create a new list containing all but the first element
    std::list<SExprPtr> newElements(++argList->elements.begin(), argList->elements.end());
    return std::make_shared<List>(newElements);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Evaluate `NIL?` function
SExprPtr Eval::evalIsNil(const List& list) {
    std::cout << "Eval NIL? function" << std::endl; 
    if (list.elements.size() != 2) {
        throw std::runtime_error("NIL? expects exactly one argument");
    }

    // Get the argument
    auto it = std::next(list.elements.begin()); // Skip the "NIL?" symbol
    SExprPtr argument = evaluate(*it);

    // Check if the argument is nil
    if (std::dynamic_pointer_cast<Nil>(argument)) {
        return TRUTH; // Return TRUTH if the argument is nil
    } else {
        return NIL; // Return NIL if the argument is not nil
    }
    std::cout << std::endl;
}

// Evaluate `SYM?` function
SExprPtr Eval::evalIsSym(const List& list) { 
    std::cout << "Eval SYM? function" << std::endl; 
    if (list.elements.size() != 2) {
        throw std::runtime_error("SYM? expects exactly one argument");
    }

    // Get the argument
    auto it = std::next(list.elements.begin()); // Skip the "SYM?" symbol
    SExprPtr argument = evaluate(*it);

    // Check if the argument is a symbol
    if (std::dynamic_pointer_cast<Symbol>(argument)) {
        return TRUTH; // Return TRUTH if the argument is a symbol
    } else {
        return NIL; // Return NIL if the argument is not a symbol
    }
    std::cout << std::endl;
}

// Evaluate `NUM?` function
SExprPtr Eval::evalIsNum(const List& list) {
    std::cout << "Eval NUM? function" << std::endl; 
    if (list.elements.size() != 2) {
        throw std::runtime_error("NUM? expects exactly one argument");
    }

    // Get the argument
    auto it = std::next(list.elements.begin()); // Skip the "NUM?" symbol
    SExprPtr argument = evaluate(*it);

    // Check if the argument is a number
    if (std::dynamic_pointer_cast<Number>(argument)) {
        return TRUTH; // Return TRUTH if the argument is a number
    } else {
        return NIL; // Return NIL if the argument is not a number
    }
    std::cout << std::endl;
}

SExprPtr Eval::evalIsList(const List& list) {
    std::cout << "Eval LIST? function" << std::endl; 
    if (list.elements.size() != 2) {
        throw std::runtime_error("LIST? expects exactly one argument");
    }

    // Evaluate the argument
    auto it = std::next(list.elements.begin()); // Skip the "LIST?" symbol
    SExprPtr argument = evaluate(*it);          // Fully evaluate the argument

    // Check if the argument is a list
    if (std::dynamic_pointer_cast<List>(argument)) {
        return TRUTH; // Return TRUTH if the argument is a list
    } else {
        return NIL;   // Return NIL otherwise
    }
}