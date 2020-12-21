fn main() {
    'outer: loop {
        println!("outer");

        'inner: loop {
            println!("inner");
            break;
        }

        println!("aha!");
    }

    println!("exited.");
}
