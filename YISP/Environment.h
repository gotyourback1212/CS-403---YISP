#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_map>
#include <string>

#include "SExpr.h"


class Environment {
public:
    Environment() {}

    void set(const std::string& name, const SExprPtr& value);

    SExprPtr get(const std::string& name) const;

private:
    std::unordered_map<std::string, SExprPtr> bindings;
};

using EnvironmentPtr = std::shared_ptr<Environment>;

#endif // ENVIRONMENT_H