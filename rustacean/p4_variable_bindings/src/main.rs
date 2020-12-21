fn main() {
    println!("{:?}", 1u32);

    let a;
    let b = 2;
    a = b - 1;

    {
        let a = 2;
        println!("{}", a);
    }

    println!("{}", a);

    let a = 3;
    println!("{}", a);

    let mut mut_a = 7;

    {
        let mut_a = 8;
        println!("{}", mut_a);

        let mut mut_a = 9;
        println!("{}", mut_a);

        mut_a = 10;
        println!("{}", mut_a);
    }

    println!("{}", mut_a);

    mut_a = 11;
    println!("{}", mut_a);
}
