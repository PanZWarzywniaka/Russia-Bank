
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