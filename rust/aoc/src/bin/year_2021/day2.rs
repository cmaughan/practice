use itertools::Itertools;

pub fn part1(input: &str) -> i32 {
    let ret = input
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

pub fn part2(input: &str) -> i64 {
    let ret = input
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
