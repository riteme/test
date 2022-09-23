use futures::executor::block_on;

async fn hello_world() {
    println!("Hello, world!");
}

async fn wrapper() {
    hello_world().await;
}

fn main() {
    let f = wrapper();
    block_on(f);
}
