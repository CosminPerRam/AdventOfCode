
use std::fs::File;
use std::io::{BufRead, BufReader};

fn get_common_letter(first: &str, second: &str) -> u8 {
    let mut apperances_first: Vec<u8> = vec![0; 58];
    let mut apperances_second: Vec<u8> = vec![0; 58];

    for character in first.as_bytes() {
        apperances_first[(character - 65) as usize] += 1;
    }

    for character in second.as_bytes() {
        apperances_second[(character - 65) as usize] += 1;
    }

    for i in 0..58 {
        if apperances_first[i] > 0 && apperances_second[i] > 0 {
            return (i + 65) as u8;
        }
    }

    panic!("Common letter not existent!");
}

fn get_priority(character: u8) -> u32 {
    if character > 96 && character < 123 {
        return (character - 96) as u32;
    }
    else if character > 64 && character < 91 {
        return (character - 64 + 26) as u32;
    }

    panic!("Invalid character")
}

pub fn run() {
    let file = File::open("day3.txt").unwrap();
    let reader = BufReader::new(file);

    let mut score: u32 = 0;

    for line_result in reader.lines() {
        let line = line_result.unwrap();

        let (first, second) = line.split_at(line.len() / 2);
        let common_letter = get_common_letter(first, second);

        score += get_priority(common_letter);
    }

    println!("{score}");
}
