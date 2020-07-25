; TASK 1
(write ((lambda (a b c)
  (CONS a (CONS b (CONS c NIL))))
  (CAR '(H G (U J) (T R))) (CAR '(2 1 (+ 4 5))) (CAR '(TYPE CHAR REAL (H G))))
)

; TASK 2
(DEFUN COMBINE (a b c)
  (CONS (THIRD a) (CONS (NTH 2 b) (CONS (THIRD c) NIL)))
)

(write
  (COMBINE '(H G (U J) (T R)) '(2 1 (+ 4 5)) '(TYPE CHAR REAL (H G)))
)

; TASK 3
(DEFUN MIX (a b)
  (LIST
    (CONS (FIRST a) (CONS (THIRD b) NIL))
    (CONS (SECOND b) (CONS (FIRST (LAST a)) NIL))
  )
)

(write
  (MIX '(A B C) '(1 2 3 4 5))
)
