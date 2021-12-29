#![feature(hash_drain_filter)]
use std::collections::HashSet;

const X_FOLD : usize = 0;
const Y_FOLD : usize = 1;

fn print_grid(dots: &HashSet<(usize, usize)>) {
    // Find the size
    let width = *dots.iter().map(|(x, _)| x).max().unwrap() + 1;
    let height = *dots.iter().map(|(_, y)| y).max().unwrap() + 1;

    for y in 0..height {
        for x in 0..width {
            if dots.contains(&(x, y)) {
                print!("*");
            }
            else {
                print!(" ");
            }
        }
        print!("\n");
    }
}

fn fold(dots: &mut HashSet<(usize, usize)>, &(fold, coord): &(usize, usize)) {

    let right : HashSet<_> = dots.drain_filter(|&(x, y)| match fold {
        X_FOLD => x > coord,
        Y_FOLD => y > coord,
        _ => panic!("error")
    }).collect();

    dots.extend(right.iter().map(|&(x, y)| match fold {
        X_FOLD => (coord - (x - coord), y),
        Y_FOLD => (x, coord - (y - coord)),
        _ => panic!("error")
    }));
}

fn part1(dots: &mut HashSet<(usize, usize)>, folds: &Vec<(usize, usize)>) -> usize {
    fold(dots, folds.first().unwrap());
    dots.len()
}

fn part2(dots: &mut HashSet<(usize, usize)>, folds: &Vec<(usize, usize)>) -> usize {
    for f in folds {
        fold(dots, f);
    }

    print_grid(&dots);
    dots.len()
}

pub fn main() {
    let d = include_str!("../input.txt").split_once("\n\n").unwrap();
    let mut dots = d.0.lines()
        .map(|l| l.split_once(',').unwrap())
        .map(|(a, b)| (a.parse::<usize>().unwrap(), b.parse::<usize>().unwrap()))
        .collect::<HashSet<(usize, usize)>>();

    let folds = d.1.lines()
        .map(|l| l.split_once('=').unwrap())
        .map(|(from, coord)|
            match from.chars().last().unwrap() {
                'x' => (X_FOLD, coord.parse::<usize>().unwrap()),
                'y' => (Y_FOLD, coord.parse::<usize>().unwrap()),
                _ => panic!("Unexpected")
            }
        )
        .collect::<Vec<(usize, usize)>>();

    println!("Part1: {}", part1(&mut dots, &folds));
    println!("Part2: {}", part2(&mut dots, &folds));
}

#[cfg(test)]
mod tests {
    //use super::*;

    #[test]
    fn test_day() {
    }
}
