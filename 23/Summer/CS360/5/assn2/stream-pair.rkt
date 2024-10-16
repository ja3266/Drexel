#lang racket

(provide (all-defined-out))

(define (stream-pair-with f S)
	(if (stream-empty? S)
		empty-stream
		(stream-cons (cons (stream-first S) (f(stream-first S))) (stream-pair-with f (stream-rest S)))
	)
)
