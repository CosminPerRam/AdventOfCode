use std::fs::File;
use std::io::{BufRead, BufReader};

// there is a bit of matrix orientation fuckery around here

fn is_visible(trees: &Vec<Vec<u8>>, x: usize, y: usize) -> bool {
    let width = trees[0].len();
    let height = trees.len();

    let tree = trees[y][x];

    let mut is_highest = true;
    for left_x in 0..x {
        if trees[y][left_x] >= tree {
            is_highest = false;
            break;
        }
    }

    if is_highest {
        return true;
    }

    is_highest = true;
    for right_x in (x + 1)..width {
        if trees[y][right_x] >= tree {
            is_highest = false;
            break;
        }
    }

    if is_highest {
        return true;
    }

    is_highest = true;
    for up_y in 0..y {
        if trees[up_y][x] >= tree {
            is_highest = false;
            break;
        }
    }

    if is_highest {
        return true;
    }

    is_highest = true;
    for down_y in (y+1)..height {
        if trees[down_y][x] >= tree {
            is_highest = false;
            break;
        }
    }

    if is_highest {
        return true;
    }

    false
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

    let mut total: u32 = (width * 2 + (height - 2) * 2) as u32;
    for x in 1..(width - 1) {
        for y in 1..(height - 1) {
            total += is_visible(&grid, x, y) as u32;
        }
    }

    println!("{total}");
}
