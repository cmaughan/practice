pub fn add_one() -> usize {
    1
}

pub struct BitWalker<'a> {
    bits: &'a [u8]
}