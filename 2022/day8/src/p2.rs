use std::fs::File;
use std::io::{BufRead, BufReader};

// there is a bit of matrix orientation fuckery around here

fn get_score(trees: &Vec<Vec<u8>>, x: usize, y: usize) -> u32 {
    let width = trees[0].len();
    let height = trees.len();

    let tree = trees[y][x];

    let mut left_score = 0;
    for left_x in (0..x).rev() {
        left_score += 1;
        if trees[y][left_x] >= tree {
            break;
        }
    }

    let mut right_score = 0;
    for right_x in (x + 1)..width {
        right_score += 1;
        if trees[y][right_x] >= tree {
            break;
        }
    }

    let mut up_score = 0;
    for up_y in (0..y).rev() {
        up_score += 1;
        if trees[up_y][x] >= tree {
            break;
        }
    }

    let mut down_score = 0;
    for down_y in (y+1)..height {
        down_score += 1;
        if trees[down_y][x] >= tree {
            break;
        }
    }

    left_score * right_score * up_score * down_score
}

pub fn run() {
    let file = File::open("day8.txt").unwrap();
    let reader = BufReader::new(file);

    let mut grid: Vec<Vec<u8>> = Vec::new();

    for line_result in reader.lines() {
        let line = line_result.unwrap();
        grid.push(line.as_bytes().iter().map(|character| character - ('0' as u8)).collect())
    }

    let width = grid[0].len();
    let height = grid.len();

    let mut highest_score = 0;
    for x in 1..(width - 1) {
        for y in 1..(height - 1) {
            let tree_score = get_score(&grid, x, y);
            if tree_score > highest_score {
                highest_score = tree_score;
            }
        }
    }

    println!("{highest_score}");
}
