<html>
<head>
    <title>Lisp Interpreter - README</title>
</head>
<body>
    <h1>Adam Howard - Lisp Interpreter</h1>
    <p><strong>CWID:</strong> 12137238</p>
    <h2>Introduction</h2>
    <p>This Lisp interpreter was implemented to demonstrate the basics of Lisp language features, including arithmetic operations, logical operations, conditionals, list operations, and user-defined functions.</p>
    <details>
        <summary><strong>List of Implemented Functions</strong></summary>
        <ul>
            <li><strong>Arithmetic Operations:</strong> +, -, *, /, %</li>
            <li><strong>Comparison Operations:</strong> lt, gt, lte, gte, eq</li>
            <li><strong>Logical Operations:</strong> and, or, not</li>
            <li><strong>Type Checks:</strong> NUM?, SYM?, LIST?, NIL?</li>
            <li><strong>List Operations:</strong> car, cdr, cons</li>
            <li><strong>Conditional Operations:</strong> if, cond</li>
            <li><strong>User Defined Functions:</strong> defun, set</li>
            <li><strong>Quoting and Evaluation:</strong> quote, eval</li>
            <li><strong>SET:</strong> set</li>
        </ul>
    </details>
<details>
        <summary><strong>Snapshot Overview</strong></summary>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 1</strong></summary>
            <ul>
                <li>In this snapshot, the basic arithmetic operations were implemented, allowing addition, subtraction, multiplication, division, and modulo. Test cases were written to verify the accuracy of these operations.</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 2</strong></summary>
            <ul>
                <li>Comparison functions such as lt, gt, lte, gte, and eq were added. Test cases validated correct logical responses for different input scenarios.</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 3</strong></summary>
            <ul>
                <li>Logical operations including and, or, and not were implemented. Test cases demonstrated successful logical computation involving multiple conditions.</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 4</strong></summary>
            <ul>
                <li>Type checking functions were introduced to identify numbers, symbols, lists, or nil. These functions were verified through comprehensive test cases.</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 5</strong></summary>
            <ul>
                <li>List operations using car, cdr, and cons were added. These operations helped in creating and manipulating list structures, as verified by the test cases.</li>
            </ul>
        </details>
        <details style="margin-left: 20px;">
            <summary><strong>Snapshot 6</strong></summary>
            <ul>
                <li>User-defined functions and conditional constructs were added, allowing for more flexible and dynamic behavior. The quote and eval functions were also introduced.</li>
            </ul>
        </details>
    </details>
    <details>
        <summary><strong>Sample Test Cases</strong></summary>
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
            <li>Setting Variable and Using It: <code>(set a 10) (passFail (+ a 5) 15)</code> PASSED)</li>
        </ul>
    </details>
    </details>
</body>
</html>
