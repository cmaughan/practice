use itertools::Itertools;

fn part1() -> i32 {
    let ret = include_str!("../input.txt")
        .split_ascii_whitespace()
        .tuples()
        .fold((0, 0), |acc, (d, v)| {
            let inc = v.parse::<i32>().unwrap();
            match d {
                "forward" => (acc.0 + inc, acc.1),
                "down" => (acc.0, acc.1 + inc),
                "up" => (acc.0, acc.1 - inc),
                _ => panic!("Unexpected")
            }
        });
    return ret.0 * ret.1;
}

fn part2() -> i64 {
    let ret = include_str!("../input.txt")
        .split_ascii_whitespace()
        .tuples()
        .fold((0, 0, 0), |acc, (d, v)| {
            let inc = v.parse::<i64>().unwrap();
            match d {
                // aim, horz, depth
                "forward" => (acc.0, acc.1 + inc, acc.2 + acc.0 * inc),
                "down" => (acc.0 + inc, acc.1, acc.2),
                "up" => (acc.0 - inc, acc.1, acc.2),
                _ => panic!("Unexpected")
            }
        });
    return ret.1 * ret.2;
}

pub fn main() {
    println!("day2_p1 {}", part1());
    println!("day2_p2 {}", part2());
}
