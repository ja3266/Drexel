#lang racket

; stream-iter -- return a stream (a (a+1) ... b)
;
; NOTES:
; - EDITOR:  tabstop=2 cols=120
;

(provide (all-defined-out))

	;; stream-iter - returns a finite stream (a..b)
	;; if a third argument is supplied, use it as the step
(define (stream-iter b e . rargs)
	(let  (
					[step (if (null? rargs) 1 (first rargs))]
				)
		(if (> b e)
			empty-stream
			(stream-cons b (stream-iter (+ b step) e step)))))

	;; stream-iter-inf - returns an infinite stream (a...)
	;; if a second argument is supplied, use it as the step
(define (stream-iter-inf b . rargs)
	(let  (
					[step (if (null? rargs) 1 (first rargs))]
				)
		(stream-cons b (stream-iter-inf (+ b step) step))))


(define S (stream-iter 12 23))  ; (12 13 14 ... 23)
(define T (stream-iter 8 33 3))  ; (8 11 14 ... 32)
(define IS (stream-iter-inf 42 5))  ; (42 47 52 57 ...)


; (stream-first S)
; (stream-first (stream-rest S))
; (stream->list S)  ; See all of (finite) stream S

; (stream-ref S 0)  ; get the 0th element
; (stream-ref S 5)  ; get the 6th element

; (stream->list (stream-take IS 5))  ; first 5 elements of a (possibly infinite) stream

