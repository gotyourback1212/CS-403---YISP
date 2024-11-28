<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Lisp Interpreter README</title>
</head>
<body>
    <h1>README</h1>
    <strong>Adam Howard CWID: 12137238 Lisp Interpreter</strong><br>
    <strong>Language Used:</strong> C++ (17 or later)<br>
    <strong>Environments that the interpreter has been tested in:</strong> MacOS, Windows 11<br>
    <strong>Compile command:</strong> <code>Use the make file by typing 'make' in the terminal</code><br>
    <strong>Run command:</strong> <code>To run the code with test file type: ./lisp_interpreter [file name], otherwise will run in terminal.</code><br>
    <strong>Run command testCases:</strong> <code>./lisp_interpreter testCases.txt</code><br><br>

    <details>
        <summary><strong>Introduction to the Lisp Interpreter</strong></summary>
        <p>This Lisp interpreter was implemented to demonstrate the basics of Lisp language features, including arithmetic operations, logical operations, conditionals, list operations, and user-defined functions. This interpreter handles a simplified version of Lisp, which makes it perfect for beginners to understand how Lisp-like interpreters work.</p>
        <p>The results of various operations are either <code>#T</code> for true or <code>nil</code> for false. Test cases have been designed to validate the functionalities of the interpreter, using <code>passFail</code> functions to verify if the output matches the expected value.</p>
    </details>

    <details>
        <summary><strong>Test Cases Overview</strong></summary>
        <p>Test cases are used to validate the different functionalities of the Lisp interpreter. Each test case follows a simple structure that checks if the actual output matches the expected output. Below are examples of the types of operations tested:</p>
        <ul>
            <li>Arithmetic Operations</li>
            <li>Comparison Functions</li>
            <li>Logical Operations</li>
            <li>Conditional Operations</li>
            <li>List Operations (CAR, CDR, CONS)</li>
            <li>User-Defined Functions</li>
            <li>Quoting and Evaluation</li>
        </ul>
    </details>

    <details>
        <summary><strong>Example Test Case Breakdown</strong></summary>
        <h3>Arithmetic Operations</h3>
        <p>We perform arithmetic operations using predefined variables or direct numbers, such as addition, subtraction, multiplication, division, and modulo. The results are checked against the expected value using the <code>passFail</code> function.</p>
        <ul>
            <li><strong>Example:</strong> <code>(passFail (+ 10 5) 15)</code> checks if the addition of 10 and 5 results in 15. If correct, it returns "PASSED"; otherwise, "FAILED".</li>
        </ul>

        <h3>Logical Operations</h3>
        <p>Logical operations include <code>not</code>, <code>and</code>, and <code>or</code>. They are used to test the logical combination of boolean results from comparison functions.</p>
        <ul>
            <li><strong>Example:</strong> <code>(passFail (and (gt 10 5) (lt 5 10)) #T)</code> checks if both <code>10 &gt; 5</code> and <code>5 &lt; 10</code> are true. Expected output: <code>#T</code>.</li>
        </ul>

        <h3>Conditional Operations</h3>
        <p>Conditional tests include testing <code>if</code> statements and <code>cond</code> expressions.</p>
        <ul>
            <li><strong>Example:</strong> <code>(passFail (if (gt 10 5) #T nil) #T)</code> checks if the <code>if</code> condition <code>10 &gt; 5</code> results in <code>#T</code>.</li>
        </ul>
    </details>

    <details>
        <summary><strong>Explanation of #T and nil</strong></summary>
        <p>In this Lisp interpreter:</p>
        <ul>
            <li><code>#T</code> represents <strong>true</strong>.</li>
            <li><code>nil</code> represents <strong>false</strong>.</li>
        </ul>
        <p>These boolean values are used to validate conditions, logical operations, and results from functions.</p>
    </details>

    <details>
        <summary><strong>Sample Test Cases</strong></summary>
        <details>
            <summary><strong>Arithmetic Operations</strong></summary>
            <ul>
                <li>Testing Addition: <code>(passFail (+ 10 5) 15)</code> (Expected: PASSED)</li>
                <li>Testing Subtraction: <code>(passFail (- 10 5) 5)</code> (Expected: PASSED)</li>
                <li>Testing Multiplication: <code>(passFail (* 10 5) 50)</code> (Expected: PASSED)</li>
                <li>Testing Division: <code>(passFail (/ 10 2) 5)</code> (Expected: PASSED)</li>
                <li>Testing Modulo: <code>(passFail (% 10 3) 1)</code> (Expected: PASSED)</li>
            </ul>
        </details>

        <details>
            <summary><strong>Comparison Operations</strong></summary>
            <ul>
                <li>Testing Greater Than: <code>(passFail (gt 10 5) #T)</code> (Expected: PASSED)</li>
                <li>Testing Less Than: <code>(passFail (lt 5 10) #T)</code> (Expected: PASSED)</li>
                <li>Testing Greater Than or Equal: <code>(passFail (gte 10 10) #T)</code> (Expected: PASSED)</li>
                <li>Testing Less Than or Equal: <code>(passFail (lte 7 8) #T)</code> (Expected: PASSED)</li>
                <li>Testing Equality: <code>(passFail (eq 5 5) #T)</code> (Expected: PASSED)</li>
                <li>Testing Not Equal: <code>(passFail (eq 5 6) nil)</code> (Expected: PASSED)</li>
            </ul>
        </details>

        <details>
            <summary><strong>List Operations (CAR, CDR, CONS)</strong></summary>
            <ul>
                <li>Constructing List: <code>(set x (cons 1 (cons 2 (cons 3 nil))))</code></li>
                <li>Testing CAR: <code>(passFail (car x) 1)</code> (Expected: PASSED)</li>
                <li>Testing CDR: <code>(passFail (cdr x) (cons 2 (cons 3 nil)))</code> (Expected: PASSED)</li>
                <li>Testing Nested CAR/CDR: <code>(passFail (car (cdr (cdr x))) 3)</code> (Expected: PASSED)</li>
            </ul>
        </details>

        <details>
            <summary><strong>User-Defined Functions</strong></summary>
            <ul>
                <li>Defining Function <code>add3</code>: <code>(defun add3 (a) (+ a 3))</code></li>
                <li>Testing Function <code>add3</code>: <code>(passFail (add3 5) 8)</code> (Expected: PASSED)</li>
                <li>Defining Function <code>max</code>: <code>(defun max (a b) (if (gt a b) a b))</code></li>
                <li>Testing Function <code>max</code>: <code>(passFail (max 10 20) 20)</code> (Expected: PASSED)</li>
            </ul>
        </details>

        <details>
            <summary><strong>Quote & Eval Operations</strong></summary>
            <ul>
                <li>Quoting a List: <code>(passFail (quote (1 2 3)) (cons 1 (cons 2 (cons 3 nil))))</code> (Expected: PASSED)</li>
                <li>Evaluating a Quoted Expression: <code>(passFail (eval (quote (+ 2 3))) 5)</code> (Expected: PASSED)</li>
            </ul>
        </details>
    </details>
</body>
</html>