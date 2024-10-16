#lang racket

(define (stream-enumerate-interval low high)
	(if (> low high)
		empty-stream
		(stream-cons low (stream-enumerate-interval (+ low 1) high))
	)
)

(define (list-interval s low high)
	(if (stream-empty? s)
		'()
		(cons (first (stream-enumerate-interval (rest s) low high))) 
	)
)

(define stream s)

(list-interval s 0 9)
