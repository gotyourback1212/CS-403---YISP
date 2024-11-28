;;Prints out if expected equals output of expression
(defun passFail (actual expected)  
    (if (eq actual expected)
        "PASSED"
        "FAILED"
    )
)


(quote "ARITHMETIC OPERATIONS WITH VARIABLES (+ - * / %):  a = 10  b = 5")
;; Set variable values
(set a 10)
(set b 5)

;; Addition using set variables
;; Addition using set variables
(print "Testing Addition:            '(+ a b)'                      (Expected: 15):             " 
    (passFail (+ a b) 15))  ; Expected Result: Pass

;; Subtraction using set variables
(print "Testing Subtraction:         '(- a b)'                      (Expected: 5):              " 
    (passFail (- a b) 5))  ; Expected Result: Pass

;; Multiplication using set variables
(print "Testing Multiplication:      '(* a b)'                      (Expected: 50):             " 
    (passFail (* a b) 50))  ; Expected Result: Pass

;; Division using set variables
(print "Testing Division:            '(/ a b)'                      (Expected: 2):              " 
    (passFail (/ a b) 2))  ; Expected Result: Pass

;; Modulo using set variables
(print "Testing Modulo:              '(% a b)'                      (Expected: 0):              " 
    (passFail (% a b) 0))  ; Expected Result: Pass

;; Complex Expression using set variables
(print "Testing Complex Expression:  '(+ (* a b) (- a b))'          (Expected: 55):             " 
    (passFail (+ (* a b) (- a b)) 55))  ; Expected Result: Pass

(print "Testing Complex Expression:  '(+ (+ b (* a b)) (/ a b))'    (Expected: 57):             " 
        (passFail (+ (+ b (* a b)) (/ a b)) 57))  ; Expected Result: Pass




(quote "")
(quote "")
(quote "COMPARISION OPERATIONS WITH VARIABLES (gt, lt, gte, lte, eq):  a = 10  b = 5")
;; Setting Variables for Comparison Operations
(set a 10)
(set b 5)

;; Test Greater Than Operation
(print "Testing Greater Than:          '(gt a b)'       (Expected: #T):       " (passFail (gt a b) #T))  ; Expected Result: Pass
(print "Testing Greater Than:          '(gt b a)'       (Expected: nil):      " (passFail (gt b a) nil))  ; Expected Result: Pass

;; Test Less Than Operation
(print "Testing Less Than:             '(lt b a)'       (Expected: #T):       " (passFail (lt b a) #T))  ; Expected Result: Pass
(print "Testing Less Than:             '(lt a b)'       (Expected: nil):      " (passFail (lt a b) nil))  ; Expected Result: Pass

;; Test Equal To Operation
(print "Testing Equality:              '(eq a a)'       (Expected: #T):       " (passFail (eq a a) #T))  ; Expected Result: Pass
(print "Testing Not Equal:             '(eq a b)'       (Expected: nil):      " (passFail (eq a b) nil))  ; Expected Result: Pass

;; Test Greater Than or Equal To Operation
(print "Testing Greater Than or Equal: '(gte a b)'      (Expected: #T):       " (passFail (gte a b) #T))  ; Expected Result: Pass
(print "Testing Greater Than or Equal: '(gte b a)'      (Expected: nil):      " (passFail (gte b a) nil)) ; Expected Result: Pass
(print "Testing Greater Than or Equal: '(gte a a)'      (Expected: #T):       " (passFail (gte a a) #T)) ; Expected Result: Pass

;; Test Less Than or Equal To Operation
(print "Testing Less Than or Equal:    '(lte b a)'      (Expected: #T):       " (passFail (lte b a) #T))  ; Expected Result: Pass
(print "Testing Less Than or Equal:    '(lte a b)'      (Expected: nil):      " (passFail (lte a b) nil)) ; Expected Result: Pass
(print "Testing Less Than or Equal:    '(lte a a)'      (Expected: #T):       " (passFail (lte a a) #T)) ; Expected Result: Pass



(quote "")
(quote "")
(quote "LOGICAL OPERATIONS (AND OR NOT)")
;; Logical AND test
(print "Testing Logical AND:                                    '(and #T #T)'                                         (Expected: #T):          " 
    (passFail (and #T #T) #T))  ; Expected Result: Pass

(print "Testing Logical AND:                                    '(and nil #T)'                                        (Expected: nil):         " 
    (passFail (and nil #T) nil))  ; Expected Result: Pass

;; Logical OR test
(print "Testing Logical OR:                                     '(or nil #T)'                                         (Expected: #T):         " 
    (passFail (or nil #T) #T))  ; Expected Result: Pass

(print "Testing Logical OR:                                     '(or nil nil)'                                        (Expected: nil):        " 
    (passFail (or nil nil) nil))  ; Expected Result: Pass

;; Logical NOT test
(print "Testing Logical NOT:                                    '(not nil)'                                           (Expected: #T):         " 
    (passFail (not nil) #T))  ; Expected Result: Pass

(print "Testing Logical NOT:                                    '(not #T)'                                            (Expected: nil):        " 
    (passFail (not #T) nil))  ; Expected Result: Pass


;; NOT Operation with Comparison Functions
(print "Testing NOT operation on 'gt 5 10':                     '(not (gt 5 10))'                                     (Expected: #T):        " 
    (passFail (not (gt 5 10)) #T))  ; Expected Result: PASSED

(print "Testing NOT operation on 'lt 5 10':                     '(not (lt 5 10))'                                     (Expected: nil):       " 
    (passFail (not (lt 5 10)) nil))  ; Expected Result: PASSED

;; AND Operation with Comparison Functions
(print "Testing AND operation on '(gt 10 5) (lt 5 10)':         '(and (gt 10 5) (lt 5 10))'                           (Expected: #T):        " 
    (passFail (and (gt 10 5) (lt 5 10)) #T))  ; Expected Result: PASSED

(print "Testing AND operation with one false condition          '(lt 10 5) (lt 5 10)': '(and (lt 10 5) (lt 5 10))'    (Expected: nil):       " 
    (passFail (and (lt 10 5) (lt 5 10)) nil))  ; Expected Result: PASSED

;; OR Operation with Comparison Functions
(print "Testing OR operation with one true condition            '(gt 10 5) (gt 5 10)': '(or (gt 10 5) (gt 5 10))'     (Expected: #T):       " 
    (passFail (or (gt 10 5) (gt 5 10)) #T))  ; Expected Result: PASSED

(print "Testing OR operation with both false conditions         '(lt 5 4) (lt 3 2)': '(or (lt 5 4) (lt 3 2))'         (Expected: nil):      " 
    (passFail (or (lt 5 4) (lt 3 2)) nil))  ; Expected Result: PASSED



(quote "")
(quote "")
(quote "TYPE CHECKS (SYM?, NUM?, LIST?, NIL?) a = 1  b = x") 
(set a 1)
(set b x)

;; Type check for Symbol
(print "Testing Symbol Check:         '(SYM? 'x)'               (Expected: #T):       " (passFail (SYM? x) #T))  ; Expected Result: Pass
(print "Testing Symbol Check:         '(SYM? 2)'                (Expected: nil):      " (passFail (SYM? 2) nil))  ; Expected Result: Pass
(print "Testing Symbol Check:         '(SYM? b)'                (Expected: #T):       " (passFail (SYM? x) #T))  ; Expected Result: Pass
(print "Testing Symbol Check:         '(SYM? a)'                (Expected: nil):      " (passFail (SYM? 2) nil))  ; Expected Result: Pass

;; Type check for Number
(print "Testing Number Check:         '(NUM? 10)'               (Expected: #T):       " (passFail (NUM? 10) #T))  ; Expected Result: Pass
(print "Testing Number Check:         '(NUM? x)'                (Expected: nil):      " (passFail (NUM? x) nil))  ; Expected Result: Pass


(print "Testing Number Check:         '(NUM? a)'                (Expected: #T):       " (passFail (NUM? a) #T))  ; Expected Result: Pass
(print "Testing Number Check:         '(NUM? b)'                (Expected: nil):      " (passFail (NUM? b) nil))  ; Expected Result: Pass

;; Type check for List
(print "Testing List Check:           '(LIST? (cons 1 nil))'    (Expected: #T):    " (passFail (LIST? (cons 1 nil)) #T))  ; Expected Result: Pass

;; Type check for NIL
(print "Testing NIL Check:            '(NIL? nil)'              (Expected: #T):       " (passFail (NIL? nil) #T))  ; Expected Result: Pass
(print "Testing NIL Check:            '(NIL? #T)'               (Expected: nil):      " (passFail (NIL? #T) nil))  ; Expected Result: Pass


(quote "")
(quote "")
(quote "LIST OPERATIONS (CAR, CDR, CONS):   x = (1 2 3)") 

;; Construct list using cons
(set x (cons 1 (cons 2 (cons 3 nil))))

(print "Testing List Construction with 'cons':              '(set x (cons 1 (cons 2 (cons 3 nil))))'                                    (Expected: #T):                               " 
    (passFail (car x) 1))  ; Expected Result: PASSED

;; Get the rest of the list using cdr
(print "Testing cdr operation on list 'x':                  '(cdr x)'                                                                   (Expected: (cons 2 (cons 3 nil))):            " 
    (passFail (cdr x) (cons 2 (cons 3 nil))))  ; Expected Result: PASSED

;; Nested list car and cdr test
(print "Testing car of cdr on list 'x':                     '(car (cdr x))'                                                             (Expected: 2):                                " 
    (passFail (car (cdr x)) 2))  ; Expected Result: PASSED

;; Nested list car and cdr test
(print "Testing car of cdr on list 'x':                     '(car (cdr (cdr x)))'                                                       (Expected: 3):                                " 
    (passFail (car (cdr (cdr x))) 3))  ; Expected Result: PASSED

;; Construct a list using cons
(set x (cons 1 (cons 2 (cons 3 (cons 4 nil)))))
    (print "Testing List Construction with 'cons':              '(set x (cons 1 (cons 2 (cons 3 (cons 4 nil)))))'                           (Expected: #T):                                " 
        (passFail (car x) 1))  ; Expected Result: PASSED

;; Get the rest of the list using cdr
(print "Testing cdr operation on list 'x':                  '(cdr x)'                                                                   (Expected: (2 3 4)):                           " 
    (passFail (cdr x) (cons 2 (cons 3 (cons 4 nil)))))  ; Expected Result: PASSED

;; Nested list car and cdr test
(print "Testing car of cdr on list 'x':                     '(car (cdr x))'                                                             (Expected: 2):                                 " 
    (passFail (car (cdr x)) 2))  ; Expected Result: PASSED

;; Get the third element of the list using nested cdrs
(print "Testing car of cdr of cdr on list 'x':              '(car (cdr (cdr x)))'                                                       (Expected: 3):                                 " 
    (passFail (car (cdr (cdr x))) 3))  ; Expected Result: PASSED

;; Construct a more complex nested list
(set y (cons (cons 1 (cons 2 nil)) (cons (cons 3 (cons 4 nil)) nil)))
(print "Testing Nested List Construction:                   '(set y (cons (cons 1 (cons 2 nil)) (cons (cons 3 (cons 4 nil)) nil)))'     (Expected: #T):                                " 
    (passFail (car (car y)) 1))  ; Expected Result: PASSED

;; Test car operation on nested list
(print "Testing car operation on nested list 'y':           '(car (car y))'                                                             (Expected: 1):                                 " 
    (passFail (car (car y)) 1))  ; Expected Result: PASSED

;; Test cdr operation on nested list
(print "Testing cdr operation on nested list 'y':           '(cdr (car y))'                                                             (Expected: (2)):                               " 
    (passFail (cdr (car y)) (cons 2 nil)))  ; Expected Result: PASSED

;; Construct a list and add an element at the front using cons
(set z (cons 0 x))
(print "Testing cons to add element to front of list 'x':   '(set z (cons 0 x))'                                                        (Expected: (0 1 2 3 4)):                      " 
    (passFail (car z) 0))  ; Expected Result: PASSED

;; Get the rest of the list after adding an element
(print "Testing cdr after cons operation on 'z':            '(cdr z)'                                                                   (Expected: (1 2 3 4)):                        " 
    (passFail (cdr z) (cons 1 (cons 2 (cons 3 (cons 4 nil))))) )  ; Expected Result: PASSED

;; Construct a list with different data types
(set mixedList (cons 1 (cons #T (cons 'a (cons nil nil)))))
(print "Testing mixed data type list construction:          '(set mixedList (cons 1 (cons #T (cons 'a (cons nil nil)))))'               (Expected: #T):                               " 
    (passFail (car mixedList) 1))  ; Expected Result: PASSED

;; Test accessing elements in the mixed data type list
(print "Testing car of cdr of mixed list:                   '(car (cdr mixedList))'                                                     (Expected: #T):                               " 
    (passFail (car (cdr mixedList)) #T))  ; Expected Result: PASSED

(print "Testing car of cdr of cdr of mixed list:            '(car (cdr (cdr mixedList)))'                                               (Expected: 'a'):                              " 
    (passFail (car (cdr (cdr mixedList))) 'a))  ; Expected Result: PASSED

(print "Testing car of cdr of cdr of cdr of mixed list:     '(car (cdr (cdr (cdr mixedList))))'                                         (Expected: nil):                              " 
    (passFail (car (cdr (cdr (cdr mixedList)))) nil))  ; Expected Result: PASSED




(quote "")
(quote "")
(quote "CONDITIONALS")

;; If condition is true
(print "Testing IF with true condition:                                     '(if (gt 10 5) #T nil)'                                                             (Expected: #T):       " 
    (passFail (if (gt 10 5) #T nil) #T))  ; Expected Result: PASSED

;; If condition is false
(print "Testing IF with false condition:                                    '(if (lt 3 2) #T nil)'                                                              (Expected: nil):      " 
    (passFail (if (lt 3 2) #T nil) nil))  ; Expected Result: PASSED

;; If conditon with funcitons
(print "Testing IF with arithmetic operations:                              '(if (gte 3 2) (+ 1 2) (* 3 3))'                                                    (Expected: 3):        " 
    (passFail (if (gte 3 2) (+ 1 2) (* 3 3)) 3)) ; Expected Result: PASSED

;; Cond with true condition
(print "Testing COND with first false, second true condition:               '(cond ((lt 10 5) nil) ((gte 5 5) #T))'                                             (Expected: #T):       " 
    (passFail (cond ((lt 10 5) nil) ((gte 5 5) #T)) #T))  ; Expected Result: PASSED

;; Define a `cond` statement that performs different arithmetic operations
(set a 10)
(set b 5)
(print "Testing COND with arithmetic operations a = 10 b = 5:               '(cond ((lt a b) (+ a b)) ((eq a b) (- a b)) ((gt a b) (* a b)))'                   (Expected: 50):       " 
       (passFail (cond ((lt a b) (+ a b)) 
                       ((eq a b) (- a b))  
                       ((gt a b) (* a b)))       
               50)) 




(quote "")
(quote "")
(quote "USER DEFINED FUNCTIONS")

;; Define a function for addition and test it
(defun add3 (a) (+ a 3))
(print "Defining and testing function 'add3' with input 5:                      '(add3 5)'                       (Expected: 8):        " 
    (passFail (add3 5) 8))  ; Expected Result: PASSED

;; Define a function to find the maximum of two numbers and test it
(defun max (a b) (if (gt a b) a b))
(print "Defining and testing function 'max' with inputs 10 and 20:              '(max 10 20)'                    (Expected: 20):       " 
    (passFail (max 10 20) 20))  ; Expected Result: PASSED

;; Define a function to add two numbers and test it
(defun add2 (a b) (+ a b))
(print "Defining and testing function 'add2' with inputs 3 and 7:               '(add2 3 7)'                     (Expected: 10):       " 
       (passFail (add2 3 7) 10))  ; Expected Result: PASSED

;; Define a function to subtract two numbers and test it
(defun sub (a b c) (- a b c))   
(print "Defining and testing function 'sub' with inputs 10 and 4:               '(sub3 10 4 3)'                  (Expected: 3):        " 
       (passFail (sub 10 4 3) 3))  ; Expected Result: PASSED

;; Define a function to multiply three numbers and test it
(defun mul3 (a b c) (* a (* b c)))
(print "Defining and testing function 'mul3' with inputs 2, 3, and 4:           '(mul3 2 3 4)'                   (Expected: 24):       " 
       (passFail (mul3 2 3 4) 24))  ; Expected Result: PASSED

;; Define a function to check if a number is positive and test it
(defun isPositive (n) (gt n 0))
(print "Defining and testing function 'isPositive' with input 5:                '(isPositive 5)'                 (Expected: #T):      " 
       (passFail (isPositive 5) #T))  ; Expected Result: PASSED
(print "Defining and testing function 'isPositive' with input -1:               '(isPositive -1)'                (Expected: nil):     " 
       (passFail (isPositive -1) nil))  ; Expected Result: PASSED

;; Define a function to calculate the factorial of a number and test it
(defun factorial (n) 
    (if (lte n 1) 
        1 
        (* n (factorial (- n 1))))) 
(print "Defining and testing function 'factorial' with input 5:                 '(factorial 5)'                  (Expected: 120):      " 
       (passFail (factorial 5) 120))  ; Expected Result: PASSED

;; Define a function to find the minimum of two numbers and test it
(defun min (a b) (if (lt a b) a b))
(print "Defining and testing function 'min' with inputs 10 and 20:              '(min 10 20)'                    (Expected: 10):       " 
       (passFail (min 10 20) 10))  ; Expected Result: PASSED
(print "Defining and testing function 'min' with inputs 15 and 5:               '(min 15 5)'                     (Expected: 5):        " 
       (passFail (min 15 5) 5))  ; Expected Result: PASSED

;; Define a function to check if a value is equal to a specific number and test it
(defun isEqualToFive (n) (eq n 5))  
(print "Defining and testing function 'isEqualToFive' with input 5:             '(isEqualToFive 5)'              (Expected: #T):       " 
       (passFail (isEqualToFive 5) #T))  ; Expected Result: PASSED  
(print "Defining and testing function 'isEqualToFive' with input 6:             '(isEqualToFive 6)'              (Expected: nil):      " 
       (passFail (isEqualToFive 6) nil))  ; Expected Result: PASSED

;; Define a function to find the maximum of three numbers and test it
(defun max3 (a b c) 
    (max (max a b) c))
(print "Defining and testing function 'max3' with inputs 3, 7, and 5:           '(max3 3 7 5)'                   (Expected: 7):        " 
       (passFail (max3 3 7 5) 7))  ; Expected Result: PASSED
(print "Defining and testing function 'max3' with inputs 12, 15, and 10:        '(max3 12 15 10)'                (Expected: 15):       " 
       (passFail (max3 12 15 10) 15))  ; Expected Result: PASSED

;; Define a function that returns the first element of a list
(defun first (lst) (car lst))
(print "Defining and testing function 'first' with input '(1 2 3)':             '(first (quote (1 2 3)))'        (Expected: 1):        " 
       (passFail (first (quote (1 2 3))) 1))  ; Expected Result: PASSED


; Recursive function for computing the nth Fibonacci number
(defun fib (n)
    (if (lt n 2)
        n
        (+ (fib (- n 1)) (fib (- n 2)))))

; Testing Fibonacci calculation
(print "Testing Fibonacci calculation for n=6 demonstrating recursive calls:    '(fib 6)'                        (Expected: 8):        " 
       (passFail (fib 6) 8))  ; Expected Result: PASSED






(quote "")
(quote "")
(quote "QUOTE & EVAL")

;; Quoting a list and testing it
(print "Quoting a list '(1 2 3)':                       '(quote (1 2 3))'                (Expected: (1 2 3)):         " 
    (passFail (quote (1 2 3)) (cons 1 (cons 2 (cons 3 nil)))))  ; Expected Result: PASSED

(print "Quoting a function call '(+ 1 2)':              '(quote (+ 1 2))'                (Expected: (+ 1 2)):         " 
    (passFail (quote (+ 1 2)) (quote (+ 1 2))))  ; Expected Result: PASSED
       
;; Evaluating a quoted arithmetic expression and testing it
(print "Evaluating quoted expression '(+ 2 3)':         '(eval (quote (+ 2 3)))'         (Expected: 5):               " 
    (passFail (eval (quote (+ 2 3))) 5))  ; Expected Result: PASSED

;; Evaluating a quoted function
(defun square (x) (* x x))
(print "Evaluating quoted function with input 4:        '(eval (quote (square 4)))'      (Expected: 16):              " 
    (passFail (eval (quote (square 4))) 16))  ; Expected Result: PASSED
     



(quote "")
(quote "")
(quote "SET")

;; Set a variable and use it in an expression
(set y 25)
(print "Setting variable 'y' to 25 and adding 10:                           '(set y 25)' then '(+ y 10)'                    (Expected: 35):             "
    (passFail (+ y 10) 35))  ; Expected Result: PASSED

(set 3As aaa)
(print "Setting variable '3As' to aaa:                                      '(set 3As aaa)'  then '3As'                     (Expected: aaa):            " 
    (passFail 3As aaa))  ; Expected Result: PASSED

; Set variable a to 10
(set a 10)
(print "Setting variable 'a' to 10:                                         '(set a 10)'                                    (Expected: 10):             " 
       (passFail a 10))  ; Expected Result: PASSED

; Set variable b to 5
(set b 5)
(print "Setting variable 'b' to 5:                                          '(set b 5)'                                     (Expected: 5):              " 
       (passFail b 5))  ; Expected Result: PASSED

; Set variable c to sum of a and b
(set c (+ a b))
(print "Setting variable 'c' to the sum of 'a' and 'b':                     '(set c (+ a b))'                               (Expected: 15):             " 
       (passFail c 15))  ; Expected Result: PASSED

; Set variable d to product of a and b
(set d (* a b))
(print "Setting variable 'd' to the product of 'a' and 'b':                 '(set d (* a b))'                               (Expected: 50):             " 
       (passFail d 50))  ; Expected Result: PASSED

; Set variable f to result of list construction
(set f (cons 1 (cons 2 (cons 3 nil))))
(print "Setting variable 'f' to a list:                                     '(set f (cons 1 (cons 2 (cons 3 nil))))'        (Expected: (1 2 3)):        " 
       (passFail (car f) 1))  ; Expected Result: PASSED

; Update existing variable a to a new value
(set a 20)
(print "Updating variable 'a' to 20:                                        '(set a 20)'                                    (Expected: 20):             " 
       (passFail a 20))  ; Expected Result: PASSED

; Use variable a in another calculation
(set g (+ a 30))
(print "Setting variable 'g' to 'a + 30':                                   '(set g (+ a 30))'                              (Expected: 50):             " 
       (passFail g 50))  ; Expected Result: PASSED

; Set variable h to an evaluated list expression
(set h (eval (quote (+ a b))))
(print "Setting variable 'h' to evaluated expression '(+ a b)':             '(set h (eval (quote (+ a b))))'                (Expected: 25):             " 
       (passFail h 25))  ; Expected Result: PASSED

; Set variable i to nil and test its value
(set i nil)
(print "Setting variable 'i' to nil:                                        '(set i nil)'                                   (Expected: nil):            " 
       (passFail i nil))  ; Expected Result: PASSED

; Set variable j to the result of a user-defined function
(defun square (x) (* x x))
(set j (square 4))
(print "Setting variable 'j' to result of '(square 4)':                     '(set j (square 4))'                            (Expected: 16):             " 
       (passFail j 16))  ; Expected Result: PASSED

(quote "")
(quote "")