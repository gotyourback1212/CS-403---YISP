;; Basic Arithmetic
(print "BASIC ARITHMETIC TEST")
(print (eq (+ 1 2 3) 6))
(print (eq (- 10 5 2) 3))
(print (eq (* 3 4 5) 60))
(print (eq (/ 100 5 2) 10))
(print (eq (% 10 3) 1))

;; Comparisons
(print "COMPARISIONS TEST")
(print (eq (gt 10 5) #T))
(print (eq (lt 3 7) #T))
(print (eq (gte 5 5) #T))
(print (eq (lte 3 3) #T))

;; Cons, Car, and Cdr
(print "CONS, CAR, CDR TEST")
(print (eq (cons 1 (cons 2 (cons 3 ()))) (1 2 3)))
(print (eq (car (cons 1 (cons 2 ()))) 1))
(print (eq (cdr (cons 1 (cons 2 ()))) (cons 2 ())))
(print (eq (car (cdr (cons 1 (cons 2 (cons 3 ()))))) 2))

;; Equality
(print "EQUALITY TEST")
(print (eq (eq 5 5) #T))
(print (eq (eq a a) #T))
(print (eq (eq a 5) nil))
(print (eq (eq (cons 1 ()) (cons 1 ())) nil))

;; List Operations
(print "LIST TEST")
(print (eq (LIST? (cons 1 (cons 2 ())))) #T)
(print (eq (LIST? 5) nil))

;; Negation
(print "NEGATION TEST")
(print (eq (not (gt 5 10)) #T))
(print (eq (not (NIL? ())) nil))

;; Nested Expressions
(print "NESTED TEST")
(print (eq (+ (car (cons 10 ())) (car (cdr (cons 20 (cons 30 ()))))) 40))
(print (eq (- (* (car (cons 3 ())) 10) (car (cdr (cdr (cons 1 (cons 2 (cons 5 ()))))))) 25))

;; Modulo and Division Edge Cases
(print "MOD AND DIV TEST")
(print (eq (% 100 10) 0))
(print (eq (/ (car (cons 100 ())) (car (cdr (cons 10 (cons 5 ()))))) 20))

;; Equality Edge Cases
(print "EQUALITY EDGE CASE TEST")
(print (eq (eq 0 ()) nil))
(print (eq (eq 'nil ()) nil))

;; Empty List Handling
(print "EMPTY LIST TEST")
(print (eq (LIST? ()) #T))
(print (eq (car (cons 1 ())) 1)) ;; Avoids calling car on empty list
(print (eq (cdr (cons 1 ())) ()))

;; Symbol and Number Detection
(print "SYMBOL AND NUM DECTECTION TEST")
(print (eq (SYM? a) #T))
(print (eq (SYM? 42) nil))
(print (eq (NUM? 42) #T))
(print (eq (NUM? b) nil))



(print (cdr (car (cons 1 (cons 2 (cons 3 ()))))))