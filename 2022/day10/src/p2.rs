use std::fs::File;
use std::io::{BufRead, BufReader};

fn add_value(values: &mut Vec<i32>, value: i32) {
    values.push(value);
}

fn is_inside(value: i32, target: i32) -> bool {
    value > target - 2 && value < target + 2
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

    for line in 0..6 {
        for column in 0..40 {
            let cycle = line * 40 + column;

            if is_inside(column, signals[cycle as usize + 1]) {
                print!("#");
            }
            else {
                print!(".");
            }
        }
        println!();
    }
}
