use std::collections::VecDeque;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn add_to_stacks(stacks: &mut Vec<VecDeque<char>>, character: char, index: usize) {
    if index >= stacks.len() {
        stacks.push(VecDeque::new());
        add_to_stacks(stacks, character, index);
    }
    else {
        stacks[index].push_front(character);
    }
}

fn process_command(stacks: &mut Vec<VecDeque<char>>, count: usize, from: usize, to: usize) {
    for _ in 0..count {
        let character = stacks[from].pop_back().unwrap();
        stacks[to].push_back(character);
    }
}

pub fn run() {
    let file = File::open("day5.txt").unwrap();
    let reader = BufReader::new(file);

    let mut parsing_starting_stacks = true;
    let mut stacks: Vec<VecDeque<char>> = Vec::new();

    for line_result in reader.lines() {
        let line = line_result.unwrap();

        if line.len() == 0 {
            parsing_starting_stacks = false;
            continue;
        }

        if parsing_starting_stacks {
            for (index, character) in line.chars().enumerate() {
                if character < 'A' as char || character > 'Z' as char {
                    continue;
                }

                add_to_stacks(&mut stacks, character, index / 4);
            }
        }
        else {
            let line_without_letters = line.replace(&['m', 'o', 'v', 'e', 'f', 'r', 't'][..], "");
            let numbers = line_without_letters.split_whitespace().collect::<Vec<&str>>();

            let count: usize = numbers[0].parse().unwrap();
            let from = numbers[1].parse::<usize>().unwrap() - 1;
            let to = numbers[2].parse::<usize>().unwrap() - 1;

            process_command(&mut stacks, count, from, to);
        }
    }

    for stack in stacks {
        print!("{}", stack.back().unwrap());
    }

    println!();
}
