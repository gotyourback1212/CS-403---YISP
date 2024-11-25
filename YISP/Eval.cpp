#include "Eval.h"
#include <stdexcept>
#include <iostream>
#include <memory>



// Evaluate the expression
SExprPtr Eval::evaluate(const SExprPtr& expr) {
    if (!expr) {
        throw std::runtime_error("Null expression during evaluation");
    }

    // Handle Nil
    if (std::dynamic_pointer_cast<Nil>(expr)) {
        return expr; // Return NIL
    }

    // Handle TRUTH (#T)
    if (std::dynamic_pointer_cast<Truth>(expr)) {
        return TRUTH; // Return TRUTH
    }

    // Handle Symbol constants or variables
    if (auto symbol = std::dynamic_pointer_cast<Symbol>(expr)) {
        if (symbol->name == "nil") {
            return NIL;
        } else if (symbol->name == "#T") {
            return TRUTH;
        } else {
            // Look up variable in the environment
            SExprPtr value = environment->get(symbol->name);
            if(value) { // If symbol has vaulue return value, else return symbol
                return value; 
            }
            else{ 
                return symbol; 
            }
        }
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
        } else if (symbol->name == "gt") {
            return evalGt(*list); // Return TRUTH or NIL
        } else if (symbol->name == "lt") {
            return evalLt(*list); // Return TRUTH or NIL
        } else if (symbol->name == "gte") {
            return evalGte(*list); // Return TRUTH or NIL
        } else if (symbol->name == "lte") {
            return evalLte(*list); // Return TRUTH or NIL
        } else if (symbol->name == "eq") {
            return evalEq(*list); // Return TRUTH or NIL
        } else if (symbol->name == "not") {
            return evalNot(*list); // Return TRUTH or NIL
        } else if (symbol->name == "and") {
            return evalAnd(*list); // Handle logical AND
        } else if (symbol->name == "or") {
            return evalOr(*list); // Handle logical OR
        } else if (symbol->name == "cons") {
            return evalCons(*list); // Return the results of cons
        } else if (symbol->name == "car") {
            return evalCar(*list); // Return the results of car
        } else if (symbol->name == "cdr") {
            return evalCdr(*list); // Return the results of cdr
        } else if (symbol->name == "quote") {
            return evalQuote(*list); // Return the quote of Sexpression
        } else if (symbol->name == "eval") {
            return evalEval(*list); // Return the results of Sexpression 
        } else if (symbol->name == "set") {
            return evalSet(*list); // Return the results of Sexpression 
        } else if (symbol->name == "+" || symbol->name == "add") {
            return evalAdd(*list); // Handle addition
        } else if (symbol->name == "-" || symbol->name == "minus") {
            return evalSub(*list); // Handle subtraction
        } else if (symbol->name == "*" || symbol->name == "mul") {
            return evalMul(*list); // Handle multiplication
        } else if (symbol->name == "/" || symbol->name == "div") {
            return evalDiv(*list); // Handle division
        } else if (symbol->name == "%" || symbol->name == "mod") {
            return evalMod(*list); // Handle modulo
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
    //std::cout << "Eval print function" << std::endl; 
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
            //std::cout << " ";
        }
    }
    //std::cout << std::endl; // Add newline after printing all arguments

    return lastResult; // Return the last evaluated result
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Evaluate 'cons' funciton
SExprPtr Eval::evalCons(const List& list) {
    //std::cout << "Eval cons function" << std::endl; 
    if (list.elements.size() != 3) {
        throw std::runtime_error("cons expects exactly two arguments");
    }

    // Evaluate the first argument (head of the list)
    auto car = evaluate(*std::next(list.elements.begin()));

    // Evaluate the second argument (tail of the list)
    auto cdr = evaluate(*std::next(list.elements.begin(), 2));

    // Ensure the tail is a list or NIL
    auto tailList = std::dynamic_pointer_cast<List>(cdr);
    if (!tailList && !std::dynamic_pointer_cast<Nil>(cdr)) {
        throw std::runtime_error("The second argument to cons must be a list or NIL");
    }

    // Create the new list
    std::list<SExprPtr> newElements = {car};
    if (tailList) {
        newElements.insert(newElements.end(), tailList->elements.begin(), tailList->elements.end());
    }

    return std::make_shared<List>(newElements);
}

//Evaluate 'car' function
SExprPtr Eval::evalCar(const List& list) {
    //std::cout << "Eval cdr function" << std::endl; 
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
    //std::cout << "Eval cdr function" << std::endl; 
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
//Evaluate 'gt' function
SExprPtr Eval::evalGt(const List& list) {
    //std::cout << "Eval gt function" << std::endl; 
    if (list.elements.size() != 3) {
        throw std::runtime_error("gt expects exactly two arguments");
    }

    // Evaluate both arguments
    auto it = std::next(list.elements.begin()); // Skip the "gt" symbol
    SExprPtr firstArg = evaluate(*it);
    SExprPtr secondArg = evaluate(*std::next(it));

    // Ensure both arguments are numbers
    auto firstNum = std::dynamic_pointer_cast<Number>(firstArg);
    auto secondNum = std::dynamic_pointer_cast<Number>(secondArg);
    if (!firstNum || !secondNum) {
        throw std::runtime_error("gt expects both arguments to be numbers");
    }

    // Perform comparison
    if (firstNum->value > secondNum->value) {
        return TRUTH; // Return TRUTH if condition is satisfied
    } else {
        return NIL;   // Return NIL otherwise
    }
}

//Evaluate 'lt' function
SExprPtr Eval::evalLt(const List& list) {
    //std::cout << "Eval lt function" << std::endl;
    if (list.elements.size() != 3) {
        throw std::runtime_error("lt expects exactly two arguments");
    }

    // Evaluate both arguments
    auto it = std::next(list.elements.begin()); // Skip the "lt" symbol
    SExprPtr firstArg = evaluate(*it);
    SExprPtr secondArg = evaluate(*std::next(it));

    // Ensure both arguments are numbers
    auto firstNum = std::dynamic_pointer_cast<Number>(firstArg);
    auto secondNum = std::dynamic_pointer_cast<Number>(secondArg);
    if (!firstNum || !secondNum) {
        throw std::runtime_error("lt expects both arguments to be numbers");
    }

    // Perform comparison
    if (firstNum->value < secondNum->value) {
        return TRUTH; // Return TRUTH if condition is satisfied
    } else {
        return NIL;   // Return NIL otherwise
    }
}

//Evaluate 'gte' function
SExprPtr Eval::evalGte(const List& list) {
    //std::cout << "Eval gte function" << std::endl;
    if (list.elements.size() != 3) {
        throw std::runtime_error("gte expects exactly two arguments");
    }

    // Evaluate both arguments
    auto it = std::next(list.elements.begin()); // Skip the "gte" symbol
    SExprPtr firstArg = evaluate(*it);
    SExprPtr secondArg = evaluate(*std::next(it));

    // Ensure both arguments are numbers
    auto firstNum = std::dynamic_pointer_cast<Number>(firstArg);
    auto secondNum = std::dynamic_pointer_cast<Number>(secondArg);
    if (!firstNum || !secondNum) {
        throw std::runtime_error("gte expects both arguments to be numbers");
    }

    // Perform comparison
    if (firstNum->value >= secondNum->value) {
        return TRUTH; // Return TRUTH if condition is satisfied
    } else {
        return NIL;   // Return NIL otherwise
    }
}

//Evaluate 'lte' function
SExprPtr Eval::evalLte(const List& list) {
    //std::cout << "Eval lte function" << std::endl;
    if (list.elements.size() != 3) {
        throw std::runtime_error("lte expects exactly two arguments");
    }

    // Evaluate both arguments
    auto it = std::next(list.elements.begin()); // Skip the "lte" symbol
    SExprPtr firstArg = evaluate(*it);
    SExprPtr secondArg = evaluate(*std::next(it));

    // Ensure both arguments are numbers
    auto firstNum = std::dynamic_pointer_cast<Number>(firstArg);
    auto secondNum = std::dynamic_pointer_cast<Number>(secondArg);
    if (!firstNum || !secondNum) {
        throw std::runtime_error("lte expects both arguments to be numbers");
    }

    // Perform comparison
    if (firstNum->value <= secondNum->value) {
        return TRUTH; // Return TRUTH if condition is satisfied
    } else {
        return NIL;   // Return NIL otherwise
    }
}

//Evaluate 'eq' function
SExprPtr Eval::evalEq(const List& list) {
     if (list.elements.size() != 3) {
        throw std::runtime_error("eq expects exactly two arguments");
    }

    // Evaluate both arguments
    auto it = std::next(list.elements.begin());
    SExprPtr firstArg = evaluate(*it);
    SExprPtr secondArg = evaluate(*std::next(it));

    // Check if both are NIL
    if (firstArg == NIL && secondArg == NIL) {
        return TRUTH;
    }

    // Check if both are TRUTH
    if (firstArg == TRUTH && secondArg == TRUTH) {
        return TRUTH;
    }

    // Check if both arguments are numbers
    auto firstNum = std::dynamic_pointer_cast<Number>(firstArg);
    auto secondNum = std::dynamic_pointer_cast<Number>(secondArg);
    if (firstNum && secondNum) {
        return (firstNum->value == secondNum->value) ? TRUTH : NIL;
    }

    // Check if both arguments are symbols
    auto firstSym = std::dynamic_pointer_cast<Symbol>(firstArg);
    auto secondSym = std::dynamic_pointer_cast<Symbol>(secondArg);
    if (firstSym && secondSym) {
        return (firstSym->name == secondSym->name) ? TRUTH : NIL;
    }

    // Check if both are lists and compare their elements
    auto firstList = std::dynamic_pointer_cast<List>(firstArg);
    auto secondList = std::dynamic_pointer_cast<List>(secondArg);
    if (firstList && secondList) {
        if (firstList->elements.size() != secondList->elements.size()) {
            return NIL;
        }

        auto it1 = firstList->elements.begin();
        auto it2 = secondList->elements.begin();
        while (it1 != firstList->elements.end() && it2 != secondList->elements.end()) {
            if (evaluate(*it1) != evaluate(*it2)) {
                return NIL;
            }
            ++it1;
            ++it2;
        }
        return TRUTH;
    }

    // If arguments are not comparable
    return NIL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Evaluate `and` function
SExprPtr Eval::evalNot(const List& list) {
     //std::cout << "Eval nor function" << std::endl;
    if (list.elements.size() != 2) {
        throw std::runtime_error("not expects exactly one argument");
    }

    // Evaluate the argument
    auto it = std::next(list.elements.begin()); // Skip the "not" symbol
    SExprPtr argument = evaluate(*it);

    // Return TRUTH if argument is NIL, otherwise return NIL
    return std::dynamic_pointer_cast<Nil>(argument) ? TRUTH : NIL;
}

// Evaluate `not` function
SExprPtr Eval::evalAnd(const List& list) {
    if (list.elements.size() < 2) {
        throw std::runtime_error("and expects at least one argument");
    }

    // Iterate over all arguments
    for (auto it = std::next(list.elements.begin()); it != list.elements.end(); ++it) {
        SExprPtr result = evaluate(*it);
        if (std::dynamic_pointer_cast<Nil>(result)) {
            return NIL; // Short-circuit: if any value is NIL, return NIL immediately
        }
    }
    return TRUTH; // If no value is NIL, return TRUTH
}

// Evaluate `or` function
SExprPtr Eval::evalOr(const List& list) {
    if (list.elements.size() < 2) {
        throw std::runtime_error("or expects at least one argument");
    }

    // Iterate over all arguments
    for (auto it = std::next(list.elements.begin()); it != list.elements.end(); ++it) {
        SExprPtr result = evaluate(*it);
        if (std::dynamic_pointer_cast<Truth>(result)) {
            return TRUTH; // Short-circuit: if any value is TRUTH, return TRUTH immediately
        }
    }
    return NIL; // If no value is TRUTH, return NIL
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Evaluate `NIL?` function
SExprPtr Eval::evalIsNil(const List& list) {
    //std::cout << "Eval NIL? function" << std::endl; 
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
    //std::cout << std::endl;
}

// Evaluate `SYM?` function
SExprPtr Eval::evalIsSym(const List& list) { 
    //std::cout << "Eval SYM? function" << std::endl; 
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
    //std::cout << std::endl;
}

// Evaluate `NUM?` function
SExprPtr Eval::evalIsNum(const List& list) {
    //std::cout << "Eval NUM? function" << std::endl; 
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
    //std::cout << std::endl;
}

SExprPtr Eval::evalIsList(const List& list) {
    //std::cout << "Eval LIST? function" << std::endl; 
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Evaluate `+` function
SExprPtr Eval::evalAdd(const List& list) {
    //std::cout << "Eval add function" << std::endl; 
    if (list.elements.size() < 3) {
        throw std::runtime_error("+ expects at least two argument");
    }

    int sum = 0;
    for (auto it = std::next(list.elements.begin()); it != list.elements.end(); ++it) {
        SExprPtr arg = evaluate(*it);
        auto number = std::dynamic_pointer_cast<Number>(arg);
        if (!number) {
            throw std::runtime_error("+ expects all arguments to be numbers");
        }
        sum += number->value;
    }

    return std::make_shared<Number>(sum);
}

// Evaluate `-` function
SExprPtr Eval::evalSub(const List& list) {
    //std::cout << "Eval sub function" << std::endl; 
    if (list.elements.size() < 3) {
        throw std::runtime_error("- expects at least two arguments");
    }

    auto it = std::next(list.elements.begin());
    SExprPtr firstArg = evaluate(*it);
    auto firstNumber = std::dynamic_pointer_cast<Number>(firstArg);
    if (!firstNumber) {
        throw std::runtime_error("- expects all arguments to be numbers");
    }

    int result = firstNumber->value;
    for (++it; it != list.elements.end(); ++it) {
        SExprPtr arg = evaluate(*it);
        auto number = std::dynamic_pointer_cast<Number>(arg);
        if (!number) {
            throw std::runtime_error("- expects all arguments to be numbers");
        }
        result -= number->value;
    }

    return std::make_shared<Number>(result);
}

// Evaluate `*` function
SExprPtr Eval::evalMul(const List& list) {
    //std::cout << "Eval Mul function" << std::endl; 
    if (list.elements.size() < 3) {
        throw std::runtime_error("* expects at least two argument");
    }

    int product = 1;
    for (auto it = std::next(list.elements.begin()); it != list.elements.end(); ++it) {
        SExprPtr arg = evaluate(*it);
        auto number = std::dynamic_pointer_cast<Number>(arg);
        if (!number) {
            throw std::runtime_error("* expects all arguments to be numbers");
        }
        product *= number->value;
    }

    return std::make_shared<Number>(product);
}

// Evaluate `/` function
SExprPtr Eval::evalDiv(const List& list) {
    //std::cout << "Eval Div function" << std::endl; 
    if (list.elements.size() < 3) {
        throw std::runtime_error("/ expects at least two arguments");
    }

    auto it = std::next(list.elements.begin());
    SExprPtr firstArg = evaluate(*it);
    auto firstNumber = std::dynamic_pointer_cast<Number>(firstArg);
    if (!firstNumber) {
        throw std::runtime_error("/ expects all arguments to be numbers");
    }

    int result = firstNumber->value;
    for (++it; it != list.elements.end(); ++it) {
        SExprPtr arg = evaluate(*it);
        auto number = std::dynamic_pointer_cast<Number>(arg);
        if (!number) {
            throw std::runtime_error("/ expects all arguments to be numbers");
        }
        if (number->value == 0) {
            throw std::runtime_error("Division by zero");
        }
        result /= number->value;
    }

    return std::make_shared<Number>(result);
}

// Evaluate `%` function
SExprPtr Eval::evalMod(const List& list) {
    //std::cout << "Eval Mod function" << std::endl;
    if (list.elements.size() != 3) {
        throw std::runtime_error("% expects exactly two arguments");
    }

    auto it = std::next(list.elements.begin());
    SExprPtr firstArg = evaluate(*it);
    SExprPtr secondArg = evaluate(*std::next(it));

    auto firstNumber = std::dynamic_pointer_cast<Number>(firstArg);
    auto secondNumber = std::dynamic_pointer_cast<Number>(secondArg);
    if (!firstNumber || !secondNumber) {
        throw std::runtime_error("% expects both arguments to be numbers");
    }
    if (secondNumber->value == 0) {
        throw std::runtime_error("Modulo by zero");
    }

    return std::make_shared<Number>(firstNumber->value % secondNumber->value);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Evaluate `quote` function
SExprPtr Eval::evalQuote(const List& list) {
    if (list.elements.size() != 2) {
        throw std::runtime_error("quote expects exactly one argument");
    }
    
    // Simply return the second element without evaluating it
    auto it = std::next(list.elements.begin()); // Skip the "quote" symbol
    return *it;
}

// Evaluate `eval` function
SExprPtr Eval::evalEval(const List& list) {
    if (list.elements.size() != 2) {
        throw std::runtime_error("eval expects exactly one argument");
    }

    // Get the argument to evaluate
    auto it = std::next(list.elements.begin()); // Skip the "eval" symbol
    SExprPtr argument = evaluate(*it);

    // Evaluate the argument
    return evaluate(argument);
}


SExprPtr Eval::evalSet(const List& list) {
    if (list.elements.size() != 3) {
        throw std::runtime_error("set expects exactly two arguments");
    }

    // Get the first argument, which should be a symbol
    auto it = std::next(list.elements.begin());
    auto symbol = std::dynamic_pointer_cast<Symbol>(*it);
    if (!symbol) {
        throw std::runtime_error("The first argument to set must be a symbol");
    }

    // Evaluate the value to be assigned
    auto value = evaluate(*std::next(it));

    // Set the value in the environment
    environment->set(symbol->name, value);

    return value; // Return the value that was set
}








 /* For debugging 
    // Check if both are TRUTH
    if (secondArg == TRUTH) {
        std::cout << "Second Arg: true" << std::endl;
    } else if (secondArg == NIL) {
        std::cout << "Second Arg: nil" << std::endl;
    } else if (std::dynamic_pointer_cast<Symbol>(secondArg)) {
        auto symbol = std::dynamic_pointer_cast<Symbol>(secondArg);
        std::cout << "Second Arg: symbol (" << symbol->name << ")" << std::endl;
    } else if (std::dynamic_pointer_cast<Number>(secondArg)) {
        auto number = std::dynamic_pointer_cast<Number>(secondArg);
        std::cout << "Second Arg: number (" << number->value << ")" << std::endl;
    } else {
        std::cout << "Second Arg: unknown type" << std::endl;
    }
*/ 
