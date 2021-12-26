pub fn jobs() -> &'static [(fn(), &'static str)] {
    &[
        (day1::main, "day1"),
        (day2::main, "day2"),
        (day3::main, "day3"),
        (day4::main, "day4"),
        (day5::main, "day5"),
        (day6::main, "day6"),
        (day7::main, "day7"),
        (day8::main, "day8"),
        (day9::main, "day9"),
        (day10::main, "day10"),
        (day11::main, "day11"),
        (day12::main, "day12"),
        (day13::main, "day13")
    ]
}
