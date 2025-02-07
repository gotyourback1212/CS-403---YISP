; Defining a function that calculates the factorial of a number
(defun factorial (n)
    (if (eq n 0)
        1
        (* n (factorial (- n 1)))))


; Testing factorial calculation
(if (eq (factorial 5) 120)
    #T
    nil)  ; Expected output: #T (5! = 120)



; Defining a function to sum two numbers
(defun add (a b)
    (+ a b))

(if (eq (add 10 20) 30)
    #T
    nil)  ; Expected output: #T (10 + 20 = 30)



; Using `cond` to demonstrate multiple conditions
(defun check-number (n)
    (cond
        ((lt n 0) (quote negative))
        ((eq n 0) (quote zero))
        (#T (quote positive))))



; Testing `cond` with a negative number
(if (eq (check-number -5) (quote negative))
    #T
    nil)  ; Expected output: #T (since -5 is negative)



; Testing `cond` with zero
(if (eq (check-number 0) (quote zero))
    #T
    nil)  ; Expected output: #T (since 0 is zero)



; Using `cons`, `car`, and `cdr` to manipulate lists
(defun list-demo ()
    (cons 1 (cons 2 (cons 3 nil)))) ; Creates the list (1 2 3)

(if (eq (car (list-demo)) 1)
    #T
    nil)  ; Expected output: #T (first element is 1)

(if (eq (cdr (list-demo)) (cons 2 (cons 3 nil)))
    #T
    nil)  ; Expected output: #T (cdr returns the rest of the list)



; Defining a function to check if a number is even using `if` and `%`
(defun is-even (n)
    (if (eq (% n 2) 0)
        #T
        nil))




; Testing `is-even` function
(if (is-even 4)
    #T
    nil)  ; Expected output: #T (4 is even)

(if (not (is-even 5))
    #T
    nil)  ; Expected output: #T (5 is not even)



; Demonstrating variable assignment and scope
(set x 100)

(if (eq x 100)
    #T
    nil)  ; Expected output: #T (x is set to 100)



; Demonstrating `eval` and `quote` with arithmetic expressions
(eval (quote (+ 1 2)))  ; Expected output: 3


; Logical operators demonstration
(if (and (is-even 4) (not (is-even 5)))
    #T
    nil)  ; Expected output: #T (4 is even AND 5 is not even)

(if (or (is-even 4) (is-even 5))
    #T
    nil)  ; Expected output: #T (at least one is even: 4)



; Recursive function for computing the nth Fibonacci number
(defun fib (n)
    (if (lt n 2)
        n
        (+ (fib (- n 1)) (fib (- n 2)))))



; Testing Fibonacci calculation
(if (eq (fib 6) 8)
    #T
    nil)  ; Expected output: #T (6th Fibonacci number is 8)





