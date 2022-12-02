
use std::fs::File;
use std::io::{BufRead, BufReader};

enum RPS { Rock, Paper, Scissors }
enum Condition { Lose, Tie, Win }

fn response_to_condition(number: u8) -> Condition {
    match number {
        89 => Condition::Tie,
        88 => Condition::Lose,
        90 => Condition::Win,
        _ => panic!("wrong condition number")
    }
}

fn response_to_calculated_rps(opponent: &RPS, condition: &Condition) -> RPS {
    match (opponent, condition) {
        (RPS::Rock, Condition::Lose) => RPS::Scissors,
        (RPS::Rock, Condition::Tie) => RPS::Rock,
        (RPS::Rock, Condition::Win) => RPS::Paper,
        (RPS::Paper, Condition::Lose) => RPS::Rock,
        (RPS::Paper, Condition::Tie) => RPS::Paper,
        (RPS::Paper, Condition::Win) => RPS::Scissors,
        (RPS::Scissors, Condition::Lose) => RPS::Paper,
        (RPS::Scissors, Condition::Tie) => RPS::Scissors,
        (RPS::Scissors, Condition::Win) => RPS::Rock,
    }
}

fn response_points(response: RPS) -> u32 {
    match response {
        RPS::Rock => 1,
        RPS::Paper => 2,
        RPS::Scissors => 3
    }
}

fn condition_points(condition: Condition) -> u32 {
    match condition {
        Condition::Lose => 0,
        Condition::Tie => 3,
        Condition::Win => 6
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

pub fn run() {
    let file = File::open("day2.txt").unwrap();
    let reader = BufReader::new(file);

    let mut score: u32 = 0;

    for line_result in reader.lines() {
        let line = line_result.unwrap();
        let line_bytes = line.as_bytes();

        let opponent = opponent_to_rps(line_bytes[0]);
        let response_condition = response_to_condition(line_bytes[2]);

        let response = response_to_calculated_rps(&opponent, &response_condition);

        let response_points = response_points(response);
        let match_points_outcome = condition_points(response_condition);

        score = score + response_points + match_points_outcome;
    }

    println!("{score}");
}
