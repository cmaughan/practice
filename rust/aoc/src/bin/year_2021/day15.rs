use std::{cmp::Reverse, collections::BinaryHeap};
use ndarray::{Array, Array2};

pub fn solve(grid : &Array2<u8>) -> usize {
    let mut q = BinaryHeap::new();
    let mut distances : Array2<usize> = Array::from_elem(grid.raw_dim(), usize::MAX);
    q.push((Reverse(0), (0, 0)));
    let goal = (grid.nrows() - 1, grid.ncols() - 1);
    while let Some((Reverse(cost), position)) = q.pop() {
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
            let new_pos = (new_x as usize, new_y as usize);
            let cave_cost = grid[new_pos] as usize + cost;
            if cave_cost < distances[new_pos] {
                q.push((Reverse(cave_cost), new_pos));
                distances[new_pos] = cave_cost;
            }
        }
    }
    unreachable!();
}

pub fn part1(d: &Data) -> usize {
    solve(&d.grid)
}

pub fn part2(d: &Data) -> usize {
    solve(&d.grid5x5)
}

pub struct Data {
    grid: Array2<u8>,
    grid5x5: Array2<u8>
}

pub fn generator(input: &str) -> Data {
    let height = input.lines().count();
    let width = input.lines().next().unwrap().len();

    let vals = input.bytes()
        .filter(|&c| c != b'\n')
        .map(|v| (v - b'0') as u8)
        .collect::<Vec<u8>>();

    let a = Array::from_shape_fn((width, height), |(x, y)| vals[y * width + x]);

    // Duplicate and increment
    let b = Array::from_shape_fn((width * 5, height * 5), |(x, y)| {
        let (orig_x, orig_y) = (x % width, y % height);
        let (x_tile, y_tile) = (x / width, y / height);
        ((vals[orig_y * width + orig_x] + x_tile as u8 + y_tile as u8 - 1) % 9) + 1
    });

    Data { grid: a, grid5x5: b }
}