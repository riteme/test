use std::mem;

fn apply<F>(f: F)
where
    F: FnOnce(),
{
    f();
}

fn apply_3<F>(f: F) -> i32
where
    F: Fn(i32) -> i32,
{
    f(3)
}

fn create_fnonce() -> impl FnOnce() {
    let text = "FnOnce".to_owned();
    move || println!("{}", text)
}

static mut GLOBAL_COUNT: i32 = 0;

fn apply_fn<F>(f: F)
where
    F: Fn() -> (),
{
    f();
}

fn foo() {
    unsafe {
        GLOBAL_COUNT += 1;
    }
}

unsafe fn _bar() {
    GLOBAL_COUNT += 1;
}

fn main() {
    apply_fn(foo);
    // apply_fn(_bar);
    unsafe {
        println!("GLOBAL_COUNT={}", GLOBAL_COUNT);
    }

    let fn_once = create_fnonce();
    fn_once();
    // fn_once();

    // what closure does determines what type of it, not how it captures values.
    // https://doc.rust-lang.org/std/keyword.move.html
    let y = Box::new(4);
    let square = move |x| x * *y;
    println!("{}", apply_3(square));
    // println!("{}", y);

    let z = String::from("hello");
    let greet = move |x| {
        println!("{}: {}", z, x);
        x
    };
    println!("{}", apply_3(greet));
    // println!("{}", z);

    let c1 = |i: i32| i + 1;
    let c2 = |i| i + 1;
    println!("{}, {}", c1(1), c2(2));

    let one = || 1;
    println!("{}", one());

    let color = String::from("green");
    let print = || println!("{}", color);

    print();

    let _reborrow = &color;
    print();

    let _moved = color;
    // print();

    let mut count = 0;
    let mut inc = || {
        count += 1;
        println!("count={}", count);
    };
    inc();
    let _reborrow = &mut count;
    // inc();

    let movable = Box::new(3);

    let consume = || {
        println!("{}", movable);
        mem::drop(movable);
    };

    consume();
    // consume();

    let heystack = vec![1, 2, 3, 4];
    let contains = move |needle| heystack.contains(&needle);
    println!("{}", contains(1));
    println!("{}", contains(56));
    // println!("len={}", heystack.len());

    let color = String::from("red");
    let diary = || {
        println!("color={}", color);
        mem::drop(color);
    };
    apply(diary);

    let sum = (0..)
        .map(|n| n * n)
        .take_while(|&a| a < 1000)
        .filter(|a| a % 2 == 1)
        .fold(0, |acc, a| acc + a);
    println!("sum={}", sum);
}
