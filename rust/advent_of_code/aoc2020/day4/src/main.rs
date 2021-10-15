use std::collections::HashSet;
use itertools::Itertools;

const FILE : &'static str = include_str!("../input.txt");
const REQ_FIELDS: [&'static str; 7] = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"];

fn part1(data : &str) -> usize {
    /*
    data
        .split("\n\n")
        .map(|fields| fields
            .split_ascii_whitespace()
            .map(| field | field.split(":").next().unwrap())
            .collect::<HashSet<_>>())
        .filter(|p| REQ_FIELDS.iter().all(|req| p.contains(req)))
        .count()
     */
    let v = data.split("\n\n").map(|f| f.split_ascii_whitespace()).next().unwrap();
    println!("{:?}", v );
    5
}

fn part2(_data : &str) -> usize {
    5
}


pub fn main() {
    println!("day4_p1 {}", part1(&FILE));
    println!("day4_p2 {}", part2(&FILE));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn day4_tests() {
const TESTDATA : &'static str = r#"ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in"#;

        part1(&TESTDATA);
        //assert_eq!(part1(&TESTDATA), 2);
    }
}
