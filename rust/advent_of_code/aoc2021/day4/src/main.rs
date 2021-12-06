use std::collections::hash_set::HashSet;
use itermore::IterMore;

fn part1() -> u32 {
    3
}

fn part2() -> u32 {
    3
}
#[derive(Debug)]
struct board {
   numbers: HashSet<u32>,
   rows: [u32; 5],
   columns: [HashSet<u32>; 5]
}
impl board {
    fn new(vals: Vec<u32>) -> board {
        let mut h = HashSet::new();
        let mut rows = [HashSet<u32>;5];
        let mut columns: [HashSet<u32>;5];
        for v in vals {
           h.insert(v) ;
        }

        board {
            numbers: h
        }
    }
}
pub fn main() {
    let input = include_str!("../input.txt");
    let nums: Vec<u32> = input.lines().next().unwrap().split(',').map(|v| { v.parse().unwrap() })
        .collect();
    let mut vals = Vec::new();
    for l in input.lines().skip(1) {
        for v in l.split_ascii_whitespace() {
            vals.push(v.parse::<u32>().unwrap());
        }
    }

    let mut boards = Vec::new();
    for chunk in vals.chunks(25) {
        boards.push(board::new(chunk.to_vec()));
    }
    println!("t: {:#?}", boards);
    println!("day3_p1 {}", part1());
    println!("day3_p2 {}", part2());
}
