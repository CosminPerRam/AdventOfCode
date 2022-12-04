
use std::fs::File;
use std::io::{BufRead, BufReader};

fn check_overlap(first_start: &u32, first_end: &u32, second_start: &u32, second_end: &u32) -> bool {
    if first_start >= second_start && first_end <= second_end {
        true
    }
    else if second_start >= first_start && second_end <= first_end {
        true
    }
    else {
        false
    }
}

pub fn run() {
    let file = File::open("day4.txt").unwrap();
    let reader = BufReader::new(file);

    let mut number_of_overlapped_jobs: u32 = 0;

    for line_result in reader.lines() {
        let line = line_result.unwrap();

        let groups = line.split(",").collect::<Vec<&str>>();
        let first = groups[0].split("-").collect::<Vec<&str>>();
        let second = groups[1].split("-").collect::<Vec<&str>>();

        let first_start: u32 = first[0].parse().unwrap();
        let first_end: u32 = first[1].parse().unwrap();
        let second_start: u32 = second[0].parse().unwrap();
        let second_end: u32 = second[1].parse().unwrap();

        number_of_overlapped_jobs += check_overlap(&first_start, &first_end, &second_start, &second_end) as u32;
    }

    println!("{number_of_overlapped_jobs}");
}
