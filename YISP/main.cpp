#include "Token.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <list> 

void repl() {
    std::string line;
    std::cout << "Lisp Interpreter REPL. Type 'exit' to quit.\n";
    while (true) {
        std::cout << ">>> ";
        if (!std::getline(std::cin, line)) {
            break;
        }
        if (line == "exit") {
            break;
        }
        try {
            std::list <Token> tokens(tokenize(line));
            Parser parser(tokens);
            SExprPtr expr = parser.parseExpr();
            expr->print();
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    repl();
    return 0;
}








/* 

The First Sprint
Create a grammar for S-Expressions.
Create a data structure for S-expressions. This is our AST.
Write a print function that can print an S-Expression.
Now write a parse function that returns an S-Expression. Parse should read the input source until it has a valid S-expression and then return that S-Expression. The S-Expression generated should be the same as if found quoted in a program. Don't try to evaluate it at this point.
 
Now you should be able to code something like:
fn repl(){
                  print(parse(std:input))
}
If you want go ahead and create an eval function that simply returns it's argument and then you can finish the repl function: 
fn repl(){
                  loop { print(eval(read() )) }
}
 
This is the first snapshot you'll turn in as part of the project.
*/






















/*

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cctype>
#include <memory>

// Forward declarations
class Environment;
class SExpression;

// Value types
enum class ValueType {
    Number,
    Symbol,
    Boolean,
    Cons,
    Nil,
    Function,
};

// Base class for all S-Expressions
class SExpression {
public:
    virtual ~SExpression() = default;
    virtual void print(std::ostream& out) const = 0;
    virtual ValueType type() const = 0;
    virtual std::shared_ptr<SExpression> eval(std::shared_ptr<Environment> env) = 0;
};

// Class for numbers
class Number : public SExpression {
public:
    int value;

    Number(int v) : value(v) {}

    void print(std::ostream& out) const override {
        out << value;
    }

    ValueType type() const override {
        return ValueType::Number;
    }

    std::shared_ptr<SExpression> eval(std::shared_ptr<Environment> env) override {
        // Numbers evaluate to themselves
        return std::make_shared<Number>(value);
    }
};

// Class for symbols
class Symbol : public SExpression {
public:
    std::string name;

    Symbol(const std::string& n) : name(n) {}

    void print(std::ostream& out) const override {
        out << name;
    }

    ValueType type() const override {
        return ValueType::Symbol;
    }

    std::shared_ptr<SExpression> eval(std::shared_ptr<Environment> env) override;
};

// Class for booleans
class Boolean : public SExpression {
public:
    bool value;

    Boolean(bool v) : value(v) {}

    void print(std::ostream& out) const override {
        if (value)
            out << "T";
        else
            out << "nil";
    }

    ValueType type() const override {
        return ValueType::Boolean;
    }

    std::shared_ptr<SExpression> eval(std::shared_ptr<Environment> env) override {
        // Booleans evaluate to themselves
        return std::make_shared<Boolean>(value);
    }
};

// Forward declaration of Cons
class Cons;

// Class for functions
class Function : public SExpression {
public:
    // For built-in functions
    using BuiltinFunc = std::function<std::shared_ptr<SExpression>(std::vector<std::shared_ptr<SExpression>>, std::shared_ptr<Environment>)>;

    BuiltinFunc func;

    Function(BuiltinFunc f) : func(f) {}

    void print(std::ostream& out) const override {
        out << "<function>";
    }

    ValueType type() const override {
        return ValueType::Function;
    }

    std::shared_ptr<SExpression> eval(std::shared_ptr<Environment> env) override {
        // Functions evaluate to themselves
        return std::make_shared<Function>(func);
    }
};

// Class for cons cells (lists)
class Cons : public SExpression {
public:
    std::shared_ptr<SExpression> car;
    std::shared_ptr<SExpression> cdr;

    Cons(std::shared_ptr<SExpression> a, std::shared_ptr<SExpression> d) : car(a), cdr(d) {}

    void print(std::ostream& out) const override {
        out << "(";
        printList(out);
        out << ")";
    }

    void printList(std::ostream& out) const {
        car->print(out);
        if (cdr->type() == ValueType::Cons) {
            out << " ";
            std::dynamic_pointer_cast<Cons>(cdr)->printList(out);
        } else if (cdr->type() != ValueType::Nil) {
            out << " . ";
            cdr->print(out);
        }
    }

    ValueType type() const override {
        return ValueType::Cons;
    }

    std::shared_ptr<SExpression> eval(std::shared_ptr<Environment> env) override;
};

// Class for the empty list (nil)
class Nil : public SExpression {
public:
    void print(std::ostream& out) const override {
        out << "nil";
    }

    ValueType type() const override {
        return ValueType::Nil;
    }

    std::shared_ptr<SExpression> eval(std::shared_ptr<Environment> env) override {
        // Nil evaluates to itself
        return std::make_shared<Nil>();
    }
};

// Environment class
class Environment : public std::enable_shared_from_this<Environment> {
public:
    std::shared_ptr<Environment> parent;
    std::unordered_map<std::string, std::shared_ptr<SExpression>> symbols;

    Environment(std::shared_ptr<Environment> p = nullptr) : parent(p) {}

    void define(const std::string& name, std::shared_ptr<SExpression> value) {
        symbols[name] = value;
    }

    bool set(const std::string& name, std::shared_ptr<SExpression> value) {
        if (symbols.count(name)) {
            symbols[name] = value;
            return true;
        } else if (parent) {
            return parent->set(name, value);
        } else {
            return false;
        }
    }

    std::shared_ptr<SExpression> lookup(const std::string& name) {
        if (symbols.count(name)) {
            return symbols[name];
        } else if (parent) {
            return parent->lookup(name);
        } else {
            return nullptr;
        }
    }
};

// Implementation of Symbol::eval
std::shared_ptr<SExpression> Symbol::eval(std::shared_ptr<Environment> env) {
    auto val = env->lookup(name);
    if (val) {
        return val;
    } else {
        std::cerr << "Error: Undefined symbol '" << name << "'" << std::endl;
        return nullptr;
    }
}

// Implementation of Cons::eval
std::shared_ptr<SExpression> Cons::eval(std::shared_ptr<Environment> env) {
    // Evaluate the operator
    auto op = car->eval(env);
    if (!op) return nullptr;

    // Check if op is a special form
    if (op->type() == ValueType::Symbol) {
        auto op_sym = std::dynamic_pointer_cast<Symbol>(op)->name;
        if (op_sym == "QUOTE") {
            // (QUOTE expr)
            if (cdr->type() == ValueType::Cons && std::dynamic_pointer_cast<Cons>(cdr)->cdr->type() == ValueType::Nil) {
                return std::dynamic_pointer_cast<Cons>(cdr)->car;
            } else {
                std::cerr << "Error: 'QUOTE' expects exactly one argument" << std::endl;
                return nullptr;
            }
        }
        // You can handle other special forms here
    }

    // Evaluate arguments
    std::vector<std::shared_ptr<SExpression>> args;
    auto current = cdr;
    while (current->type() == ValueType::Cons) {
        auto cons_current = std::dynamic_pointer_cast<Cons>(current);
        auto arg = cons_current->car->eval(env);
        if (!arg) return nullptr;
        args.push_back(arg);
        current = cons_current->cdr;
    }
    if (current->type() != ValueType::Nil) {
        // Improper list
        std::cerr << "Error: Improper list structure" << std::endl;
        return nullptr;
    }

    if (op->type() == ValueType::Function) {
        auto func = std::dynamic_pointer_cast<Function>(op);
        return func->func(args, env);
    } else {
        std::cerr << "Error: Attempt to call non-function" << std::endl;
        return nullptr;
    }
}

// Nil singleton instance
std::shared_ptr<Nil> NIL = std::make_shared<Nil>();

// Tokenizer
class Tokenizer {
public:
    Tokenizer(std::istream& in) : input(in), has_unget(false) {}

    std::string nextToken() {
        if (has_unget) {
            has_unget = false;
            return unget_token;
        }

        // Skip whitespace
        while (std::isspace(peek())) {
            get();
        }

        if (input.eof()) return "";

        char c = peek();
        if (c == '(' || c == ')') {
            get();
            return std::string(1, c);
        } else {
            std::string atom;
            while (!input.eof() && !std::isspace(peek()) && peek() != '(' && peek() != ')') {
                atom += get();
            }
            return atom;
        }
    }

    void unget(const std::string& token) {
        has_unget = true;
        unget_token = token;
    }

private:
    std::istream& input;
    bool has_unget;
    std::string unget_token;

    char peek() { return input.peek(); }
    char get() { return input.get(); }
};

// Parser functions
std::shared_ptr<SExpression> parseSExpression(Tokenizer& tokenizer);

std::shared_ptr<SExpression> parseAtom(const std::string& token) {
    // Check if the token is a number
    if (!token.empty() && (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1))) {
        bool is_number = true;
        for (size_t i = 1; i < token.size(); ++i) {
            if (!std::isdigit(token[i])) {
                is_number = false;
                break;
            }
        }
        if (is_number) {
            return std::make_shared<Number>(std::stoi(token));
        }
    }
    // Else, it's a symbol
    if (token == "nil") {
        return NIL;
    } else if (token == "T") {
        return std::make_shared<Boolean>(true);
    } else {
        return std::make_shared<Symbol>(token);
    }
}

std::shared_ptr<SExpression> parseSExpression(Tokenizer& tokenizer) {
    std::string token = tokenizer.nextToken();
    if (token == "") {
        return nullptr;
    } else if (token == "(") {
        // Start of a list
        std::vector<std::shared_ptr<SExpression>> elements;
        while (true) {
            std::string nextToken = tokenizer.nextToken();
            if (nextToken == "") {
                std::cerr << "Error: Unexpected end of input while parsing list" << std::endl;
                return nullptr;
            } else if (nextToken == ")") {
                // End of list
                break;
            } else {
                tokenizer.unget(nextToken);
                auto expr = parseSExpression(tokenizer);
                if (!expr) {
                    return nullptr;
                }
                elements.push_back(expr);
            }
        }
        // Convert vector to linked list
        std::shared_ptr<SExpression> list = NIL;
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            list = std::make_shared<Cons>(*it, list);
        }
        return list;
    } else if (token == ")") {
        std::cerr << "Error: Unexpected ')'" << std::endl;
        return nullptr;
    } else {
        return parseAtom(token);
    }
}

std::shared_ptr<SExpression> parse(std::istream& in) {
    Tokenizer tokenizer(in);
    return parseSExpression(tokenizer);
}

// Built-in function implementations

// Addition
std::shared_ptr<SExpression> builtin_add(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    int sum = 0;
    for (auto arg : args) {
        if (arg->type() == ValueType::Number) {
            auto num = std::dynamic_pointer_cast<Number>(arg);
            sum += num->value;
        } else {
            std::cerr << "Error: '+' expects numbers" << std::endl;
            return nullptr;
        }
    }
    return std::make_shared<Number>(sum);
}

// Subtraction
std::shared_ptr<SExpression> builtin_subtract(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.empty()) {
        std::cerr << "Error: '-' expects at least one argument" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != ValueType::Number) {
        std::cerr << "Error: '-' expects numbers" << std::endl;
        return nullptr;
    }
    int result = std::dynamic_pointer_cast<Number>(args[0])->value;
    if (args.size() == 1) {
        // Unary minus
        result = -result;
    } else {
        for (size_t i = 1; i < args.size(); ++i) {
            if (args[i]->type() != ValueType::Number) {
                std::cerr << "Error: '-' expects numbers" << std::endl;
                return nullptr;
            }
            result -= std::dynamic_pointer_cast<Number>(args[i])->value;
        }
    }
    return std::make_shared<Number>(result);
}

// Multiplication
std::shared_ptr<SExpression> builtin_multiply(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    int product = 1;
    for (auto arg : args) {
        if (arg->type() == ValueType::Number) {
            auto num = std::dynamic_pointer_cast<Number>(arg);
            product *= num->value;
        } else {
            std::cerr << "Error: '*' expects numbers" << std::endl;
            return nullptr;
        }
    }
    return std::make_shared<Number>(product);
}

// Division
std::shared_ptr<SExpression> builtin_divide(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() < 2) {
        std::cerr << "Error: '/' expects at least two arguments" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != ValueType::Number) {
        std::cerr << "Error: '/' expects numbers" << std::endl;
        return nullptr;
    }
    int result = std::dynamic_pointer_cast<Number>(args[0])->value;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i]->type() != ValueType::Number) {
            std::cerr << "Error: '/' expects numbers" << std::endl;
            return nullptr;
        }
        int divisor = std::dynamic_pointer_cast<Number>(args[i])->value;
        if (divisor == 0) {
            std::cerr << "Error: Division by zero" << std::endl;
            return nullptr;
        }
        result /= divisor;
    }
    return std::make_shared<Number>(result);
}

// Equality
std::shared_ptr<SExpression> builtin_equal(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 2) {
        std::cerr << "Error: '=' expects exactly two arguments" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != args[1]->type()) {
        return std::make_shared<Boolean>(false);
    }
    if (args[0]->type() == ValueType::Number) {
        auto num1 = std::dynamic_pointer_cast<Number>(args[0]);
        auto num2 = std::dynamic_pointer_cast<Number>(args[1]);
        return std::make_shared<Boolean>(num1->value == num2->value);
    } else if (args[0]->type() == ValueType::Symbol) {
        auto sym1 = std::dynamic_pointer_cast<Symbol>(args[0]);
        auto sym2 = std::dynamic_pointer_cast<Symbol>(args[1]);
        return std::make_shared<Boolean>(sym1->name == sym2->name);
    } else if (args[0]->type() == ValueType::Boolean) {
        auto bool1 = std::dynamic_pointer_cast<Boolean>(args[0]);
        auto bool2 = std::dynamic_pointer_cast<Boolean>(args[1]);
        return std::make_shared<Boolean>(bool1->value == bool2->value);
    } else {
        // For other types, return false
        return std::make_shared<Boolean>(false);
    }
}

// Less than
std::shared_ptr<SExpression> builtin_less_than(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 2) {
        std::cerr << "Error: '<' expects exactly two arguments" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != ValueType::Number || args[1]->type() != ValueType::Number) {
        std::cerr << "Error: '<' expects numbers" << std::endl;
        return nullptr;
    }
    int num1 = std::dynamic_pointer_cast<Number>(args[0])->value;
    int num2 = std::dynamic_pointer_cast<Number>(args[1])->value;
    return std::make_shared<Boolean>(num1 < num2);
}

// Greater than
std::shared_ptr<SExpression> builtin_greater_than(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 2) {
        std::cerr << "Error: '>' expects exactly two arguments" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != ValueType::Number || args[1]->type() != ValueType::Number) {
        std::cerr << "Error: '>' expects numbers" << std::endl;
        return nullptr;
    }
    int num1 = std::dynamic_pointer_cast<Number>(args[0])->value;
    int num2 = std::dynamic_pointer_cast<Number>(args[1])->value;
    return std::make_shared<Boolean>(num1 > num2);
}

// Define
std::shared_ptr<SExpression> builtin_define(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 2) {
        std::cerr << "Error: 'define' expects exactly two arguments" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != ValueType::Symbol) {
        std::cerr << "Error: First argument to 'define' must be a symbol" << std::endl;
        return nullptr;
    }
    auto name = std::dynamic_pointer_cast<Symbol>(args[0])->name;
    auto value = args[1];
    env->define(name, value);
    return value;
}

// Set
std::shared_ptr<SExpression> builtin_set(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 2) {
        std::cerr << "Error: 'set' expects exactly two arguments" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != ValueType::Symbol) {
        std::cerr << "Error: First argument to 'set' must be a symbol" << std::endl;
        return nullptr;
    }
    auto name = std::dynamic_pointer_cast<Symbol>(args[0])->name;
    auto value = args[1];
    if (!env->set(name, value)) {
        std::cerr << "Error: Undefined symbol '" << name << "'" << std::endl;
        return nullptr;
    }
    return value;
}

// Cons
std::shared_ptr<SExpression> builtin_cons(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 2) {
        std::cerr << "Error: 'cons' expects exactly two arguments" << std::endl;
        return nullptr;
    }
    return std::make_shared<Cons>(args[0], args[1]);
}

// Car
std::shared_ptr<SExpression> builtin_car(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 1) {
        std::cerr << "Error: 'car' expects exactly one argument" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != ValueType::Cons) {
        std::cerr << "Error: 'car' expects a non-empty list" << std::endl;
        return nullptr;
    }
    auto cons = std::dynamic_pointer_cast<Cons>(args[0]);
    return cons->car;
}

// Cdr
std::shared_ptr<SExpression> builtin_cdr(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 1) {
        std::cerr << "Error: 'cdr' expects exactly one argument" << std::endl;
        return nullptr;
    }
    if (args[0]->type() != ValueType::Cons) {
        std::cerr << "Error: 'cdr' expects a non-empty list" << std::endl;
        return nullptr;
    }
    auto cons = std::dynamic_pointer_cast<Cons>(args[0]);
    return cons->cdr;
}

// Number?
std::shared_ptr<SExpression> builtin_numberp(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 1) {
        std::cerr << "Error: 'number?' expects exactly one argument" << std::endl;
        return nullptr;
    }
    return std::make_shared<Boolean>(args[0]->type() == ValueType::Number);
}

// Symbol?
std::shared_ptr<SExpression> builtin_symbolp(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 1) {
        std::cerr << "Error: 'symbol?' expects exactly one argument" << std::endl;
        return nullptr;
    }
    return std::make_shared<Boolean>(args[0]->type() == ValueType::Symbol);
}

// List?
std::shared_ptr<SExpression> builtin_listp(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 1) {
        std::cerr << "Error: 'list?' expects exactly one argument" << std::endl;
        return nullptr;
    }
    return std::make_shared<Boolean>(args[0]->type() == ValueType::Cons || args[0]->type() == ValueType::Nil);
}

// Nil?
std::shared_ptr<SExpression> builtin_nilp(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() != 1) {
        std::cerr << "Error: 'nil?' expects exactly one argument" << std::endl;
        return nullptr;
    }
    return std::make_shared<Boolean>(args[0]->type() == ValueType::Nil);
}

// And?
std::shared_ptr<SExpression> builtin_andp(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    for (auto arg : args) {
        if (arg->type() == ValueType::Boolean) {
            auto bool_arg = std::dynamic_pointer_cast<Boolean>(arg);
            if (!bool_arg->value) {
                return std::make_shared<Boolean>(false);
            }
        } else {
            return std::make_shared<Boolean>(false);
        }
    }
    return std::make_shared<Boolean>(true);
}

// Or?
std::shared_ptr<SExpression> builtin_orp(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    for (auto arg : args) {
        if (arg->type() == ValueType::Boolean) {
            auto bool_arg = std::dynamic_pointer_cast<Boolean>(arg);
            if (bool_arg->value) {
                return std::make_shared<Boolean>(true);
            }
        } else {
            return std::make_shared<Boolean>(true);
        }
    }
    return std::make_shared<Boolean>(false);
}

// Eq?
std::shared_ptr<SExpression> builtin_eqp(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    return builtin_equal(args, env);
}

// Cond
std::shared_ptr<SExpression> builtin_cond(std::vector<std::shared_ptr<SExpression>> args, std::shared_ptr<Environment> env) {
    if (args.size() % 2 != 0) {
        std::cerr << "Error: 'cond' expects pairs of test and result expressions" << std::endl;
        return nullptr;
    }
    for (size_t i = 0; i < args.size(); i += 2) {
        auto test_expr = args[i];
        auto result_expr = args[i + 1];
        auto test_result = test_expr->eval(env);
        if (test_result && test_result->type() != ValueType::Nil) {
            return result_expr->eval(env);
        }
    }
    return NIL;
}

// Initialize global environment
void initGlobalEnvironment(std::shared_ptr<Environment> env) {
    env->define("+", std::make_shared<Function>(builtin_add));
    env->define("-", std::make_shared<Function>(builtin_subtract));
    env->define("*", std::make_shared<Function>(builtin_multiply));
    env->define("/", std::make_shared<Function>(builtin_divide));
    env->define("=", std::make_shared<Function>(builtin_equal));
    env->define("<", std::make_shared<Function>(builtin_less_than));
    env->define(">", std::make_shared<Function>(builtin_greater_than));
    env->define("define", std::make_shared<Function>(builtin_define));
    env->define("set", std::make_shared<Function>(builtin_set));
    env->define("cons", std::make_shared<Function>(builtin_cons));
    env->define("car", std::make_shared<Function>(builtin_car));
    env->define("cdr", std::make_shared<Function>(builtin_cdr));
    env->define("number?", std::make_shared<Function>(builtin_numberp));
    env->define("symbol?", std::make_shared<Function>(builtin_symbolp));
    env->define("list?", std::make_shared<Function>(builtin_listp));
    env->define("nil?", std::make_shared<Function>(builtin_nilp));
    env->define("AND?", std::make_shared<Function>(builtin_andp));
    env->define("OR?", std::make_shared<Function>(builtin_orp));
    env->define("EQ?", std::make_shared<Function>(builtin_eqp));
    env->define("COND", std::make_shared<Function>(builtin_cond));
    // You can add more built-in functions here
}

// REPL function
void repl() {
    auto globalEnv = std::make_shared<Environment>();
    initGlobalEnvironment(globalEnv);

    while (true) {
        std::cout << "> ";
        std::string input_line;
        if (!std::getline(std::cin, input_line)) {
            break;
        }

        // Skip empty lines
        if (input_line.empty()) {
            continue;
        }

        // Handle multi-line inputs
        int paren_balance = 0;
        for (char c : input_line) {
            if (c == '(') paren_balance++;
            else if (c == ')') paren_balance--;
        }

        while (paren_balance > 0) {
            std::cout << "  ";
            std::string continuation_line;
            if (!std::getline(std::cin, continuation_line)) {
                break;
            }
            input_line += "\n" + continuation_line;
            for (char c : continuation_line) {
                if (c == '(') paren_balance++;
                else if (c == ')') paren_balance--;
            }
        }

        std::istringstream input(input_line);
        auto expr = parse(input);
        if (expr) {
            auto result = expr->eval(globalEnv);
            if (result) {
                result->print(std::cout);
                std::cout << std::endl;
            }
        } else {
            std::cerr << "Failed to parse S-Expression." << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    auto globalEnv = std::make_shared<Environment>();
    initGlobalEnvironment(globalEnv);

    if (argc > 1) {
        // Filename provided, execute the file
        std::string filename = argv[1];
        std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
            return 1;
        }

        // Read the entire file content
        std::string file_content((std::istreambuf_iterator<char>(infile)),
                                  std::istreambuf_iterator<char>());

        // Create a stringstream for parsing
        std::istringstream input(file_content);

        // Tokenizer for the file input
        Tokenizer tokenizer(input);

        // Parse and evaluate each expression in the file
        while (true) {
            auto expr = parseSExpression(tokenizer);
            if (!expr) {
                break; // End of file or parsing error
            }
            auto result = expr->eval(globalEnv);
            if (result) {
                result->print(std::cout);
                std::cout << std::endl;
            }
        }
    } else {
        // No filename provided, start REPL
        repl();
    }

    return 0;
}





























/* 
// Abstract base class for S-Expressions
class SExpression {
public:
    virtual ~SExpression() {}
    virtual void print(std::ostream& out) const = 0;
};

// Class representing atoms (symbols or numbers)
class Atom : public SExpression {
public:
    std::string value;

    Atom(const std::string& v) : value(v) {}

    void print(std::ostream& out) const override {
        out << value;
    }
};

// Class representing lists of S-Expressions
class List : public SExpression {
public:
    std::vector<SExpression*> elements;

    ~List() {
        for (auto e : elements) {
            delete e;
        }
    }

    void print(std::ostream& out) const override {
        out << "(";
        for (size_t i = 0; i < elements.size(); ++i) {
            elements[i]->print(out);
            if (i != elements.size() - 1) out << " ";
        }
        out << ")";
    }
};

// Tokenizer class to split input into tokens
class Tokenizer {
public:
    Tokenizer(std::istream& in) : input(in), line_no(1), has_unget(false) {}

    std::string nextToken() {
        if (has_unget) {
            has_unget = false;
            return unget_token;
        }

        // Skip whitespace
        while (std::isspace(peek())) {
            if (peek() == '\n') line_no++;
            get();
        }

        if (input.eof()) return "";

        char c = peek();
        if (c == '(' || c == ')') {
            get();
            return std::string(1, c);
        } else {
            std::string atom;
            while (!input.eof() && !std::isspace(peek()) && peek() != '(' && peek() != ')') {
                atom += get();
            }
            return atom;
        }
    }

    void unget(const std::string& token) {
        has_unget = true;
        unget_token = token;
    }

    int lineNumber() const { return line_no; }

private:
    std::istream& input;
    int line_no;
    bool has_unget;
    std::string unget_token;

    char peek() { return input.peek(); }
    char get() { return input.get(); }
};

// Function to parse S-Expressions
SExpression* parseSExpression(Tokenizer& tokenizer) {
    std::string token = tokenizer.nextToken();
    if (token == "") {
        // End of input
        return nullptr;
    } else if (token == "(") {
        // Start of a list
        List* list = new List();
        while (true) {
            std::string nextToken = tokenizer.nextToken();
            if (nextToken == "") {
                // Error: unexpected end of input
                std::cerr << "Error: Unexpected end of input while parsing list" << std::endl;
                delete list;
                return nullptr;
            } else if (nextToken == ")") {
                // End of list
                break;
            } else {
                tokenizer.unget(nextToken);
                SExpression* expr = parseSExpression(tokenizer);
                if (!expr) {
                    // Error in subexpression
                    delete list;
                    return nullptr;
                }
                list->elements.push_back(expr);
            }
        }
        return list;
    } else if (token == ")") {
        // Error: unexpected ')'
        std::cerr << "Error: Unexpected ')' at line " << tokenizer.lineNumber() << std::endl;
        return nullptr;
    } else {
        // Atom
        return new Atom(token);
    }
}

// Function to parse input and return an S-Expression
SExpression* parse(std::istream& in) {
    Tokenizer tokenizer(in);
    SExpression* expr = parseSExpression(tokenizer);
    return expr;
}

// REPL function
void repl() {
    while (true) {
        std::cout << "> ";
        std::string input_line;
        if (!std::getline(std::cin, input_line)) {
            break;
        }

        // Keep reading lines until we have balanced parentheses
        int paren_balance = 0;
        for (char c : input_line) {
            if (c == '(') paren_balance++;
            else if (c == ')') paren_balance--;
        }

        while (paren_balance > 0) {
            std::cout << "  ";
            std::string continuation_line;
            if (!std::getline(std::cin, continuation_line)) {
                break;
            }
            input_line += "\n" + continuation_line;
            for (char c : continuation_line) {
                if (c == '(') paren_balance++;
                else if (c == ')') paren_balance--;
            }
        }

        std::istringstream input(input_line);
        SExpression* expr = parse(input);
        if (expr) {
            expr->print(std::cout);
            std::cout << std::endl;
            delete expr;
        } else {
            std::cerr << "Failed to parse S-Expression." << std::endl;
        }
    }
}

int main() {
    repl();
    return 0;
}
*/ 