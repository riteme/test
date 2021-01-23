macro_rules! print_result {
    ($expression:expr) => {
        println!("{} = {:?}", stringify!($expression), $expression);
    };
}

macro_rules! find_min {
    {$x:expr} => ($x);
    {$x:expr, $($y:expr), +} => {
        std::cmp::min($x, find_min!($($y), +))
    }
}

fn main() {
    print_result!(1 + 1);
    print_result!({
        let x = 1;
        x + 1
    });
    print_result!(find_min! {9, 5, 3, 7});
}
