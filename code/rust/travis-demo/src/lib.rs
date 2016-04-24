#![crate_name = "travisdemo"]
#![crate_type = "lib"]

//! This is a comment

/// This function always returns true.  It's very useful!
pub fn always_true() -> bool { true }

#[test]
fn it_works() {
    assert_eq!(always_true(), true);
}
