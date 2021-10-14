use lazy_static::lazy_static;

lazy_static! {
    static ref FILE : String = include_str!("../input.txt").to_string();
}

fn do_slope(input : &str, x: usize, y: usize) -> usize {
    input
        .lines()
        .step_by(y)
        .zip((0..).step_by(x))
        .skip(1)
        .filter(|&(l, x)| l.bytes().cycle().nth(x).unwrap() == b'#')
        .count()
}

fn part1() -> usize {
    do_slope(&FILE, 3, 1)
}

fn part2() -> usize {
    [(1, 1), (3, 1), (5, 1), (7,1), (1, 2)]
        .iter()
        .map(|s| do_slope(&FILE, s.0, s.1))
        .product()
}

pub fn main() {
    println!("day3_p1 {}", part1());
    println!("day3_p2 {}", part2());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn slope_test() {
        lazy_static! {
static ref TESTDATA : String = r#"..##.......
#...#...#..
.#....#..#.
..#.#...#.#
.#...##..#.
..#.##.....
.#.#.#....#
.#........#
#.##...#...
#...##....#
.#..#...#.#"#.to_string();
            }

        assert_eq!(2, do_slope(&TESTDATA, 1, 1));
        assert_eq!(7, do_slope(&TESTDATA, 3, 1));
        assert_eq!(3, do_slope(&TESTDATA, 5, 1));
        assert_eq!(4, do_slope(&TESTDATA, 7, 1));
        assert_eq!(2, do_slope(&TESTDATA, 1, 2));
    }
}
