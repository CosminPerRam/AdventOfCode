
use anyhow::Error;
use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn run() -> Result<(), Error> {
    let file = File::open("day1e.txt")?;
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

    // Because there isnt a newline at the end
    elfs.push(total);

    // An alternative here would be sorting the vector, then sum the last 3 elements with
    // elfs[elfs.len() - 3..].iter().sum()
    let mut c = 0; let mut b = 0; let mut a = 0;
    for elf in elfs {
        if elf > a {
            c = b;
            b = a;
            a = elf;
        }
        else if elf > b {
            c = b;
            b = elf;
        }
        else if elf > c {
            c = elf;
        }
    }

    let last_three_total: u32 = a + b + c;

    println!("{last_three_total}");

    Ok(())
}
