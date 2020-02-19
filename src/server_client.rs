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

pub mod client_state;
pub mod card;
pub mod game;
use client_state::*;

lazy_static! {
    static ref SERVER: Mutex<Option<ClientState>> = Mutex::from(None);
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
pub extern fn init_server() {
    let mut s = SERVER.lock().unwrap();
    *s = Some(ClientState::new());
}

#[no_mangle]
pub extern fn drop_server() {
    let mut s = SERVER.lock().unwrap();
    *s = None;
}