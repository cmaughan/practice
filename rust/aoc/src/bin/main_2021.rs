#![feature(hash_drain_filter)]
#![feature(iter_array_chunks)]

mod year_2021;
use year_2021::{*};

aoc_main::main! {
    year 2021;
    day1  => part1, part2, part1_generic, part2_generic;
    day2  => part1, part2;
    day3: generator => part1, part2;
    day4: generator => part1, part2;
    day5: generator => part1, part2;
    day6: generator => part1, part2;
    day7: generator => part1, part2;
    day8: generator => part1, part2;
    day9: generator => part1, part2;
    day10: generator => part1, part2;
    day11: generator => part1, part2;//, part2_render;
    day12: generator => part1, part2;
    day13: generator => part1, part2;
    day14: generator => part1, part1_slow, part2;
    day15: generator => part1, part2;
    day16: generator => part1, part2;
}
