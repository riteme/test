struct ToDrop;

impl Drop for ToDrop {
    fn drop(&mut self) {
        println!("dropping...");
    }
}

#[derive(Debug)]
struct Person {
    name: String,
    age: u32,
}

#[allow(dead_code)]
fn pass_x<'a, 'b>(x: &'a i32, _: &'b i32) -> &'b i32
where
    'a: 'b,
{
    x
}

#[derive(Debug)]
struct Single;

#[derive(Debug)]
struct Borrowed<'a>(&'a Single);

#[derive(Debug)]
struct NamedBorrowed<'a> {
    x: &'a Single,
    y: &'a Single,
}

#[derive(Debug)]
enum Either<'a> {
    Ref(&'a Single),
}

impl Default for NamedBorrowed<'_> {
    fn default() -> Self {
        Self {
            x: &Single,
            y: &Single,
        }
    }
}

fn main() {
    let x = Single;
    let y = Single;

    let single = Borrowed(&x);
    let double = NamedBorrowed { x: &x, y: &y };
    println!("{:?}", single);
    println!("{:?}", double);

    let reference = Either::Ref(&x);
    println!("{:?}", reference);

    let _ = NamedBorrowed::default();
    let test: NamedBorrowed = Default::default();
    println!("{:?}", test);

    let x = ToDrop;
    println!("aha!");
    let _ = x;

    let immutable_box = Box::new(5u32);
    println!("{}", immutable_box);
    // *immutable_box = 4u32;
    let mut mutable_box = immutable_box;
    *mutable_box = 4u32;
    println!("{}", mutable_box);

    let person = Person {
        name: String::from("Alice"),
        age: 20u32,
    };

    let Person { name, ref age } = person;
    println!("name={}", name);
    println!("age={}", age);
    // println!("person={:?}", person);
    println!("person.age={}", person.age);
}
