#lang racket 

(define (finite-str low high)
	(if (> low high)
		empty-stream
		(stream-cons low (finite-str (+ low 1) high))
	)
)

(define s (finite-str 0 9))
(stream->list s)
