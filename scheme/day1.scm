(define (readlines filename)
  (call-with-input-file filename
                        (lambda (p)
                          (let loop ((line (read-line p))
                                     (result '()))
                            (if (eof-object? line)
                              (reverse result)
                              loop (read-line p) (cons (string->number line) result)))))))

(display (string-append "Part1: " (number->string (apply + (readlines "day_1.txt"))) "\n"))
