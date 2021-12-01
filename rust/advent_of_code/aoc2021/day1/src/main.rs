use itertools::Itertools;
use itermore::IterMore;

fn part1() -> usize {
    include_str!("../input.txt")
        .split_ascii_whitespace()
        .map(|i| i.parse::<i32>().unwrap())
        .windows()
        .filter(|[a,b]| (a < b))
        .count()
}

fn part2() -> usize {
    include_str!("../input.txt")
        .split_ascii_whitespace()
        .map(|i| i.parse::<i32>().unwrap())
        .tuple_windows()
        .filter(|(first, _, _, last)| first < last)
        .count()
}

fn part1and2<const N: usize>() -> usize {
    include_str!("../input.txt")
        .split_ascii_whitespace()
        .map(|i| i.parse().unwrap())
        .windows()
        .filter(|a:&[i32;N]| (a.last() > a.first()))
        .count()
}

pub fn main() {
    println!("day1_p1 {}", part1and2::<2>());
    println!("day1_p2 {}", part1and2::<4>());
}
