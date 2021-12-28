use std::cmp::Ordering;
use std::collections::BinaryHeap;
use itertools::Itertools;
use ndarray::Array;
use ndarray::Array2;

#[derive(Copy, Clone, Eq, PartialEq)]
struct State {
    cost: usize,
    position: (usize, usize)
}

impl Ord for State {
    fn cmp(&self, other: &Self) -> Ordering {
        other.cost.cmp(&self.cost).then_with(|| self.position.cmp(&other.position))
    }
}
impl PartialOrd for State {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> { Some(self.cmp(other)) }
}

fn part1(grid : &Array2<usize>) -> usize {
    let mut q = BinaryHeap::new();
    let mut distances : Array2<usize> = Array::from_elem(grid.raw_dim(), usize::MAX);
    q.push(State {cost: 0, position: (0, 0) });
    let goal = (grid.nrows() - 1, grid.ncols() - 1);
    while let Some(State { cost, position }) = q.pop() {
        if position == goal {
            return cost;
        }
        if cost > distances[position] {
            continue;
        }
        for (x, y) in [(0, 1), (1, 0), (-1, 0), (0, -1)].iter() {
            let new_x = x + position.0 as i32;
            let new_y = y + position.1 as i32;
            if new_x < 0 || new_x >= grid.ncols() as i32 {
                continue;
            }
            if new_y < 0 || new_y >= grid.nrows() as i32 {
                continue;
            }
            let cave = grid[(new_x as usize, new_y as usize)];
            let next = State { cost: cost + cave, position: (new_x as usize, new_y as usize) };
            if next.cost < distances[next.position] {
                q.push(next);
                distances[next.position] = next.cost;
            }
        }
    }
    unreachable!();
}

pub fn main() {
    let input = include_str!("../input.txt");
    let height = input.lines().count();
    let width = input.lines().next().unwrap().len();

    let vals = input.bytes()
        .filter(|&c| c != b'\n')
        .map(|v| (v - b'0') as usize)
        .collect_vec();

    let a = Array::from_shape_fn((width, height), |(x, y)| vals[y * width + x]);

    // Duplicate and increment
    let b = Array::from_shape_fn((width * 5, height * 5), |(x, y)| {
        let (orig_x, orig_y) = (x % width, y % height);
        let (x_tile, y_tile) = (x / width, y / height);
        ((vals[orig_y * width + orig_x] + x_tile + y_tile - 1) % 9) + 1
    });

    println!("Part1: {}", part1(&a));
    println!("Part2: {}", part1(&b));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_day() {
    }
}
