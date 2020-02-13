use std::io;
use rand::RngCore;

fn main() {
    loop {
        println!("Guess a number:");
        let mut guess = String::new();

        let val = rand::thread_rng().next_u32();
        println!("Val {}", val);
        io::stdin().read_line(&mut guess)
            .expect("Bad");

        println!("You guessed {}", guess);
    }

}
