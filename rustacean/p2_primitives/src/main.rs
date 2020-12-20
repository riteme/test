use std::{fmt, mem};

struct Matrix(f64, f64, f64, f64);

impl fmt::Display for Matrix {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "( {}, {} )\n", self.0, self.1)?;
        write!(f, "( {}, {} )", self.2, self.3)
    }
}

impl Matrix {
    fn transpose(&self) -> Matrix {
        Matrix(self.0, self.2, self.1, self.3)
    }
}

fn analyze(slice: &[i32]) {
    println!("first element: {}", slice[0]);
    println!("# of elements: {}", slice.len());
}

fn main() {
    let long_tuple = (1, 2, 3, 4);
    println!("{:?}", long_tuple);
    let (a, _, b, ..) = long_tuple;
    println!("{} {}", a, b);

    let mat = Matrix(1.1, 1.2, 2.1, 2.2);
    println!("{}", mat);
    println!("{}", mat.transpose());

    let xs: [i32; 5] = [1, 2, 3, 4, 5];
    let ys: [i32; 500] = [0; 500];
    println!("memory used by ys: {}", mem::size_of_val(&ys));
    analyze(&xs);
    analyze(&ys);
    analyze(&ys[1..4]);
}
