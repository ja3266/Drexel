#lang racket

(require "stream-apply.rkt")

(stream->list (stream-take (stream-apply (lambda (x) (+ x 1)) 0) 10))

