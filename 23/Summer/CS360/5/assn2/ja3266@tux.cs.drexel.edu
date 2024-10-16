#lang racket

(provide (all-defined-out))

(define apply-count 
	(let ([i 0])
		(lambda (f x)
			(set! i (+ i 1))
			(cons (f x) i)
		)
	)
)

