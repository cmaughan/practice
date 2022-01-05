pub fn part1(v: &Vec<u32>) -> usize {
    let mut vals = v.clone();
    for _ in 0..80 {
        let mut add = 0;
        for i in vals.iter_mut() {
            if *i == 0 {
                *i = 6;
                add += 1;
            } else {
                *i = *i - 1;
            }
        }
        while add > 0 {
            add = add - 1;
            vals.push(8);
        }
    }
    vals.len()
}

pub fn part2(v : &Vec<u32>) -> u64 {
    let mut f:[u64;9] = [0;9];

    // Init the fish kinds
    for &i in v {
        f[i as usize] = f[i as usize] + 1;
    }

    for _ in 0..256 {
        //     0,    1,    2,    3,    4,   ,5    ,6           ,7,   ,8
        f = [f[1], f[2], f[3], f[4], f[5], f[6], f[7] + f[0], f[8], f[0]];
    }
    return f.iter().sum();
}

pub fn generator(input: &str) -> Vec<u32> {
    input
        .lines()
        .map(|v| v.split(","))
        .flatten()
        .map(|v| v.parse::<u32>().unwrap())
        .collect::<Vec<_>>()
}
