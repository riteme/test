use std::fmt;

#[derive(Debug)]
struct Structure(i32);

#[derive(Debug)]
struct Deep(Structure);

#[derive(Debug)]
struct Person<'a> {
    name: &'a str,
    age: u32,
}

impl<'a> fmt::Display for Person<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}, #{}", self.name, self.age)
    }
}

struct List(Vec<i32>);

impl fmt::Display for List {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let v = &self.0;

        write!(f, "[")?;

        for (i, v) in v.iter().enumerate() {
            if i > 0 {
                write!(f, ", ")?;
            }
            write!(f, "{}: {}", i, v)?;
        }

        write!(f, "]")
    }
}

fn main() {
    #![allow(unused_variables)]

    let a = Deep(Structure(1));
    println!("{arg:?}", arg = a);
    println!("{:?}", "string test");

    let b = Person {
        name: "Peter",
        age: 27,
    };
    println!("{:#?}", b);
    println!("{}", b);

    let c = 2;

    let li = List(vec![1, 2, 3, 5, 4]);
    println!("{}", li);

    println!("0x{:0width$x}", 19260817, width = 16);
}
