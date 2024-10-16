#lang racket

(provide (all-defined-out))

(define (stream-zip S T)
	(if (or (stream-empty? S) (stream-empty? T))
		empty-stream
		(stream-cons (cons (stream-first S) (stream-first T)) (stream-zip (stream-rest S) (stream-rest T)))
	)
)
