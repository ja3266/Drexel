#lang racket

(require "apply-count.rkt")

(apply-count (lambda (x) (* x x)) 5)
(apply-count (lambda (x) x) 100)
(apply-count (lambda (x) x) 100)
