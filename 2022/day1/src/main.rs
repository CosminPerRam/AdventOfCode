use anyhow::Error;

mod p1;
mod p2;

fn main() -> Result<(), Error> {
    p1::run()?;
    p2::run()?;

    Ok(())
}
