use lazy_static::lazy_static;
use regex::Regex;

lazy_static! {
    static ref RE : Regex = Regex::new(r"(\d+)-(\d+) (.): (\w+)").unwrap();
    static ref FILE : String = include_str!("../input.txt").to_string();
}

fn part1() -> usize {
    return RE.captures_iter(&FILE)
        .filter(|c| {
            // c1,c2 range, c3 letter, c4 pw
            let matches = c[4].matches(&c[3].to_string()).count();
            matches >= c[1].parse().unwrap() && matches <= c[2].parse().unwrap()
        }).count();
}

fn part2() -> usize {
    return RE.captures_iter(&FILE)
        .filter(|c| {
            let pw = c[4].to_string().into_bytes();
            let letter = c[3].as_bytes()[0];
            let range = (c[1].parse::<usize>().unwrap(), c[2].parse::<usize>().unwrap());
            (pw[range.0 - 1] == letter) != (pw[range.1 - 1] == letter)
        }).count();
}

pub fn main() {
    println!("day2_p1 {}", part1());
    println!("day2_p2 {}", part2());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse() {
        let cap = RE.captures_iter("6-3 f: abc");
        for c in cap {
            println!("{:#?}", c);
        }

        assert_eq!("6", "6");
    }
}