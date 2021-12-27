use std::collections::HashMap;
use itertools::Itertools;
use std::io::Write;

#[allow(dead_code)]
fn slow(rules: &HashMap<(char, char), char>,
        count: usize,
        txt: &str) -> usize {

    let mut t = txt.clone().to_string();
    for x in 0..count {
        println!("Step..{}", x);
        std::io::stdout().flush().unwrap();
        let last = t.chars().last().unwrap();
        t = t.chars().tuple_windows::<(char, char)>().fold(String::new(), |mut acc, (a, b)| {
            acc.push(a);
            acc.push(rules[&(a, b)]);
            acc
        });
        t.push(last);
    }
    let c = t.chars().counts();
    let ret = c.values().minmax().into_option().unwrap();
    ret.1 - ret.0
}

fn fast(letters: &HashMap<(char, char), usize>,
         rules: &HashMap<(char, char), char>,
         count: usize,
         txt: &str) -> usize {
    let mut init = letters.clone();
    for _ in 0..count {
        let mut counts= HashMap::new();
        for (key, c) in init.iter() {
            // Make the 2 new pairs
            let v = rules[key];
            *counts.entry((key.0, v)).or_insert(0) += c;
            *counts.entry((v, key.1)).or_insert(0) += c;
        }
        init = counts;
    }

    let mut count_map = init.iter().fold(HashMap::new(), |mut acc, ((a, _), c)| {
        *acc.entry(a).or_insert(0) += c;
        acc
    });
    let last = txt.chars().last().unwrap();
    *count_map.entry(&last).or_insert(0) += 1;

    let ret = count_map.values().minmax().into_option().unwrap();
    return ret.1 - ret.0
}

pub fn main() {
    let d = include_str!("../input.txt").split_once("\n\n").unwrap();

    let letters: HashMap<(char, char), usize> = d.0.chars().tuple_windows().counts();

    let rules = d.1.lines()
        .flat_map(|l| l.split_once(" -> "))
        .map(|(a, b)| {
            ((a.as_bytes()[0] as char, a.as_bytes()[1] as char), b.as_bytes()[0] as char)}
        )
        .collect::<HashMap<(char, char), char>>();

    println!("Part1: {}", fast(&letters, &rules, 10, &d.0));
    println!("Part2: {}", fast(&letters, &rules, 40, &d.0));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_day() {
    }
}
