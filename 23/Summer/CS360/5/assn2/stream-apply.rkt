#lang racket

(provide (all-defined-out))

(define (stream-apply f x)
	(stream-cons  x (stream-apply f(f x)))
)
