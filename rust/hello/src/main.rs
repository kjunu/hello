use crate::animal::Consume;

pub mod animal;

#[derive(Default)]
pub struct Bio {
    //animal: animal::Animal,
    name: String,
}

impl Bio {
    fn default() -> Bio {
        let a = animal::Animal::new(String::from("apple"), String::from("soda"));
        //Bio { animal: a }
        Bio {
            name: String::from("earth"),
        }
    }
}

fn main() {
    let b = Bio::default();
    println!("Hello, world! {:?}", b.name);
    //println!("Hello, world! {:?}", b.animal.eat());
}
