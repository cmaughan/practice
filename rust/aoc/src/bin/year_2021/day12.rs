use std::collections::HashMap;

pub fn seek<'a>(caves: &HashMap<&str, Vec<&'a str>>, path : &mut Vec<&'a str>, entry: &str,
                small_count: i32)
                -> usize {
    caves[entry].iter()
        .map(|&s| {
            if s == "end" {
                return 1;
            }

            let mut count = 0;
            if s.to_lowercase() == s {
                if s == "start" {
                    return 0;
                }
                count = path.iter().filter(|&&comp| s == comp).count() as i32;
                if count > small_count {
                    return 0;
                }
            };

            path.push(s);
            let ret = seek(&caves, path, s, small_count - count);
            path.pop();
            ret
        }).sum()
}

pub fn part1(d:  &HashMap<&str, Vec<&str>>) -> usize {
    seek(&d, &mut Vec::new(), "start", 0)
}

pub fn part2(d: &HashMap<&str, Vec<&str>>) -> usize {
    seek(&d, &mut Vec::new(), "start", 1)
}

pub fn generator(input: &str) -> HashMap<&str, Vec<&str>> {
    input.lines()
        .fold(HashMap::new(), |mut acc, l| {
            let (left, right) = l.split_once("-").unwrap();
            acc.entry(left).or_insert(Vec::new()).push(right);
            acc.entry(right).or_insert(Vec::new()).push(left);
            acc
        })

}

