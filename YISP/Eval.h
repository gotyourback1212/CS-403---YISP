#ifndef EVAL_H
#define EVAL_H

#include "SExpr.h"
#include "Environment.h"

#include <iostream>
#include <stdexcept>

class Eval {
public:

    Eval (EnvironmentPtr env) : environment(env) {}

    SExprPtr evaluate(const SExprPtr& expr);

    //Predicate Functions
    SExprPtr evalIsNil(const List& list); 
    SExprPtr evalIsSym(const List& list); 
    SExprPtr evalIsNum(const List& list); 
    SExprPtr evalIsList(const List& list);

    //Comparison Funcitons
    SExprPtr evalGt(const List& list); 
    SExprPtr evalLt(const List& list); 
    SExprPtr evalGte(const List& list); 
    SExprPtr evalLte(const List& list);
    SExprPtr evalEq(const List& list);

    //Logical Functions
    SExprPtr evalNot(const List& list);
    SExprPtr evalAnd(const List& list);
    SExprPtr evalOr(const List& list);
    SExprPtr evalIf(const List& list);
    SExprPtr evalCond(const List& list); 

    //Math Functions
    SExprPtr evalAdd(const List& list); 
    SExprPtr evalSub(const List& list); 
    SExprPtr evalMul(const List& list); 
    SExprPtr evalDiv(const List& list); 
    SExprPtr evalMod(const List& list); 
    
    //List Funcitons
    SExprPtr evalCons(const List& list); 
    SExprPtr evalCar(const List& list); 
    SExprPtr evalCdr(const List& list); 

    //Define Funcitions
    SExprPtr evalQuote(const List& list); 
    SExprPtr evalEval(const List& list); 
    SExprPtr evalSet(const List& list); 

private: 
    EnvironmentPtr environment; 

};

#endif // EVALR_H