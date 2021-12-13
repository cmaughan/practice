use std::collections::HashMap;

fn part1((_,b): &(Vec<&str>, Vec<&str>)) -> usize {
    b.iter().filter(|x| [2,3,4,7].contains(&x.len())).count()
}

fn part2((ins, outs): &(Vec<&str>, Vec<&str>)) -> usize {
    // Match the known
    let h = ins.iter().fold(HashMap::new(), |mut h, s| {
        match s.len() {
            2 => h.insert(1, s),
            3 => h.insert(3, s),
            4 => h.insert(4, s),
            7 => h.insert(8, s),
            _ => None
        };
        h
    });

    // Walk the outputs and find their values based on what we know
    let res = outs.iter().map(|&s| {
        let common_one = h[&1].chars().fold(0, |acc, c| if s.contains(c) { acc + 1 }
        else { acc });
        let common_four = h[&4].chars().fold(0, |acc, c| if s.contains(c) { acc + 1 }
        else { acc });

        match (s.len(), common_one, common_four) {
            (2,2,2) => 1,
            (5,1,2) => 2,
            (5,2,3) => 3,
            (4,2,4) => 4,
            (5,1,3) => 5,
            (6,1,3) => 6,
            (3,2,2) => 7,
            (7,2,4) => 8,
            (6,2,4) => 9,
            (6,2,3) => 0,
            (_,_,_) => 0
        }
    }).collect::<Vec<usize>>(); // row result
    res[0] * 1000 + res[1] * 100 + res[2] * 10 + res[3]
}

pub fn main() {
    let data = include_str!("../input.txt")
        .lines()
        .map(|l| {
            let (inputs, outputs) = l.split_once("|").unwrap();
            let ins = inputs.split_ascii_whitespace().collect();
            let outs = outputs.split_ascii_whitespace().collect();
            (ins, outs)
        }).collect::<Vec<_>>();

    println!("Part1: {}", data.iter().map(part1).sum::<usize>());
    println!("Part2: {}", data.iter().map(part2).sum::<usize>());
}

