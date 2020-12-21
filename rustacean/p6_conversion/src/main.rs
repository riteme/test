use std::convert::{From, TryFrom};
use std::fmt;
use std::num::ParseIntError;
use std::str::FromStr;

#[derive(Debug)]
struct Number {
    value: i64,
}

impl From<i64> for Number {
    fn from(value: i64) -> Number {
        Number { value }
    }
}

#[derive(Debug)]
struct EvenNumber {
    value: i64,
}

impl TryFrom<i64> for EvenNumber {
    type Error = ();

    fn try_from(value: i64) -> Result<Self, Self::Error> {
        if value % 2 == 0 {
            Ok(EvenNumber { value })
        } else {
            Err(())
        }
    }
}

impl fmt::Display for EvenNumber {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "An even number {}", self.value)
    }
}

#[derive(Debug)]
struct Point {
    x: i32,
    y: i32,
}

#[derive(Debug)]
enum ParsePointError {
    FormatError,
    Other(ParseIntError),
}

impl From<ParseIntError> for ParsePointError {
    fn from(err: ParseIntError) -> Self {
        ParsePointError::Other(err)
    }
}

impl FromStr for Point {
    type Err = ParsePointError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let coords: Vec<_> = s
            .trim_matches(|c| c == '(' || c == ')')
            .split(',')
            .collect();
        if coords.len() != 2 {
            return Err(ParsePointError::FormatError);
        }

        let x: i32 = coords[0].parse()?;
        let y = coords[1].parse::<i32>()?;

        Ok(Point { x, y })
    }
}

fn main() {
    let number1 = Number::from(123);
    println!("{:?}", number1);
    let number2: Number = 456i64.into();
    println!("{:?}", number2);
    let number3 = Number::from(number1);
    println!("{:?}", number3);
    // println!("{:?}", number1);

    let result1 = EvenNumber::try_from(234i64);
    let result2 = EvenNumber::try_from(235i64);
    println!("{:?}", result1);
    println!("{:?}", result2);
    println!("{}", result2.unwrap_or(EvenNumber { value: 19260817 }));

    if let Ok(value) = result1 {
        println!("{:?}", value);
        println!("{}", value);
        println!("{}", value.to_string());
    }

    let p = Point::from_str("(1)");
    println!("{:?}", p);
    let p = Point::from_str("(1,2,3,4)");
    println!("{:?}", p);
    let p = Point::from_str("(1, 2)");
    println!("{:?}", p);
    let p = Point::from_str("(1,2)");
    println!("{:?}", p);
}
