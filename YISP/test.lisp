;; ARITHMETIC OPERATIONS
(quote(ARITHMETIC OPERATIONS))
(quote (if (eq (+ 1 2) 3) #T nil Expected Result: true))
(if (eq (+ 1 2) 3) #T nil)                  

(quote (if (eq (- 5 3) 2) #T nil Expected Result: true))
(if (eq (- 5 3) 2) #T nil)                 

(quote (if (eq (* 4 3) 12) #T nil Expected Result: true))
(if (eq (* 4 3) 12) #T nil)                 

(quote (if (eq (/ 10 2) 5) #T nil Expected Result: true))
(if (eq (/ 10 2) 5) #T nil)            

(quote (if (eq (% 10 3) 1) #T nil Expected Result: true))
(if (eq (% 10 3) 1) #T nil)                

(quote (if (eq (+ 1 2 3 4) 10) #T nil Expected Result: true))
(if (eq (+ 1 2 3 4) 10) #T nil)            

;; COMPARISON OPERATIONS
(quote(COMPARISON OPERATIONS))
(quote (if (eq (gt 10 5) #T) #T nil Expected Result: true))
(if (eq (gt 10 5) #T) #T nil)

(quote (if (eq (lt 5 10) #T) #T nil Expected Result: true))
(if (eq (lt 5 10) #T) #T nil)

(quote (if (eq (eq 5 5) #T) #T nil Expected Result: true))
(if (eq (eq 5 5) #T) #T nil)

(quote (if (eq (eq 5 6) nil) #T nil Expected Result: true))
(if (eq (eq 5 6) nil) #T nil)

(quote (if (eq (gte 10 10) #T) #T nil Expected Result: true))
(if (eq (gte 10 10) #T) #T nil)

(quote (if (eq (lte 7 8) #T) #T nil Expected Result: true))
(if (eq (lte 7 8) #T) #T nil)

(quote (if (eq (lte 8 8) #T) #T nil Expected Result: true))
(if (eq (lte 8 8) #T) #T nil)

;; LOGICAL OPERATIONS
(quote(LOGICAL OPERATIONS))
(quote (if (eq (and #T #T) #T) #T nil Expected Result: true))
(if (eq (and #T #T) #T) #T nil)

(quote (if (eq (and #T nil) nil) #T nil Expected Result: true))
(if (eq (and #T nil) nil) #T nil)

(quote (if (eq (or #T nil) #T) #T nil Expected Result: true))
(if (eq (or #T nil) #T) #T nil)

(quote (if (eq (or nil nil) nil) #T nil Expected Result: true))
(if (eq (or nil nil) nil) #T nil)

(quote (if (eq (not #T) nil) #T nil Expected Result: true))
(if (eq (not #T) nil) #T nil)

(quote (if (eq (not nil) #T) #T nil Expected Result: true))
(if (eq (not nil) #T) #T nil)

;; CONDITIONALS
(quote(CONDITIONALS))
(quote (if (eq (if (gt 10 5) 1 0) 1) #T nil Expected Result: true))
(if (eq (if (gt 10 5) 1 0) 1) #T nil)

(quote (if (eq (if (lt 3 2) 1 0) 0) #T nil Expected Result: true))
(if (eq (if (lt 3 2) 1 0) 0) #T nil)

(quote (if (eq (if #T 42 99) 42) #T nil Expected Result: true))
(if (eq (if #T 42 99) 42) #T nil)

(quote (if (eq (if nil 42 99) 99) #T nil Expected Result: true))
(if (eq (if nil 42 99) 99) #T nil)

;; COND
(quote(COND))
(quote (if (eq (cond ((gt 10 5) 1) ((lt 3 2) 0)) 1) #T nil Expected Result: true))
(if (eq (cond ((gt 10 5) 1) ((lt 3 2) 0)) 1) #T nil)

(quote (if (eq (cond ((lt 0 0) 1) ((#T) 100)) 100) #T nil Expected Result: true))
(if (eq (cond ((lt 0 0) 1) ((#T) 100)) 100) #T nil)

(quote (if (eq (cond ((eq 2 2) 10) ((#T) 20)) 10) #T nil Expected Result: true))
(if (eq (cond ((eq 2 2) 10) ((#T) 20)) 10) #T nil)

;; LIST OPERATIONS (CONS, CAR, CDR)
(quote(LIST OPERATIONS (CONS, CAR, CDR)))
(set x (cons 1 (cons 2 (cons 3 (cons 4 ()))))) ; No Output

(quote (if (eq (cdr x) (cons 2 (cons 3 (cons 4 ())))) #T nil Expected Result: true))
(if (eq (cdr x) (cons 2 (cons 3 (cons 4 ())))) #T nil)

(quote (if (eq (cons 1 nil) (cons 1 nil)) #T nil Expected Result: true))
(if (eq (cons 1 nil) (cons 1 nil)) #T nil)

(quote (if (eq (cons 1 (cons 2 nil)) (cons 1 (cons 2 nil))) #T nil Expected Result: true))
(if (eq (cons 1 (cons 2 nil)) (cons 1 (cons 2 nil))) #T nil)

(quote (if (eq (car (cons 1 (cons 2 nil))) 1) #T nil Expected Result: true))
(if (eq (car (cons 1 (cons 2 nil))) 1) #T nil)

(quote (if (eq (cdr (cons 1 (cons 2 nil))) (cons 2 nil)) #T nil Expected Result: true))
(if (eq (cdr (cons 1 (cons 2 nil))) (cons 2 nil)) #T nil)

(quote (if (eq (car (cdr (cons 1 (cons 2 (cons 3 nil))))) 2) #T nil Expected Result: true))
(if (eq (car (cdr (cons 1 (cons 2 (cons 3 nil))))) 2) #T nil)

;; TYPE CHECKS (SYM?, NUM?, LIST?, NIL?)
(quote(TYPE CHECKS (SYM?, NUM?, LIST?, NIL?)))
(quote (if (eq (SYM? 'a) #T) #T nil Expected Result: true))
(if (eq (SYM? 'a) #T) #T nil)

(quote (if (eq (SYM? 5) nil) #T nil Expected Result: true))
(if (eq (SYM? 5) nil) #T nil)

(quote (if (eq (NUM? 5) #T) #T nil Expected Result: true))
(if (eq (NUM? 5) #T) #T nil)

(quote (if (eq (NUM? 'a) nil) #T nil Expected Result: true))
(if (eq (NUM? 'a) nil) #T nil)

(quote (if (eq (LIST? (cons 1 nil)) #T) #T nil Expected Result: true))
(if (eq (LIST? (cons 1 nil)) #T) #T nil)

(quote (if (eq (LIST? 10) nil) #T nil Expected Result: true))
(if (eq (LIST? 10) nil) #T nil)

(quote (if (eq (NIL? nil) #T) #T nil Expected Result: true))
(if (eq (NIL? nil) #T) #T nil)

(quote (if (eq (NIL? 0) nil) #T nil Expected Result: true))
(if (eq (NIL? 0) nil) #T nil)

;; USER DEFINED FUNCTIONS
(quote(USER DEFINED FUNCTIONS))
(defun add (a b) (+ a b)) ; No output
(quote (if (eq (add 2 3) 5) #T nil Expected Result: true))
(if (eq (add 2 3) 5) #T nil)

(defun mul (x y) (* x y)) ; No output
(quote (if (eq (mul 4 5) 20) #T nil Expected Result: true))
(if (eq (mul 4 5) 20) #T nil)

(defun square (x) (mul x x)) ; No output
(quote (if (eq (square 4) 16) #T nil Expected Result: true))
(if (eq (square 4) 16) #T nil)

(defun abs (x) (if (lt x 0) (- x) x)) ; No output             
(quote (if (eq (abs 10) 10) #T nil Expected Result: true))
(if (eq (abs 10) 10) #T nil)

(quote (if (eq (abs -5) 5) #T nil Expected Result: true))
(if (eq (abs -5) 5) #T nil)


;; QUOTING
(quote(QUOTING))
(quote (if (eq (quote (1 2 3)) (cons 1 (cons 2 (cons 3 nil)))) #T nil Expected Result: true))
(if (eq (quote (1 2 3)) (cons 1 (cons 2 (cons 3 nil)))) #T nil)

(quote (if (eq (quote a) a) #T nil Expected Result: true))
(if (eq (quote a) a) #T nil)

(quote (if (eq (quote (add 1 2)) (quote (add 1 2))) #T nil Expected Result: true))
(if (eq (quote (add 1 2)) (quote (add 1 2))) #T nil)

;; EVALUATING
(quote(EVALUATING))
(quote (if (eq (eval (quote (+ 1 2))) 3) #T nil Expected Result: true))
(if (eq (eval (quote (+ 1 2))) 3) #T nil)

(quote (if (eq (eval (quote (mul 3 4))) 12) #T nil Expected Result: true))
(if (eq (eval (quote (mul 3 4))) 12) #T nil)

(defun evalAdd (x y) (eval (quote (+ x y)))) ; No output
(quote (if (eq (evalAdd 5 7) 12) #T nil Expected Result: true))
(if (eq (evalAdd 5 7) 12) #T nil)

;; COMBINATIONS (SET, EVAL, QUOTE)
(quote(COMBINATIONS (SET, EVAL, QUOTE)))
(set x 10) ; No output
(quote (if (eq (eval (quote (+ x 5))) 15) #T nil Expected Result: true))
(if (eq (eval (quote (+ x 5))) 15) #T nil)

(defun calculate (a b) (eval (quote (+ a b)))) ; No output
(quote (if (eq (calculate 20 30) 50) #T nil Expected Result: true))
(if (eq (calculate 20 30) 50) #T nil)


;; USER DEFINED FUNCTIONS USING COND AND LOGICAL OPERATIONS
(quote(USER DEFINED FUNCTIONS USING COND AND LOGICAL OPERATIONS))

;; Test cases for the `max` function
(defun max (a b) (cond ((gt a b) a) (#T b))) ; No output

(quote (if (eq (max 10 20) 20) #T nil Expected Result: true))
(if (eq (max 10 20) 20) #T nil)

(quote (if (eq (max 15 5) 15) #T nil Expected Result: true))
(if (eq (max 15 5) 15) #T nil)

;; Test cases for the `min` function
(defun min (a b) (if (lt a b) a b)) ; No output

(quote (if (eq (min 3 7) 3) #T nil Expected Result: true))
(if (eq (min 3 7) 3) #T nil)

(quote (if (eq (min 10 5) 5) #T nil Expected Result: true))
(if (eq (min 10 5) 5) #T nil)

;; Test cases for the `logicalTest` function
(defun logicalTest (x y) (and (gt x 0) (lt y 10))) ; No output

(quote (if (eq (logicalTest 5 9) #T) #T nil Expected Result: true))
(if (eq (logicalTest 5 9) #T) #T nil)

(quote (if (eq (logicalTest 0 9) nil) #T nil Expected Result: true))
(if (eq (logicalTest 0 9) nil) #T nil)