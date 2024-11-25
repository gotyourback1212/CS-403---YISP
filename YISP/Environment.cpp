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
