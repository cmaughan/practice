use std::collections::hash_set::HashSet;

const SIZE: usize = 5;

struct Board {
    numbers: Vec<u32>,
    found: HashSet<u32>,
    won: bool
}

impl Board {
    fn new(vals: Vec<u32>) -> Board {
        Board {
            numbers: vals,
            found: HashSet::new(),
            won: false
        }
    }

    fn at(&self, x: usize, y: usize) -> u32 {
        return self.numbers[y * SIZE + x];
    }

    fn score(&self) -> u32 {
        self.numbers.iter().filter(|n| {
            !self.found.contains(n)
        }).sum::<u32>()

    }
    pub fn add_number(&mut self, num : u32) {
        for x in 0..SIZE {
            for y in 0..SIZE {
                if num == self.at(x, y) {
                    self.found.insert(num);
                }
            }
        }
    }
    fn check_winner(&mut self) -> u32 {
        for major in 0..SIZE {
            if (0..SIZE).all(|x| self.found.contains(&self.at(x, major))) {
                return self.score();
            }
            if (0..SIZE).all(|y| self.found.contains(&self.at(major, y))) {
                return self.score();
            }
        }
        return 0
    }
}

fn part1(boards: &mut Vec<Board>, vals: &[u32]) -> u32 {
    for num in vals {
        for board in boards.iter_mut() {
            board.add_number(*num);
            let val = board.check_winner();
            if val != 0 {
                board.won = true;
                return val * *num;
            }
        }
    }
    return 0
}

fn part2(boards: &mut Vec<Board>, vals: &[u32]) -> u32 {
    let mut last_score = 0;
    for num in vals {
        for board in boards.iter_mut() {
            if !board.won {
                board.add_number(*num);
                let val = board.check_winner();
                if val != 0 {
                    last_score = val * *num;
                    board.won = true;
                }
            }
        }
    }
    last_score
}

pub fn main() {
    let input = include_str!("../input.txt");
    let nums: Vec<u32> = input.lines().next().unwrap().split(',').map(|v| { v.parse().unwrap() })
        .collect();

    // Called numbers
    let mut vals = Vec::new();
    for l in input.lines().skip(1) {
        for v in l.split_ascii_whitespace() {
            vals.push(v.parse::<u32>().unwrap());
        }
    }

    // Boards
    let mut boards = Vec::new();
    for chunk in vals.chunks(25) {
        boards.push(Board::new(chunk.to_vec()));
    }

    println!("Part1: {}", part1(&mut boards, &nums));
    println!("Part2: {}", part2(&mut boards, &nums));
}
