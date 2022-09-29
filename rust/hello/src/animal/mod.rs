//pub mod animal {
#[derive(Debug)]
pub struct Animal {
    food: String,
    drink: String,
}
pub trait Consume {
    fn eat(&self);
    fn drink(&self);
}

impl Animal {
    pub fn new() -> Animal {
        Animal {
            food: String::from("food"),
            drink: String::from("drink"),
        }
    }
    fn eat(&self) {
        println!("animal eat {:?}", self.food)
    }
    fn drink(&self) {
        println!("animal drink {:?}", self.drink)
    }
}

impl Consume for Animal {
    fn eat(&self) {
        //self.eat();
        println!("eat {:?}", self.food)
    }
    fn drink(&self) {
        //self.drink();
        println!("drink {:?}", self.drink)
    }
}
