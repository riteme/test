use std::fmt;

#[derive(Debug)]
struct Person {
    name: String,
    age: u8,
}

struct Unit;

#[derive(Debug)]
struct Pair(i32, f32);

struct Point {
    x: f32,
    y: f32,
}

impl fmt::Display for Point {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

enum WebEvent {
    PageLoad,
    PageUnload,
    KeyPress(char),
    Paste(String),
    Click { x: i64, y: i64 },
}

fn inspect(event: WebEvent) {
    match event {
        WebEvent::PageLoad => println!("page loaded"),
        WebEvent::PageUnload => println!("page unloaded"),
        WebEvent::KeyPress(c) => println!("pressed '{}'", c),
        WebEvent::Paste(s) => println!("pasted \"{}\"", s),

        // be careful with if, since it's hard to analyze.
        // WebEvent::Click { x, .. } if x != 0 => println!("clicked at x={}", x),
        WebEvent::Click { x: 0, y } => println!("clicked at y={}", y),
        WebEvent::Click { x, .. } => println!("clicked at x={}", x),
    }
}

type Ev = WebEvent;

enum Color {
    Red = 0xff0000,
    Green = 0x00ff00,
    Blue = 0x0000ff,
}

enum List {
    Cons(u32, Box<List>),
    Null,
}

use crate::List::*;

impl List {
    fn new() -> Self {
        Null
    }

    fn prepend(self, x: u32) -> Self {
        Cons(x, Box::new(self))
    }

    fn len(&self) -> usize {
        match *self {
            Cons(_, ref remain) => remain.len() + 1,
            Null => 0,
        }
    }

    fn stringify(&self) -> String {
        match *self {
            Cons(x, ref remain) => format!("{}, {}", x, remain.stringify()),
            Null => String::from("#"),
        }
    }
}

static mut LANG: &str = "Rust";

fn main() {
    let name = String::from("Peter");
    let age = 27;
    let peter = Person { age, name };
    println!("{:?}", peter);

    let point: Point = Point { x: 10.3, y: 0.4 };
    println!("{}", point);

    let p2 = Point { x: -9.8, ..point };
    println!("{}", p2);

    let _unused = Unit;
    let pair = Pair(1, 0.9);
    println!("{:?}", pair);

    let Pair(integer, decimal) = pair;
    println!("{}, {}", integer, decimal);

    use crate::WebEvent::*;

    let pressed = KeyPress('x');
    // `to_owned()` creates an owned `String` from a string slice.
    let pasted = Paste("my text".to_owned());
    let click = WebEvent::Click { x: 20, y: 80 };
    let load = WebEvent::PageLoad;
    let unload = Ev::PageUnload;

    inspect(pressed);
    inspect(pasted);
    inspect(click);
    inspect(WebEvent::Click { x: 0, y: 1120 });
    inspect(load);
    inspect(unload);

    use Color::{Blue, Green, Red};
    println!("red is 0x{:06x}", Red as u32);
    println!("green is 0x{:06x}", Green as u32);
    println!("blue is 0x{:06x}", Blue as u32);

    // Create an empty linked list
    let mut list = List::new();

    // Prepend some elements
    list = list.prepend(1);
    list = list.prepend(2);
    list = list.prepend(3);

    // Show the final state of the list
    println!("linked list has length: {}", list.len());
    println!("{}", list.stringify());

    unsafe {
        LANG = "C++";
    }

    unsafe {
        println!("{}", LANG);
    }

    struct NonCopy(i32);
    const FOO: NonCopy = NonCopy(42);
    static BAR: NonCopy = NonCopy(-1);

    let _works = FOO;
    // let _fails = BAR;
    let _also_works = &BAR;
}
