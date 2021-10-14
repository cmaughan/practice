pub fn jobs() -> &'static [(fn(), &'static str)] {
    &[
        (day1::main, "day1"),
        (day2::main, "day2"),
        (day3::main, "day3")
    ]
}
