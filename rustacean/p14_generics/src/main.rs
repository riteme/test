struct Val {
    val: f64,
}

struct GenVal<T> {
    gen_val: T,
}

impl Val {
    fn value(&self) -> f64 {
        self.val
    }
}

impl GenVal<&Val> {
    fn rvalue(&self) -> f64 {
        self.gen_val.value()
    }
}

impl<T> GenVal<T> {
    fn value(&self) -> &T {
        &self.gen_val
    }
}

struct FTP;
struct HTTP;

trait DoubleDrop<T> {
    fn double_drop(self, _: T);
}

impl<T, U> DoubleDrop<T> for U {
    fn double_drop(self, _: T) {}
}

struct Cardinal;
struct BlueJay;

trait Red {}
trait Blue {}

impl Red for Cardinal {}
impl Blue for BlueJay {}

fn red<T: Red>(_: &T) -> &'static str {
    "red"
}

fn blue<T: Blue>(_: &T) -> &'static str {
    "blue"
}

use std::fmt::{Debug, Display};

fn compare_prints<T>(t: &T)
where
    T: Debug + Display,
{
    println!("{}", t);
    println!("{:?}", t);
}

trait PrintInOption {
    fn print_in_option(self);
}

impl<T> PrintInOption for T
where
    Option<T>: Debug,
{
    fn print_in_option(self) {
        println!("{:?}", Some(self));
    }
}

use std::marker::PhantomData;
use std::ops::Add;

#[derive(Debug, Clone, Copy)]
struct Inch {}

#[derive(Debug, Clone, Copy)]
struct Mm {}

#[derive(Clone, Copy, Debug)]
struct Length<Unit>(f64, PhantomData<Unit>);

impl<Unit> Add for Length<Unit> {
    type Output = Length<Unit>;

    fn add(self, rhs: Self) -> Self {
        Length(self.0 + rhs.0, PhantomData)
    }
}

fn main() {
    let one_foot = Length::<Inch>(12.0, PhantomData);
    let one_meter: Length<Mm> = Length(1000.0, PhantomData);
    let two_feet = one_foot + one_foot;
    let two_meters = one_meter + one_meter;
    println!("two_feet = {:?}", two_feet);
    println!("two_meters = {:?}", two_meters);

    let v = vec![1, 2, 4, 5, 7];
    v.print_in_option();

    let s = "Hello, Rustacean!";
    compare_prints(&s);

    let ftp = FTP;
    let http = HTTP;
    let x = 1;
    let y = 2;

    x.double_drop(y);
    ftp.double_drop(http);

    let c = Cardinal;
    let b = BlueJay;
    println!("{}", red(&c));
    println!("{}", blue(&b));

    let x = Val { val: 3.0 };
    let y = GenVal { gen_val: 3i32 };
    let z = GenVal { gen_val: &x };
    println!("{} {} {}", x.value(), y.value(), z.rvalue());
}
