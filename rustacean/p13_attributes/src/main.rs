fn main() {
    #[cfg(feature = "some_condition")]
    {
        println!("Hello, world!");
    }
    println!("aha!");
}
