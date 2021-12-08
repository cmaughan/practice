use itertools::Itertools;
use std::collections::HashMap;

#[derive(Debug)]
struct Row {
    inputs: Vec<String>,
    outputs: Vec<String>
}

impl Row {
    pub fn new(ins: Vec<String>, outs: Vec<String>) -> Row {
        Row {
            inputs: ins,
            outputs: outs
        }
    }
}
pub fn common_chars(a: &str, b:&str) -> usize {
    a.chars().fold(0, |a, c| if b.chars().contains(&c) {
        a + 1
    } else {
        a
    })
}

pub fn main() {
    let input: Vec<&str> = include_str!("../input.txt")
        .lines()
        .collect();

    let mut rows = Vec::new();
    for s in input {
        let mut inputs = Vec::new();
        let mut outputs = Vec::new();

        let vals : Vec<&str> = s.split_ascii_whitespace().collect();
        let mut ins = true;
        for v in vals {
            if v == "|" {
                ins = false;
                continue;
            }
            let sorted = v.chars().sorted().collect();
            if ins {
                inputs.push(sorted);
            } else {
                outputs.push(sorted);
            }
        }

        rows.push(Row::new(inputs, outputs));
    }

    let count = rows.iter().map(|v| v.outputs.iter().filter(|v| match(v.len()) {
        2 => true, // 1
        4 => true, // 4
        3 => true, // 7
        7 => true,
        _ => false
    }).count()).sum::<usize>();

    println!("Part1: {}", count);

    let mut total = 0;
    for row in rows.iter() {
        let mut nums = std::collections::HashMap::new();
        for v in row.inputs.iter() {
            nums.insert(match v.len() {
                // A 1, 4, 7, 8
                2 => 1,
                4 => 4,
                3 => 7,
                7 => 8,
                _ => 9
            }, v);
        }

        for v in row.inputs.iter() {
            let common_1 = common_chars(v, nums.get(&1).unwrap());
            let common_4 = common_chars(v, nums.get(&4).unwrap());
            let common_7 = common_chars(v, nums.get(&7).unwrap());
            let common_8 = common_chars(v, nums.get(&8).unwrap());
            if v.len() == 6 {
                if common_1 == 1 {
                    nums.insert(6,  v); // 6
                } else if common_4 == 3 {
                    nums.insert(0, v); // 0
                } else if common_1 == 2 && common_4 == 4 {
                    nums.insert(9, v); // 9
                }
                else {
                    panic!();
                }
            } else if v.len() == 5 {
                if common_8 == 5 && common_1 == 1 && common_4 == 2 {
                    nums.insert(2, v); // 2
                } else if common_8 == 5 && common_1 == 2 {
                    nums.insert(3, v); // 3
                } else if common_7 == 2 && common_1 == 1 {
                    nums.insert(5, v); // 5
                }
                else {
                    panic!();
                }
            }
        }

        let mut s: HashMap<String, i32> = HashMap::new();
        for (k, v) in nums.iter() {
            s.insert(v.to_string(), *k);
        }

        let mut mul = 1000;
        for v in row.outputs.iter() {
            total += s.get(v.as_str()).unwrap() * mul;
            mul /= 10;
        }
    }

    println!("Part2: {}", total);
}
