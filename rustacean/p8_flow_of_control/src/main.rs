fn main() {
    #![allow(unreachable_code)]
    'outer: loop {
        println!("outer");

        /* 'inner: */
        loop {
            println!("inner");
            break 'outer;
        }

        println!("aha!");
    }

    println!("exited.");

    let mut counter = 0;
    let result = loop {
        counter += 1;

        if counter == 10 {
            break counter * 3;
        }
    };

    println!("{}", result);

    let mut sum = 0;
    for x in 1..=100 {
        sum += x;
    }
    println!("{}", sum);

    let mut names = vec!["Bob", "Frank", "Ferris"];
    for name in names.iter_mut() {
        *name = match name {
            &mut "Ferris" => "There's a rustacean among us!",
            _ => "Hello",
        }
    }

    println!("{:?}", names);

    let mut reference = &4;
    let ref also_reference = 5;
    println!("{:?} {:?}", reference, also_reference);

    match also_reference {
        &val => println!("{}", val),
    }

    match reference {
        ref mut val => *val = &123,
    }

    println!("{}", reference);

    match 123 {
        n @ 1..=200 => println!("n = {}", n),
        x => println!("x = {}", x),
    }
}
