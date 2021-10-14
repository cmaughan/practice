(import spork/misc :as spork)

(defn read-numbers
  ``Read line separated from `f`.``
  [f]
  (def res @[])
  (loop [line :iterate (file/read f :line)]
    (if-let [n (scan-number (string/trimr line))]
      (array/push res n)
      (error "not a number")))
  res)

(defn bsearch
  ``Find the first value in `ind` that satisfies `pred` using binary search.``
  [pred ind]
  (var l 0)
  (var r (- (length ind) 1))
  (var res nil)
  (while (and (<= l r) (nil? res))
    (let [m (math/floor (/ (+ l r) 2))
          n (in ind m)
          c (pred n)]
      (cond (> c 0) (set l (+ m 1))
        (< c 0) (set r (- m 1))
        (set res n))))
  res)

(def test
  (->>
    ```
    1721
    979
    366
    299
    675
    1456
    ``` 
    spork/dedent
    string/trim
    (string/split "\n")
    (map scan-number)))

(def puzzle (read-numbers (file/open "d:/dev/practice/janet/advent_of_code/2020/day1.txt")))

(defn part-1 [input]
  (var x nil)
  (each i input
    (each ii input
      (when (= (+ i ii) 2020)
        (set x (*  i ii)))))
  x)

(defn part-1-loop [input]
  (var x nil)
  (loop [i :in input :until x]
    (loop [ii :in input :until x]
      (when (= (+ i ii) 2020)
        (set x (* ii i)))))
  x)

(defn part-1-sequence [input]
  (first (seq [i :in input
        ii :in input
        :when (= 2020 (+ i ii))]
    (* i ii))))

(defn part-1-sequence-ignore-same [input]
  (seq [[itrA i] :pairs input
        [itrB ii] :pairs input
        :when (= 2020 (+ i ii))
        :when (not= itrA itrB)]
    (* i ii)))

(defn part-1-search [input]
  (let [input (sorted input)]
    (var x nil)
    (loop [i :in input :until x]
      (if-let [j (bsearch (fn [x] (- 2020 (+ i x))) input)]
        (set x (* i j))))
    x))

(defn part-1-search-short [input]
  (let [input (sorted input)]
    (var x nil)
    (loop [i :in input :until x]
      (if-let [j (bsearch |(- 2020 (+ i $)) input)]
        (set x (* i j))))
    x))


(print (part-1 test))

(print (part-1 puzzle))
(print (part-1-loop puzzle))
(print (part-1-search puzzle))
(print (part-1-search-short puzzle))
(print (part-1-sequence puzzle))
(print (part-1-sequence-ignore-same puzzle))
