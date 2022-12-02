
use std::fs::File;
use std::io::{BufRead, BufReader};

enum RPS { Rock, Paper, Scissors }

fn response_to_rps(number: u8) -> RPS {
    match number {
        88 => RPS::Rock,
        89 => RPS::Paper,
        90 => RPS::Scissors,
        _ => panic!("wrong response number")
    }
}

fn response_points(response: &RPS) -> u32 {
    match response {
        RPS::Rock => 1,
        RPS::Paper => 2,
        RPS::Scissors => 3
    }
}

fn opponent_to_rps(number: u8) -> RPS {
    match number {
        65 => RPS::Rock,
        66 => RPS::Paper,
        67 => RPS::Scissors,
        _ => panic!("wrong opponent number")
    }
}

fn match_outcome_points(opponent: RPS, response: RPS) -> u32 {
    match (opponent, response) {
        (RPS::Rock, RPS::Rock) => 3,
        (RPS::Rock, RPS::Paper) => 6,
        (RPS::Rock, RPS::Scissors) => 0,
        (RPS::Paper, RPS::Rock) => 0,
        (RPS::Paper, RPS::Paper) => 3,
        (RPS::Paper, RPS::Scissors) => 6,
        (RPS::Scissors, RPS::Rock) => 6,
        (RPS::Scissors, RPS::Paper) => 0,
        (RPS::Scissors, RPS::Scissors) => 3,
    }
}

pub fn run() {
    let file = File::open("day2.txt").unwrap();
    let reader = BufReader::new(file);

    let mut score: u32 = 0;

    for line_result in reader.lines() {
        let line = line_result.unwrap();
        let line_bytes = line.as_bytes();

        let opponent = opponent_to_rps(line_bytes[0]);
        let response = response_to_rps(line_bytes[2]);

        let response_points = response_points(&response);
        let match_points_outcome = match_outcome_points(opponent, response);

        score = score + response_points + match_points_outcome;
    }

    println!("{score}");
}
