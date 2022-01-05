use itermore::Itermore;
use itertools::Itertools;

pub fn part1(data: &Vec<u8>) -> usize {
    println!("{:#?}", data);
    0
}

pub fn part2(data: &Vec<u8>) -> usize {
    0
}

pub fn generator(input: &str) -> Vec<u8> {
    input
        .chars()
        .array_chunks()
        .map(|[a, b]| {
            ((a.to_digit(16).unwrap() << 4) | (b.to_digit(16).unwrap()))  as u8
        }).collect::<Vec<u8>>()
}
