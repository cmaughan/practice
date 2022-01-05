use std::collections::hash_map::HashMap;

fn solve(vals: &[(i32, i32, i32, i32)], diag: bool) -> usize {
    let mut m = HashMap::new();
    for (x1, y1, x2, y2) in vals {
        if !diag && !(x1 == x2 || y1 == y2) {
            continue;
        }

        let (mut x, mut y) = (*x1, *y1);
        let (x_inc, y_inc) = ((x2 - x1).signum(), (y2 - y1).signum());
        loop {
            *m.entry((x, y)).or_insert(0) += 1;
            x += x_inc;
            y += y_inc;
            if x == (x2 + x_inc) && y == (y2 + y_inc) {
                break;
            }
        }
    }
    m.values().filter(|&&v| v > 1).count()
}

pub fn part1(vals: &[(i32, i32, i32, i32)]) -> usize {
    solve(vals, false)
}

pub fn part2(vals: &[(i32, i32, i32, i32)]) -> usize {
    solve(vals, true)
}

pub fn generator(input: &str) -> Vec<(i32, i32, i32, i32)> {
    input
        .lines()
        .map(|l| l.split(" -> "))
        .flatten()
        .map(|l| l.split(','))
        .flatten()
        .map(|i| i.parse::<i32>().unwrap())
        .collect::<Vec<_>>()
        .chunks(4)
        .map(|v| (v[0], v[1], v[2], v[3]))
        .collect::<Vec<_>>()
}
