#ifndef EVAL_H
#define EVAL_H

#include "SExpr.h"
#include <iostream>
#include <stdexcept>

class Eval {
public:
    SExprPtr evaluate(const SExprPtr& expr);

    SExprPtr evalPrint(const List& list);

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

    //Math functions
    SExprPtr evalAdd(const List& list); 
    SExprPtr evalSub(const List& list); 
    SExprPtr evalMul(const List& list); 
    SExprPtr evalDiv(const List& list); 
    SExprPtr evalMod(const List& list); 
    
    //List funcitons
    SExprPtr evalCons(const List& list); 
    SExprPtr evalCar(const List& list); 
    SExprPtr evalCdr(const List& list); 
};

#endif // EVALR_H