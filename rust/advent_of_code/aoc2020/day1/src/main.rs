use itertools::Itertools;

fn part1and2(combinations : usize) -> usize {
    include_str!("../input.txt")
        .lines()
        .map(|i| i.parse::<usize>().unwrap())
        .combinations(combinations)
        .filter(|a| a.iter().sum::<usize>() == 2020)
        .map(|a| a.iter().product())
        .next().unwrap()
}

pub fn main() {
    println!("day1_p1 {}", part1and2(2));
    println!("day1_p2 {}", part1and2(3));
}
