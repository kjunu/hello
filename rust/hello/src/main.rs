use crate::animal::Consume;

pub mod animal;

pub struct Bio {
    animal: animal::Animal,
}

fn main() {
    let a = animal::Animal::new();
    //let b = Bio { animal: a };
    println!("Hello, world! {:?}", a.eat());
}
