#lang racket

(define (my-iter b e)
	(if (> b e) 
		'()
		(cons b (my-iter (+ b 1) e))
		)
	)

(define (finite-str b e)
	(if (> b e) 
		empty-stream
		(stream-cons b (finite-str (+ b 1) e))
		)
	)

(define (infinite-str b)
		(stream-cons b (infinite-str (+ b 1)))
	)

(define (my-stream-filter pred? S)
	(if (stream-empty? S)
		empty-stream
		(if (pred? (stream-first S))
			(stream-cons (stream-first S) (my-stream-filter pred? (stream-rest S)))
			(my-stream-filter pred? (stream-rest S))
		)
	)
)

(define (my-stream-remove pred? S)
	(if (stream-empty? S)
		empty-stream
		(if (pred? (stream-first S))
			(my-stream-remove pred? (stream-rest S))
			(stream-cons (stream-first S) (my-stream-remove pred? (stream-rest S)))
		)
	)
)

(define (my-stream-map proc S)
	(if (stream-empty? S)
		empty-stream
		(stream-cons (proc (stream-first S)) (my-stream-map proc (stream-rest S)))
		)
	)
	
(define (sq n)
	(* n n)
	)

(define S (finite-str 17 37))
(stream? S)
(stream->list (my-stream-map sq S))
