use itermore::Itermore;
use itertools::Itertools;

pub fn part1(input: &str) -> usize {
    input
        .split_ascii_whitespace()
        .map(|i| i.parse::<i32>().unwrap())
        .array_windows()
        .filter(|[a,b]| (a < b))
        .count()
}

pub fn part2(input: &str) -> usize {
    input
        .split_ascii_whitespace()
        .map(|i| i.parse::<i32>().unwrap())
        .tuple_windows()
        .filter(|(first, _, _, last)| first < last)
        .count()
}

fn part1and2<const N: usize>(input: &str) -> usize {
    input
        .split_ascii_whitespace()
        .map(|i| i.parse().unwrap())
        .array_windows()
        .filter(|a:&[i32;N]| (a.last() > a.first()))
        .count()
}

pub fn part1_generic(input: &str) -> usize {
    part1and2::<2>(input)
}
pub fn part2_generic(input: &str) -> usize {
    part1and2::<4>(input)
}
