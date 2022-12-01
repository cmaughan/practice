use itertools::Itertools;

fn main() {
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

    println!("Day1, Part1: {}", vals[0]);
    println!("Day1, Part2: {}", vals[0] + vals[1] + vals[2]);
}
