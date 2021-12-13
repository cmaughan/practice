use itertools::Itertools;

fn part1(data: &Vec<Vec<u8>>) -> usize {
    // x, y visit
    (0..data[0].len() as i32).cartesian_product(0..data.len() as i32)
        .fold(0, |acc, (x, y)| {
            // Surrounding
            if [(x + 1, y), (x - 1, y), (x, y - 1), (x, y + 1)].iter().
                map(|&(xx, yy)| {
                    // Border cases
                    if xx < 0 || yy < 0 || xx >= data[0].len() as i32 || yy >= data.len() as i32 {
                        return 9 as u8;
                    }
                    let ret = data[yy as usize][xx as usize];
                    ret
                }).all(|v| v > data[y as usize][x as usize])
            {
                acc + data[y as usize][x as usize] as usize + 1
            } else {
                acc
            }
        })
}

// Realization: basins are just areas surrounded by 9
fn visit(data: &mut Vec<Vec<u8>>, (x, y) : (i32, i32)) -> usize {
    data[y as usize][x as usize] = 9;
    [(x + 1, y), (x - 1, y), (x, y - 1), (x, y + 1)].iter()
        .map(|&(xx, yy)| {
            if xx < 0 || yy < 0 || xx >= data[0].len() as i32 || yy >= data.len() as i32 {
                return 0;
            }
            if data[yy as usize][xx as usize] < 9 {
                return visit(data, (xx, yy)) + 1;
            }
            return 0;
        }).sum::<usize>()
}

fn part2(data: &mut Vec<Vec<u8>>) -> usize {
    let ret: Vec<usize> = (0..data[0].len() as i32).cartesian_product(0..data.len() as i32)
        .map(|(x, y)| {
            visit(data, (x, y))
        }).collect::<Vec<usize>>();

    ret.iter().sorted().rev().take(3).product()
}

pub fn main() {
    let mut data = include_str!("../input.txt").lines()
        .map(|l| l.as_bytes().into_iter().map(|&b| b - b'0').collect_vec())
        .collect_vec();

    println!("Part1: {}", part1(&data));
    println!("Part2: {}", part2(&mut data));
}