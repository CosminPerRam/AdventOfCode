use std::fs::File;
use std::io::{BufRead, BufReader};

fn add_value(values: &mut Vec<i32>, value: i32) {
    values.push(value);
}

pub fn run() {
    let file = File::open("day10.txt").unwrap();
    let reader = BufReader::new(file);

    let mut x: i32 = 1;
    let mut signals: Vec<i32> = vec![0, 0]; //wtf? needs investigation

    for line_result in reader.lines() {
        let line = line_result.unwrap();

        let command = &line[0..4];

        add_value(&mut signals, x);

        if command == "addx" {
            let value: i32 = line[5..].parse().unwrap();
            x += value;
            add_value(&mut signals, x);
        }
    }

    let mut sum = 0;
    for i in 0..6 {
        let cycle = 20 + 40 * i;
        let value = signals[cycle] * cycle as i32;
        sum += value;
    }

    println!("{sum}");
}
