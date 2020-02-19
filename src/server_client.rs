#[macro_use]
extern crate lazy_static;
extern crate futures;
extern crate rand;
extern crate serde_json;




pub use rand::prelude::*;
pub use std::net::*;
pub use std::io::*;
pub use futures::prelude::*;
pub use std::collections::*;
pub use std::sync::*;
pub use std::thread::*;

pub mod server_state;
pub mod card;
pub mod game;
use server_state::*;

lazy_static! {
    static ref SERVER: Mutex<Option<ServerState>> = Mutex::from(None);
}


//This is C code
extern "C" {
    fn hello_c();
}

//This is Rust code visible for binding in C
#[no_mangle]
pub extern fn foo() {
    println!("hello from Rust. Binding test.");
    unsafe {
        hello_c();
    }
}

#[no_mangle]
pub extern fn bye() {
    println!("Deconstruction of the server object. Hello from Rust btw.")
}

#[no_mangle]
pub extern fn init_server() {
    let s = SERVER.lock().unwrap();
}

#[no_mangle]
pub extern fn drop_server() {

}