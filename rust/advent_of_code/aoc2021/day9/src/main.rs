use itertools::Itertools;

fn part1(data: &Vec<Vec<u8>>) -> usize {
    let mut tot: usize = 0;
    for y in 0..data.len() as i32{
        for x in 0..data[0].len() as i32 {
            let at = data[y as usize][x as usize];
            let found = [(x + 1, y), (x  - 1, y), (x, y - 1), (x, y  + 1)].iter().
                map(|&(xx, yy)| {
                    if xx < 0 || yy < 0 || xx >= data[0].len() as i32 || yy >= data.len() as i32 {
                        return 9 as u8;
                    }
                    let ret = data[yy as usize][xx as usize];
                    ret
                }).all(|v| v > at);
            if found {
                tot += data[y as usize][x as usize] as usize + 1;
            }
        }
    }
    tot
}

fn part2(grid: &mut Grid) -> usize {
    let mut vals: Vec<i32> = (0..grid.data[0].len()).cartesian_product(0..grid.data.len()).map(|
        (x, y)| {
        let r = grid.clone().fill((x as i32, y as i32)) as i32 + 1;
        r
    }).collect::<Vec<i32>>();
    vals.sort();
    vals.reverse();
    (vals[0] * vals[1] * vals[2]) as usize
}

pub fn main() {
   let d = "2199943210
3987894921
9856789892
8767896789
9899965678";
   // let d = include_str!("../input.txt");
    let data = d.lines()
        .map(|l| l.as_bytes().into_iter().map(|&b| b - b'0').collect_vec())
        .collect_vec();

    //let mut g = Grid::new(data);
    println!("Part1: {}", part1(&data));
    //println!("Part2: {}", part2(&data));
}
/*
const NEXT: [(isize, isize); 4] = [(0, -1), (0, 1), (-1, 0), (1, 0)];
pub fn main() {
    let mut input = include_bytes!("../input.txt")
        .split(|&b| b == b'\n')
        .map(|l| l.to_vec())
        .collect::<Vec<Vec<u8>>>();

    let mut basins = vec![];
    for y in 0..input.len() {
        for x in 0..input[0].len() {
                (input[x][y] < b'9').then(|| basins.push(basin(&mut input, x, y)));
            }
    }
    basins.sort_unstable();
    println!("{}", basins.iter().rev().take(3).product::<usize>());
}

fn basin(map: &mut Vec<Vec<u8>>, x: usize, y: usize) -> usize {
    map[y][x] = b'9';
    NEXT.iter()
        .map(|(xx, yy)| ((x as isize + xx) as usize, (y as isize + yy) as usize))
        .fold(1, |acc, (x, y)| {
            match map.get(y).and_then(|l| l.get(x)).map(|&n| n < b'9') {
                Some(true) => acc + basin(map, x, y),
                _ => acc,
            }
        })
}
*/