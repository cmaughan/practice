use itertools::Itertools;
use std::time::{Instant};

fn day1(display: bool) {
    let vals : Vec<i32> = include_str!("inputs/1.txt")
        .trim()
        .split("\n\n")
        .map(|elf| {
            elf.lines().map(|val| {
                val.parse::<i32>().unwrap_or(0)
            }).sum()
        })
        .sorted()
        .rev()
        .collect();

    if display {
        println!("Day1, Part1: {}", vals[0]);
        println!("Day1, Part2: {}", vals[0] + vals[1] + vals[2]);
    }
}

fn main() {
    let start = Instant::now();

    for _ in 1..100 {
        day1(false);
    }
    day1(true);

    let duration = start.elapsed() / 101;
    println!("Time elapsed: {:?}", duration);
}
