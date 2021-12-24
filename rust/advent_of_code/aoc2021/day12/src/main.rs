use std::collections::HashMap;

pub fn seek<'a>(caves: &HashMap<&str, Vec<&'a str>>, path : &mut Vec<&'a str>, small_count: i32)
    -> usize {
    let mut tot = 0;
    for &s in caves.get(*path.last().unwrap()).unwrap().iter() {
        let mut count = 0;
        if s == "end" {
            tot += 1;
            continue;
        }
        if s == "start" {
            continue;
        }
        if s.to_lowercase() == s {
            count = path.iter().filter(|&&comp| s == comp).count() as i32;
            if count > small_count {
                continue;
            }
        };

        path.push(s);
        tot += seek(&caves, path, small_count - count);
        path.pop();
    }
    tot
}
pub fn start<'a>(caves : &HashMap<&str, Vec<&'a str>>, small_count: i32) -> usize {
    let mut tot = 0;
    for s in caves["start"].iter() {
        let mut v = Vec::new();
        v.push(*s);
        tot += seek(&caves, & mut v, small_count);
        v.pop();
    }
    tot
}

pub fn main() {
    let d = include_str!("../input.txt").lines()
        .fold(HashMap::new(), |mut acc, l| {
            let (left, right) = l.split_once("-").unwrap();
            acc.entry(left).or_insert(Vec::new()).push(right);
            acc.entry(right).or_insert(Vec::new()).push(left);
            acc
        });

    let p1 = start(&d, 0);
    assert!(p1 == 3497);
    println!("Part1: {}", p1);

    let p2 = start(&d, 1);
    assert!(p2 == 93686);
    println!("Part2: {}", p2);

}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_day() {
    }
}
