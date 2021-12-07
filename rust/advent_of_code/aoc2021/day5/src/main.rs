use lazy_static::lazy_static;
use std::collections::hash_map::HashMap;
use regex::Regex;

fn solve(vals: &Vec<(i32, i32, i32, i32)>, diag: bool) -> usize {
    let mut m = HashMap::new();
    for (x1, y1, x2, y2) in vals {
        if !diag && !(x1 == x2 || y1 == y2) {
            continue;
        }

        let (mut x, mut y) = (*x1, *y1);
        let (x_inc, y_inc) = ((x2 - x1).signum(), (y2 - y1).signum());
        loop {
            *m.entry((x, y)).or_insert(0) += 1;
            x += x_inc;
            y += y_inc;
            if x == (x2 + x_inc) && y == (y2 + y_inc) {
                break;
            }
        }
    }
    m.values().filter(|&&v| v > 1).count()
}

lazy_static! {
    static ref RE : Regex = Regex::new(r"(\d+),(\d+) -> (\d+),(\d+)").unwrap();
}
pub fn main() {
    let input = include_str!("../input.txt");

     let vals = RE.captures_iter(input)
         .map(|x| (x[1].parse().unwrap(), x[2].parse().unwrap(), x[3].parse().unwrap(), x[4].parse()
             .unwrap()))
         .collect();
    /*let vals = input.split_ascii_whitespace()
        .filter(|l| *l != "->")
        .map(|s| s.split(','))
        .flatten()
        .map(|i| i.parse::<i32>().unwrap())
        .collect::<Vec<_>>()
        .chunks(4)
        .map(|v| (v[0], v[1], v[2], v[3]))
        .collect();
     */

    println!("Part1: {}", solve(&vals, false));
    println!("Part2: {}", solve(&vals, true));
}
