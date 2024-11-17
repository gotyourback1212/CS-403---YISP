#ifndef EVAL_H
#define EVAL_H

#include "SExpr.h"
#include <iostream>
#include <stdexcept>

class Eval {
public:
    SExprPtr evaluate(const SExprPtr& expr);

    SExprPtr evalPrint(const List& list);

    SExprPtr evalIsNil(const List& list); 
    SExprPtr evalIsSym(const List& list); 
    SExprPtr evalIsNum(const List& list); 
    SExprPtr evalIsList(const List& list);

    SExprPtr evalCons(const List& list); 
    SExprPtr evalCar(const List& list); 
    SExprPtr evalCdr(const List& list); 
};

#endif // EVALR_H