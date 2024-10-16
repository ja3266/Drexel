#lang racket

(require "stream-pair.rkt")
(require "stream-iter.rkt")

(define S (stream-iter 0 9))

(stream->list (stream-pair-with sqr (stream 1 2 3 4)))
