
use anyhow::Error;
use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn run() -> Result<(), Error> {
    let file = File::open("day1.txt")?;
    let reader = BufReader::new(file);

    let mut elfs: Vec<u32> = Vec::new();
    let mut total: u32 = 0;

    for line_result in reader.lines() {
        let line = line_result?;
        if line.is_empty() {
            elfs.push(total);
            total = 0;
        }
        else {
            total = total + line.parse::<u32>()?;
        }
    }

    elfs.push(total);

    let max_value = elfs.iter().max();

    println!("{:?}", max_value);

    Ok(())
}
