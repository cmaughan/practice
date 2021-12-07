pub fn jobs() -> &'static [(fn(), &'static str)] {
    &[
        (day1::main, "day1"),
        (day2::main, "day2"),
        (day3::main, "day3"),
        (day4::main, "day4"),
        (day5::main, "day5"),
        (day6::main, "day6"),
        (day7::main, "day7")
    ]
}
