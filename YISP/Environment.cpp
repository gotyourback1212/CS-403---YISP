#include <stdexcept>
#include <iostream> 
#include <memory> 

#include "Environment.h"
#include "Token.h"

void Environment::set(const std::string& name, const SExprPtr& value) {
        bindings[name] = value;
}

SExprPtr Environment::get(const std::string& name) const {
    auto it = bindings.find(name);
    if (it != bindings.end()) {
        return it->second;
    } 
    return nullptr; 

}

void FunctionEnvironment::define(const std::string& name, const std::list<std::string>& args, const SExprPtr& body) {
    functions[name] = {args, body};
}

bool FunctionEnvironment::hasFunction(const std::string& name) const {
    return functions.find(name) != functions.end();
}

std::pair<std::list<std::string>, SExprPtr> FunctionEnvironment::getFunction(const std::string& name) const {
    auto it = functions.find(name);
    if (it != functions.end()) {
        return {it->second.args, it->second.body};
    } else {
        throw std::runtime_error("Undefined function: " + name);
    }
}