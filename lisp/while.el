
(setq x 0)
(while (< x 10)
  (print (format "x: %d" x))
  (setq x (+ x 1)))

(let ((y 32))
  (while (< y 127)
    (ucs-insert y)
    (setq y (+ y 2))
    ))
