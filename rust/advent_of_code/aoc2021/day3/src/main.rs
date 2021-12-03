fn get_bit_for_column(numbers: &[u32],  bit: u32) -> u32 {
    let mut count  = [0, 0];
    for num in numbers {
        count[((num >> bit) & 1) as usize] += 1;
    }
    (count[0] < count[1]) as u32
}

fn part1(numbers: &[u32], bits: usize) -> u32 {
    let val = (0..bits).map(|bit| (get_bit_for_column(&numbers, bit as u32) << bit)).sum::<u32>();
    return val * (!val & ((1 << bits) - 1));
}

fn scan(n:&[u32], bits: usize, stat: u32) -> u32 {
    let mut numbers = n.to_vec();
    for index in (0..bits).rev() {
        let one_or_zero = get_bit_for_column(&numbers, index as u32) ^ stat;
        numbers.retain(|num| {
            ((num >> index) & 0x1) == one_or_zero
        });

        if numbers.len() == 1 {
            return numbers[0];
        }
    }
    0
}

fn part2(numbers: &[u32], bits: usize) -> u32 {
    scan(numbers, bits, 0) * scan(numbers, bits, 1)
}

pub fn main() {
    let input = include_str!("../input.txt");
    let nums: Vec<u32> = input.split_ascii_whitespace()
        .map(|val| u32::from_str_radix(val, 2).unwrap())
        .collect();
    let size = input.lines().next().unwrap().len();
    println!("day3_p1 {}", part1(&nums, size));
    println!("day3_p2 {}", part2(&nums, size));
}
