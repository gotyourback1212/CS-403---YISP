;;ARITHETIC OPERATIONS 
(quote(ARITHETIC OPERATIONS))
(if (eq (+ 1 2) 3) #T nil)                  ; Expected Result: true
(if (eq (- 5 3) 2) #T nil)                  ; Expected Result: true
(if (eq (* 4 3) 12) #T nil)                 ; Expected Result: true
(if (eq (/ 10 2) 5) #T nil)                 ; Expected Result: true
(if (eq (% 10 3) 1) #T nil)                 ; Expected Result: true
(if (eq (+ 1 2 3 4) 10) #T nil)             ; Expected Result: true


;;COMPARISIONS OPERATIONS
(quote(COMPARISIONS OPERATIONS))
(if (eq (gt 10 5) #T) #T nil)               ; Expected Result: true
(if (eq (lt 5 10) #T) #T nil)               ; Expected Result: true
(if (eq (eq 5 5) #T) #T nil)                ; Expected Result: true
(if (eq (eq 5 6) nil) #T nil)               ; Expected Result: true ;;Fault
(if (eq (gte 10 10) #T) #T nil)             ; Expected Result: true
(if (eq (lte 7 8) #T) #T nil)               ; Expected Result: true
(if (eq (lte 8 8) #T) #T nil)               ; Expected Result: true


;;LOGICAL OPERATIONS
(quote(LOGICAL OPERATIONS))
(if (eq (and #T #T) #T) #T nil)             ; Expected Result: true
(if (eq (and #T nil) nil) #T nil)           ; Expected Result: true ;;Fault
(if (eq (or #T nil) #T) #T nil)             ; Expected Result: true
(if (eq (or nil nil) nil) #T nil)           ; Expected Result: true ;;Fault
(if (eq (not #T) nil) #T nil)               ; Expected Result: true ;;Fault 
(if (eq (not nil) #T) #T nil)               ; Expected Result: true


;;CONDITONALS 
(quote(CONDITONALS))
(if (eq (if (gt 10 5) (1) 0) 1) #T nil)     ; Expected Result: true
(if (eq (if (lt 3 2) 1 0) 0) #T nil)        ; Expected Result: true
(if (eq (if #T 42 99) 42) #T nil)           ; Expected Result: true
(if (eq (if nil 42 99) 99) #T nil)          ; Expected Result: true


;;COND
(quote(COND))
(if (eq (cond ((gt 10 5) 1) ((lt 3 2) 0)) 1) #T nil)  ; Expected Result: true
(if (eq (cond ((lt 0 0) 1) ((#T) 100)) 100) #T nil)   ; Expected Result: true ;;Fault
(if (eq (cond ((eq 2 2) 10) ((#T) 20)) 10) #T nil)    ; Expected Result: true


;;LIST OPERATIONS (CONS, CAR, CDR)
(quote(LIST OPERATIONS (CONS, CAR, CDR)))
(set x (cons 1 (cons 2 (cons 3 (cons 4 ())))))                       ; No Oupt 
(eq (cons 2 (cons 3 (cons 4 ()))) (cdr x))                           ; Exprect ResultL true 
(if (eq (cons 1 nil) (cons 1 nil)) #T nil)                           ; Expected Result: true 
(if (eq (cons 1 (cons 2 nil)) (const 1 (cons 2 nil))) #T nil)        ; Expected Result: true 
(if (eq (car (cons 1 (cons 2 nil))) (cons 1 (cons 2 nil))) #T nil)   ; Expected Result: true  
(if (eq (cdr (cons 1 (cons 2 nil))) (cons 2 nil)) #T nil)            ; Expected Result: true 
(if (eq (car (cdr (cons 1 (cons 2 (cons 3 nil))))) 2) #T nil)        ; Expected Result: true


;;TYPE CHECKS (SYM?, NUM?, LIST?, NIL?)
(quote(TYPE CHECKS (SYM?, NUM?, LIST?, NIL?)))
(if (eq (SYM? 'a) #T) #T nil)               ; Expected Result: true
(if (eq (SYM? 5) nil) #T nil)               ; Expected Result: true ;;Fault 
(if (eq (NUM? 5) #T) #T nil)                ; Expected Result: true
(if (eq (NUM? 'a) nil) #T nil)              ; Expected Result: true ;;Fault 
(if (eq (LIST? (cons 1 nil)) #T) #T nil)    ; Expected Result: true
(if (eq (LIST? 10) nil) #T nil)             ; Expected Result: true ;;Fault 
(if (eq (NIL? nil) #T) #T nil)              ; Expected Result: true 
(if (eq (NIL? 0) nil) #T nil)               ; Expected Result: true ;;Fault


;;USER DEFINED FUNCTIONS
(quote(USER DEFINED FUNCTIONS))
(defun add (a b) (+ a b))                   ; No output
(if (eq (add 2 3) 5) #T nil)                ; Expected Result: true

(defun mul (x y) (* x y))                   ; No output
(if (eq (mul 4 5) 20) #T nil)               ; Expected Result: true

(defun square (x) (mul x x))                ; No output
(if (eq (square 4) 16) #T nil)              ; Expected Result: true

(defun abs (x) (if (lt x 0) (x) x))       ; No output             
(if (eq (abs 10) 10) #T nil)               ; Expected Result: true  
(if (eq (abs 5) 5) #T nil)                  ; Expected Result: true 

(defun sign (x) (cond ((gt x 0) 1) ((lt x 0) -1) (#T 0))) ; No output
(if (eq (sign -5) -1) #T nil)               ; Expected Result: true
(if (eq (sign 0) 0) #T nil)                 ; Expected Result: true
(if (eq (sign 10) 1) #T nil)                ; Expected Result: true


;;QUOTING
(quote(QUOTING))
(if (eq (quote (1 2 3)) (1 2 3)) #T nil)    ; Expected Result: true
(if (eq (quote a) a) #T nil)                ; Expected Result: true
(if (eq (quote (add 1 2)) (quote (add 1 2))) #T nil); Expected Result: true


;;EVALUATING 
(quote(EVALUATING))
(if (eq (eval (quote (+ 1 2))) 3) #T nil)   ; Expected Result: true
(if (eq (eval (quote (mul 3 4))) 12) #T nil); Expected Result: true

(defun evalAdd (x y) (eval (quote (+ x y)))) ; No output
(if (eq (evalAdd 5 7) 12) #T nil)           ; Expected Result: true

;;COMBINATIONS (SET, EVAL, QUOTE)
(set x 10)                                  ; No output
(if (eq (eval (quote (+ x 5))) 15) #T nil)  ; Expected Result: true

(defun calculate (a b) (eval (quote (+ a b)))) ; No output
(if (eq (calculate 20 30) 50) #T nil)       ; Expected Result: true


;;USER DEFINED FUNCTIONS USING COND and LOGICAL OPERATIONS
(quote(USER DEFINED FUNCTIONS USING COND and LOGICAL OPERATIONS))
(defun max (a b) (cond ((gt a b) a) (#T b))) ; No output
(if (eq (max 10 20) 20) #T nil)             ; Expected Result: true
(if (eq (max 15 5) 15) #T nil)              ; Expected Result: true

(defun min (a b) (if (lt a b) a b))         ; No output
(if (eq (min 3 7) 3) #T nil)                ; Expected Result: true
(if (eq (min 10 5) 5) #T nil)               ; Expected Result: true

(defun logicalTest (x y) (and (gt x 0) (lt y 10))) ; No output
(if (eq (logicalTest 5 9) #T) #T nil)       ; Expected Result: true
(if (eq (logicalTest 0 9) nil) #T nil)      ; Expected Result: true ;;Error