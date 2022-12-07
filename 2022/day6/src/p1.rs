use std::collections::{HashSet, VecDeque};
use std::fs::File;
use std::io::{BufRead, BufReader};

const QUEUE_UNIQUE_LENGTH: usize = 4;

fn has_repeated_entries(queue: &VecDeque<char>) -> bool {
    let mut uniq = HashSet::new();
    queue.into_iter().all(move |x| uniq.insert(x))
}

fn add_character(queue: &mut VecDeque<char>, character: char) {
    if queue.len() == QUEUE_UNIQUE_LENGTH {
        queue.pop_front();
    }

    queue.push_back(character);
}

fn is_unique(queue: &VecDeque<char>) -> bool {
    if queue.len() != QUEUE_UNIQUE_LENGTH {
        false
    }
    else {
        has_repeated_entries(queue)
    }
}

pub fn run() {
    let file = File::open("day6.txt").unwrap();
    let reader = BufReader::new(file);

    let mut line_result = reader.lines();
    let line_binding = line_result.next().unwrap().unwrap();
    let line = line_binding.chars();

    let mut queue: VecDeque<char> = VecDeque::with_capacity(4);

    for (index, character) in line.enumerate() {
        add_character(&mut queue, character);

        if is_unique(&queue) {
            println!("{}", index + 1);
            return;
        }
    }
}
