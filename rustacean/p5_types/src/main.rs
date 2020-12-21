type NanoSecond = u64;

fn main() {
    let dec = 65.4321f64;
    let int = dec as u8;
    let chr = int as char;
    println!("{}", int);
    println!("{}", chr);
    println!("{}", 66.0f64 as NanoSecond as u8 as char);
    println!("{}", -1i64 as u8);
    println!("{}", -3 % 7);

    let mut vec = Vec::new();
    vec.push(1i32);
    println!("{:?}", vec);
}
