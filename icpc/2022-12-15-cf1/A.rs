use std::io;

fn main() {
    let mut buf = String::new();
    let stdin = io::stdin();
    stdin.read_line(&mut buf).expect("");
    let v: Vec<i64> = buf
        .split(" ")
        .map(|x| x.trim().parse().expect(""))
        .collect();
    let a = v[0];
    let b = v[1];
    let c = v[2];
    let d = ((a + c - 1) / c) * ((b + c - 1) / c);
    println!("{}", d);
}
