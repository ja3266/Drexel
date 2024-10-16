#lang racket

(require "stream-zip.rkt")

(define (infinite-str b)
	(stream-cons b (infinite-str (+ b 1))))

(define S (infinite-str 1))

(define T (infinite-str 5))



(stream->list (stream-take (stream-zip S T) 10))
