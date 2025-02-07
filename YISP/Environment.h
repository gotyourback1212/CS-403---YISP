#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_map>
#include <string>

#include "SExpr.h"



class Environment {
public:
     Environment(std::shared_ptr<Environment> parent = nullptr) : parent(parent) {}

    void set(const std::string& name, const SExprPtr& value);
    SExprPtr get(const std::string& name) const;

private:
    std::unordered_map<std::string, SExprPtr> bindings;
    std::shared_ptr<Environment> parent;
};

// Class for storing functions
class FunctionEnvironment {
public:
    FunctionEnvironment() {}

    void define(const std::string& name, const std::list<std::string>& args, const SExprPtr& body);
    bool hasFunction(const std::string& name) const;
    std::pair<std::list<std::string>, SExprPtr> getFunction(const std::string& name) const;

private:
    struct FunctionDefinition {
        std::list<std::string> args;
        SExprPtr body;
    };

    std::unordered_map<std::string, FunctionDefinition> functions;
};

using EnvironmentPtr = std::shared_ptr<Environment>;
using FunctionEnvironmentPtr = std::shared_ptr<FunctionEnvironment>;

#endif // ENVIRONMENT_H