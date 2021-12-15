use itertools::Itertools;

fn solve(lines: Vec<&str>) -> (usize, usize) {
    let mut tot = 0;
    let mut results= Vec::new();
    for l in lines {
        let mut h = Vec::new();
        let score = l.chars().fold(0, |acc, c| {
            acc + match c {
                // New opening, just push
                '[' | '{' | '(' | '<' => {h.push(c); 0},
                _ => match (h.pop().unwrap(), c) {
                    // Valid Closures
                    ('(', ')') => 0,
                    ('[', ']') => 0,
                    ('{', '}') => 0,
                    ('<', '>') => 0,
                    // Invalid Closures
                    (_, ')') => 3,
                    (_, ']') => 57,
                    (_, '}') => 1197,
                    (_, '>') => 25137,
                    _ => panic!(),
                }
            }
        });

        tot += score;

        // Invalid line so not part of the fixed lines
        if score != 0 {
            continue;
        }

        // Fix up the line, remember the result
        results.push(h.iter().rev().fold(0, |acc, c| {
            match c {
                '(' => acc * 5 + 1,
                '[' => acc * 5 + 2,
                '{' => acc * 5 + 3,
                '<' => acc * 5 + 4,
                _ => panic!()
            }
        }));
    }
    // Mid point of sorted lines
    (tot, *results.iter().sorted().nth(results.len() / 2).unwrap())
}

pub fn main() {
    let tot = include_str!("../input.txt").lines().collect::<Vec<&str>>();
    let result = solve(tot);

    println!("Part1: {}", result.0);
    println!("Part2: {}", result.1);
}