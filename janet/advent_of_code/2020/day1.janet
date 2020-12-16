(defn read-numbers
  ``Read line separated from `f`.``
  [f]
  (def res @[])
  (loop [line :iterate (file/read f :line)]
    (if-let [n (scan-number (string/trimr line))]
      (array/push res n)
      (error "not a number")))
  res)

(let [input (read-numbers (file/open "d:/dev/practice/janet/advent_of_code/2020/day1.txt"))] 
  (var ret nil)
  (loop [x :in input :until ret]
    (loop [y :in input :until ret]
      (when (and (= (+ x y) 2020) (not= x y))
        (print (* x y))))))


(let [input (read-numbers (file/open "d:/dev/practice/janet/advent_of_code/2020/day1.txt"))] 
  (seq [x :in input
               y :in input
                 :when (= 2020 (+ x y))]
           (do (print x) (print y) (* x y))))

