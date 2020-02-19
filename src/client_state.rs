use crate::*;

pub struct ClientState {
    comm_thread : Option<JoinHandle<()>>
}

impl ClientState {
    pub fn new() -> Self {
        println!("ClientState: New instance");
        Self {
            comm_thread : Some(spawn(move || {
                /*
                for n in 0..50 {
                    println!("It's the server thread! {}",n);
                    sleep(std::time::Duration::from_millis(100));
                }
                */
            }))
        }
    }
}

impl Drop for ClientState {
    fn drop(&mut self) {
        let comm_thread = self.comm_thread.take();
        comm_thread.unwrap().join().unwrap();
        println!("ClientState: Deconstruction");
    }
}