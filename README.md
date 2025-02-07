<html>
<head>
    <title>Lisp Interpreter - README</title>
</head>
<body>
    <h1>Adam Howard - Lisp Interpreter</h1>
    <p><strong>CS 403-001 </p>
    <p><strong>CWID:</strong> 12137238</p>
    <h2>Introduction</h2>
    <p>This Lisp interpreter was implemented to demonstrate the basics of Lisp language features, including arithmetic operations, logical operations, conditionals, list operations, and user-defined functions.</p>
    <p>To run the interpreter, compile it with the following command (ensure you have C++17 or later):</p>
    <pre><code>make</code></pre>
    <p>Once compiled, you can run the interpreter with:</p>
    <pre><code>./lisp_interpreter</code></pre>
    <p>To run a test file:</p>
    <pre><code>./lisp_interpreter &lt;filename&gt;</code></pre>
    <details>
        <summary><strong>List of Implemented Functions</strong></summary>
        <ul>
            <li><strong>Arithmetic Operations:</strong> +, -, *, /, % (or: add, minus, mul, div, mod)</li>
            <li><strong>Comparison Operations:</strong> <, >, <=,  >=, = (or: lt, gt, lte, gte, eq)</li>
            <li><strong>Logical Operations:</strong> and, or, not</li>
            <li><strong>Type Checks:</strong> NUM?, SYM?, LIST?, NIL?</li>
            <li><strong>List Operations:</strong> car, cdr, cons</li>
            <li><strong>Conditional Operations:</strong> if, cond</li>
            <li><strong>User Defined Functions:</strong> defun, set</li>
            <li><strong>Quoting and Evaluation:</strong> quote, eval</li>
        </ul>
    </details>
<details>
        <summary><strong>Snapshot Overview</strong></summary>
        <p> NOTE: All sprints are functional. However, sprints 1-4 require the print funciton to be used to print out the results of any expresssion (EX: (print (+ 1 2)) ) This was because of confussion about wheter a print function needed to be implemented for the resulst to be printed. Sprints 5-6 do not require the print function (EX: (+ 1 2) ), but it is implemeneted for testing purposes, so I can print out string to make the test cases readable.</p>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 1</strong></summary>
            <ul>
                <p> In this sprint, I implemented the basic structure of S-Expression and created an AST to just print out the exprression after it has been tokinized and parsed.</p>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 2</strong></summary>
            <ul>
                <p>In this sprint type-checking functions have been implemented to distinguish between numbers, symbols, lists, and nil values. Additionally, boolean equivalents were established, with #T representing true and nil representing false. During testing, the interpreter correctly outputs true when #T is used and nil when false is represented. Furthermore, constructors were created for symbols and numbers from strings, as well as a constructor that takes two S-expressions (cons cells), necessitating the implementation of the car and cdr functions.</p>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 3</strong></summary>
            <ul>
                <p>During this sprint, basic arithmetic functions were defined, including add (+) for addition, sub (-) for subtraction, mul (*) for multiplication, div (/) for division, and mod (%) for computing the remainder. Comparison functions were also introduced to compare numbers, such as lt (<), gt (>), lte (<=), and gte (>=). Additionally, the eq (=) function was implemented to compare two atoms, such as numbers or symbols, for equality. On the logical side, the not function was added to perform logical negation, allowing the interpreter to evaluate whether a value is logically false (nil) and return the corresponding truth value. </p>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 4</strong></summary>
           <ul>
            <p>For testing purposes, an initial implementation of the eval function was already in place ahead of this sprint. This early version served as a simple placeholder, designed to return the argument as-is. However, expanding its functionality required the introduction of a lookup function and a set function to handle symbol-value operations effectively. To manage these operations, I implemented an Environment class, which utilizes an unordered_map for efficient storage and retrieval of symbols and their corresponding values.</p>
            <p>The Environment class leverages the unordered_map data structure to map symbols (keys) to their evaluated values. The set function was implemented to insert or update entries in this map, ensuring constant-time insertion and retrieval. Similarly, the lookup function checks the map for the presence of a symbol and returns its associated value if found. If the symbol is not present in the environment, the function simply returns the symbol itself, preserving the interpreter's functionality for undefined symbols.</p>
            <p>To ensure accessibility across all operations, global functions, including set, were incorporated into the eval method. This integration allows the evaluation process to interact directly with the environment when handling symbols, ensuring a streamlined and efficient workflow.</p>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 5</strong></summary>
            <ul>
                <p>In this sprint, short-circuiting logical functions and conditional statements (if and cond) were implemented. For logical, the and function was defined to evaluate its first expression (e1). If e1 evaluates to nil, and immediately returns nil without evaluating the second expression (e2). Otherwise, e2 is evaluated, and the result is returned, which could be #T or nil. Similarly, the or function was implemented to evaluate e1 first. If e1 evaluates to a truthy value (#T), it is returned without evaluating e2. If e1 is nil, e2 is evaluated, and its result (#T or nil) is returned.</p>
                <p>For conditional execution, the if function was introduced. When invoked as (if e1 e2 e3), the interpreter evaluates e1. If e1 is truthy, the result of evaluating e2 is returned; otherwise, the result of evaluating e3 is returned. This ensures that only the necessary branch is evaluated. The cond function was similarly implemented to handle multiple conditional branches. Given pairs of conditions and expressions, cond evaluates each condition in sequence, stopping at the first truthy condition and evaluating its corresponding expression. If no condition evaluates to true, the behavior is left undefined and returns nil.</p>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 6</strong></summary>
            <ul>
                <p>In this sprint, the interpreter was extended to support user-defined functions through the introduction of the defun keyword, allowing users to define and call custom functions. The syntax (defun fname (arg0 arg1 ... argn) body) enables users to create a function named fname, specify its arguments, and provide a single S-expression as the function body. To implement this, I used an Lisp2 approach, where functions and variables are stored in separate environments to avoid conflicts and ensure proper context-specific resolution.</p>
                <p>The FunctionEnvironment class was created to manage user-defined functions. This class uses an unordered_map to store function definitions, mapping each function name to its argument list and body. The define method registers new functions, while the hasFunction and getFunction methods check for a function’s existence and retrieve its definition, respectively. These functions enable the interpreter to distinguish functions from variables, even when they share the same name, preserving the flexibility and clarity of a Lisp2 design. </p>
                <p>The evalFun method was implemented to handle the definition of user-defined functions. It validates the structure of the defun expression, ensuring it consists of exactly three arguments: the function name, a list of arguments, and a function body. The argument list is parsed to ensure all elements are symbols (or nil for no arguments), while the function body is stored as-is. The function definition is then registered in the FunctionEnvironment using the define method, and nullptr (representing nil) is returned, as the definition does not produce a result.</p>
                <p>The evalUserFun method processes calls to user-defined functions. When a user-defined function is invoked, its definition is retrieved from the FunctionEnvironment. The method validates that the number of provided arguments matches the function’s expected arguments. Each argument is then evaluated, and the results are stored in a list. A new Environment instance is created for the function call, using the current environment as its parent to support variable scoping. The evaluated arguments are then bound to their respective parameter names in the local environment.</p>
                <p>During the function call, the local environment is temporarily set as the current environment, ensuring the function body is evaluated in its own scope. Once the body is evaluated, the original environment is restored, preventing residual side effects from the function’s execution. The result of evaluating the body is returned as the function’s result.</p>
            </ul>
        </details>
    </details>
    <details>
        <summary><strong>Sample Test Cases</strong></summary>
            <p>The <code>passFail</code> function is used to validate test cases in the Lisp interpreter. It takes two arguments: the actual result of an expression and the expected value. If the actual result matches the expected value, it prints "PASSED"; otherwise, it prints "FAILED".</p>
            <ul>
                <li><strong>Defining passFail:</strong></li>
                <pre>
                    (defun passFail (actual expected)  
                        (if (eq actual expected)
                            "PASSED"
                            "FAILED"
                        )
                    )
                </pre>
                <li><strong>Usage Example:</strong></li>
                <pre>
                    (passFail (+ 10 5) 15) ; Expected Output: PASSED
                </pre>
            </ul>
             <p> Below is just few sample test cases that have been ran. Additional test cases can be seen by running the testCases.lisp file. The results can be seen in the testResults.txt file. I also implemented a print function and Strings for testing purposes only.</p>
        <details style="margin-left: 20px;">
            <summary><strong>Arithmetic Operations</strong></summary>
            <ul>
                <li>Testing Addition: <code>(passFail (+ 10 5) 15)</code> (PASSED)</li>
                <li>Testing Subtraction: <code>(passFail (- 10 5) 5)</code> (PASSED)</li>
                <li>Testing Multiplication: <code>(passFail (* 10 5) 50)</code> (PASSED)</li>
                <li>Testing Division: <code>(passFail (/ 10 2) 5)</code> (PASSED)</li>
                <li>Testing Modulo: <code>(passFail (% 10 3) 1)</code> (PASSED)</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Comparison Operations</strong></summary>
            <ul>
                <li>Testing Greater Than: <code>(passFail (gt 10 5) #T)</code> (PASSED)</li>
                <li>Testing Less Than: <code>(passFail (lt 5 10) #T)</code> (PASSED)</li>
                <li>Testing Greater Than or Equal: <code>(passFail (gte 10 10) #T)</code> (PASSED)</li>
                <li>Testing Less Than or Equal: <code>(passFail (lte 7 8) #T)</code> (PASSED)</li>
                <li>Testing Equality: <code>(passFail (eq 5 5) #T)</code> (PASSED)</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Logical Operations</strong></summary>
            <ul>
                <li>Testing Logical AND: <code>(passFail (and #T #T) #T)</code> (PASSED)</li>
                <li>Testing Logical OR: <code>(passFail (or nil #T) #T)</code> (PASSED)</li>
                <li>Testing Logical NOT: <code>(passFail (not nil) #T)</code> (PASSED)</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Type Checks</strong></summary>
            <ul>
                <li>Testing Number Check: <code>(passFail (NUM? 10) #T)</code> (PASSED)</li>
                <li>Testing Symbol Check: <code>(passFail (SYM? 'x) #T)</code> (PASSED)</li>
                <li>Testing List Check: <code>(passFail (LIST? (cons 1 nil)) #T)</code> (PASSED)</li>
                <li>Testing NIL Check: <code>(passFail (NIL? nil) #T)</code> (PASSED)</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>List Operations</strong></summary>
            <ul>
                <li>Testing CAR: <code>(passFail (car (cons 1 (cons 2 nil))) 1)</code> (PASSED)</li>
                <li>Testing CDR: <code>(passFail (cdr (cons 1 (cons 2 nil))) (cons 2 nil))</code> (PASSED)</li>
                <li>Testing CONS: <code>(passFail (cons 1 nil) (cons 1 nil))</code> (PASSED)</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Conditionals</strong></summary>
            <ul>
                <li>Testing IF with true condition: <code>(passFail (if (gt 10 5) #T nil) #T)</code> (PASSED)</li>
                <li>Testing IF with false condition: <code>(passFail (if (lt 3 2) #T nil) nil)</code> (PASSED)</li>
                <li>Testing COND with arithmetic operations: <code>(passFail (cond ((lt 10 5) nil) ((gte 5 5) #T)) #T)</code> (PASSED)</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>User-Defined Functions</strong></summary>
            <ul>
                <li>Defining Function <code>add3</code>: <code>(defun add3 (a) (+ a 3))</code></li>
                <li>Testing function <code>add3</code> with input 5: <code>(passFail (add3 5) 8)</code> (PASSED)</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Quote & Eval Operations</strong></summary>
            <ul>
                <li>Quoting a List: <code>(passFail (quote (1 2 3)) (cons 1 (cons 2 (cons 3 nil))))</code> (PASSED)</li>
                <li>Evaluating a Quoted Expression: <code>(passFail (eval (quote (+ 2 3))) 5)</code> (PASSED)</li>
            </ul>
        </details>
         <details style="margin-left: 20px;">
        <summary><strong>Set Operations</strong></summary>
        <ul>
            <li>Setting Variable and Using It: <code>(set a 10) (passFail (+ a 5) 15)</code> (PASSED)=</li>
        </ul>
    </details>
    </details>
</body>
</html>
