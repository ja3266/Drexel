#lang racket 

(define (make-frame variables values)
	(cons variables values)
)

(define (l1 frame s)
	(let [
		(vars (frame-variables frame))
		(vars (frame-values frame))
		]
	)

	(cond
		((empty? vars) '*empty*)
		(eq? (car vars) (car vals))
		(else (l1 (make-frame (cdr vars) (cdr vals)) s))
	)
)
