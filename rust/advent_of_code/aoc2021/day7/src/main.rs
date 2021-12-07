use itertools::Itertools;

fn part1(vals : &[i64]) -> i64 {
    let c = vals[vals.len() / 2];
    vals.iter().map(|&v| (v - c).abs()).sum()
}

fn part2(vals : &[i64]) -> i64 {
    let align = vals.iter().sum::<i64>() / vals.len() as i64;
    (align-1..align+1).map(|c| {
        vals.iter().map(|&v| {
            let d = (v-c).abs();
            (d * (d + 1)) / 2
        }).sum()}).min().unwrap()
}

pub fn main() {
    let input = include_str!("../input.txt")
        .trim()
        .split(',')
        .map(|v| v.parse().unwrap())
        .sorted()
        .collect::<Vec<_>>();

    println!("Part1: {}", part1(&input));
    println!("Part2: {}", part2(&input));
}
