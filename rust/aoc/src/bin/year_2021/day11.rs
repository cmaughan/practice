use itertools::Itertools;
//use crate::day11_render;

const COUNT : usize = 100;
const SURROUND : [(isize, isize); 8] = [(0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0),
    (-1, -1)];

pub fn flash(grid: &mut Vec<Vec<u8>>, (x, y) : (usize, usize)) -> usize {
    // Reset this flash
    grid[y as usize][x as usize] = 0;
    SURROUND.iter().fold(1, |acc, (a, b)| {
        let (xx, yy) = (x as isize + a, y as isize + b);
        if (xx >= 0) && (yy >= 0) && (xx < grid[0].len() as isize) && (yy < grid.len() as isize) {
            let (ux, uy) = (xx as usize, yy as usize);
            if grid[uy][ux] > 0 {
                grid[uy][ux] += 1;
                if grid[uy][ux] > 9 {
                    return acc + flash(grid, (ux, uy));
                }
            }
        }
        acc
    })
}

pub fn step(grid: &mut Vec<Vec<u8>>) -> usize {
    let mut tot = 0;
    // Increment Octopi
    for y in 0..grid.len() {
        for x in 0..grid[0].len() {
            grid[y][x] += 1;
        }
    }

    // Do flashes
    for y in 0..grid.len() {
        for x in 0..grid[0].len() {
            if grid[y][x] > 9 {
                tot += flash(grid, (x, y));
            }
        }
    }
    tot
}

pub fn part1(g: &Vec<Vec<u8>>) -> usize {
    let mut tot = 0;
    let mut grid = g.clone();
    for _count in 0..COUNT {
        tot += step(&mut grid)
    }
    tot
}

pub fn part2(g : &Vec<Vec<u8>>) -> usize {
    let mut steps = 0;
    let mut grid = g.clone();
    loop {
        steps += 1;
        let count = step(&mut grid);
        if count == grid.len() * grid[0].len(){
            break;
        }
    }
    steps
}

#[allow(dead_code)]
pub fn part2_render(g: &Vec<Vec<u8>>) -> usize {
    crate::day11_render::part2_render(g);
    0
}

pub fn generator(input: &str) -> Vec<Vec<u8>> {
   input.lines()
        .map(|l| l.as_bytes().into_iter().map(|&b| b - b'0').collect_vec())
        .collect_vec()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_day() {
        let data = "5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526".lines()
            .map(|l| l.as_bytes().into_iter().map(|&b| b - b'0').collect_vec())
            .collect_vec();

        assert_eq!(part1(&mut data.clone()), 1656);
    }
}
