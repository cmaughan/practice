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

pub fn part1(d: &Data) -> usize {
    fold(&mut d.dots.clone(), d.folds.first().unwrap());
    d.dots.len()
}

pub fn part2(d: &Data) -> usize {
    let mut dots = d.dots.clone();
    for f in d.folds.iter() {
        fold(&mut dots, &f);
    }

    print_grid(&dots);
    d.dots.len()
}

pub struct Data {
    dots: HashSet<(usize, usize)>,
    folds: Vec<(usize, usize)>
}

pub fn generator(input: &str) -> Data {
    let d = input.split_once("\n\n").unwrap();
    let dots = d.0.lines()
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

    Data { dots: dots, folds: folds}
}
