
#[no_mangle]
pub extern fn foo() {
    println!("hello from Rust. Binding test.")
}

#[no_mangle]
pub extern fn bye() {
    println!("Deconstruction of the server object. Hello from Rust btw.")
}