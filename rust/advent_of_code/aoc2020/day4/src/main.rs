use std::collections::HashMap;

const FILE : &'static str = include_str!("../input.txt");
const REQ_FIELDS: [&'static str; 7] = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"];
const EYE_COLORS : [&'static str; 7] = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"];

fn part1(data : &str) -> usize {
    data
        .split("\n\n")
        .map(|fields| fields
            .split_ascii_whitespace()
            .map(| field | field.split_once(":").unwrap())
            .collect::<HashMap<_,_>>())
        .filter(|p| REQ_FIELDS.iter().all(|req| p.contains_key(req)))
        .count()

}

fn validate_passport(field: &str, value: &str) -> bool {
    match field {
        "byr" => value.parse::<usize>().unwrap().wrapping_sub(1920) <= 82,
        "iyr" => value.parse::<usize>().unwrap().wrapping_sub(2010) <= 10,
        "eyr" => value.parse::<usize>().unwrap().wrapping_sub(2020) <= 10,
        "hgt" => {
            if value.ends_with("cm") && value.len() == 5 {
                value[0..3].parse::<usize>().unwrap().wrapping_sub(150) <= 43
            } else if value.ends_with("in") && value.len() == 4 {
                value[0..2].parse::<usize>().unwrap().wrapping_sub(59) <= 27
            } else {
                false
            }
        }
        "hcl" => value.len() == 7,
        "ecl" => EYE_COLORS.contains(&value),
        "pid" => value.len() == 9,
        "cid" => true,
        _ => panic!("Field?")
    }
}

fn part2(data : &str) -> usize {
    data
        .split("\n\n")
        .map(|fields| fields
            .split_ascii_whitespace()
            .map(| field | field.split_once(":").unwrap())
            .collect::<HashMap<_,_>>())
        .filter(|p| REQ_FIELDS.iter().all(|req| p.contains_key(req)))
        .filter(|p| p.iter().all(|(k,v)| validate_passport(k, v)))
        .count()
}


pub fn main() {
    println!("day4_p1 {:?}", part1(&FILE));
    println!("day4_p2 {:?}", part2(&FILE));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn day_tests() {
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
