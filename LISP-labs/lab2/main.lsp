; TASK 1
(defun atomicity (lst n)
  (cond ((null lst) nil)
        ((and (atom (car lst)) (eq n '0)) (car lst))
        ((not (atom (car lst)))
          (atomicity (cdr lst) n))
        ((and (atom (car lst)) (not (eq n '0)))
          (atomicity (cdr lst) (- n 1)))))

(print (atomicity '((2) (3) 4 5 a (e r) g) '2))

; TASK 4
(defun mergeo (l1 l2)
  (cond ((null l1) l2)
        ((null l2) l1)
        ((> (car l1) (car l2)) (cons (car l2) (mergeo l1 (cdr l2))))
        (T (cons (car l1) (mergeo (cdr l1) l2)))))

(print (mergeo '(5 6 7) '(4 7 8 9 10 11)))
; (print (mergeo '(7 8 9) '(1 2 3)))

; QuickSort
(defun quicksort (l)
  (cond
    ((null l) nil)
    (T
      (append
        (quicksort (list< (car l) (cdr l)))
        (list (car l))
        (quicksort (list>= (car l) (cdr l)))))))

(defun list< (a b)
  (cond
    ((or (null a) (null b)) nil)
    ((< a (car b)) (list< a (cdr b)))
    (T (cons (car b) (list< a (cdr b))))))

(defun list>= (a b)
  (cond
    ((or (null a) (null b)) nil)
    ((>= a (car b)) (list>= a (cdr b)))
    (T (cons (car b) (list>= a (cdr b))))))

(print (quicksort '(4 2 8 3 1 7 5 6)))
; 4 2 8
; 4 - 2 8
; 2 + 4 - 8
; 4 - 8 => () - 8 => nil

; Shell Sort
(defun insertion (lst x)
  (cond ((null lst) (list x))
        ((> (car lst) x) (cons x lst))
        (T (cons (car lst) (insertion (cdr lst) x)))))

(defun isort (x &optional (s nil))
  (cond ((null x) s)
        (T (isort (cdr x) (insertion s (car x))))))

(defun shello (lst gap finalst)
  (cond ((null lst) finalst)
        (T (cond ((> gap (length lst)) (append qfinalst (isort lst)))
  (T (append finalst (isort (subseq lst 0 gap)) (shello (subseq lst gap (length lst)) gap finalst)))))))

(defun shellSort (lst gaps)
  (cond ((null (cdr gaps)) (shello lst (car gaps) '()))
        (T (shellSort (shello lst (car gaps) '()) (cdr gaps)))))

(defun gaps (len finalLIST)
  '(1 4 13 40 121 364))

(defun shellexecute (lst)
  (shellSort lst (gaps (length lst) '(1))))

(print (shellexecute '(4 2 8 3 1 7 5 6)))
; (print (shellexecute '(3 4 2 1 5 7 8 9 0 6)))
