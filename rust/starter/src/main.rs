use std::io;
use rand::Rng;

fn main() {
    loop {
        println!("Guess a number:");
        let mut guess = String::new();

        io::stdin().read_line(&mut guess)
            .expect("Bad");

        println!("You guessed {}", guess);
    }

}
