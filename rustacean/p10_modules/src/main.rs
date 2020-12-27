mod my_mod {
    fn private_function() {
        println!("private");
    }

    pub fn function() {
        private_function();
    }

    pub mod nested {
        pub fn function() {
            println!("nested");
        }

        pub(in crate::my_mod) fn public_in_my_mod() {
            println!("aha!");
        }
    }

    pub mod private {
        pub(crate) fn aha() {
            println!("emmm...");
        }
    }
}

use my_mod::private::aha as emm;

fn main() {
    my_mod::private::aha();
    emm();
}
