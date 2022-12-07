use std::collections::HashMap;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn make_location(paths: &Vec<String>, location: &str) -> String {
    let latest = match paths.last() {
        None => "",
        Some(loc) => loc
    };

    [latest, "/", location].join("")
}

fn add_size_to_folder(folders: &mut HashMap<String, u32>, folder: &String, value: u32) {
    if let Some(existent_value) = folders.get_mut(folder) {
        *existent_value += value;
    }
    else {
        folders.insert(folder.clone(), value);
    }
}

pub fn run() {
    let file = File::open("day7.txt").unwrap();
    let reader = BufReader::new(file);

    let mut folders: HashMap<String, u32> = HashMap::new();
    let mut paths: Vec<String> = Vec::new();

    for line_result in reader.lines() {
        let line = line_result.unwrap();
        let command = &line[..4];

        match command {
            "$ ls" | "dir " => (), //we dont need these
            "$ cd" => {
                let location = &line[5..];

                if location == ".." {
                    paths.pop();
                }
                else {
                    paths.push(make_location(&paths, location));
                }
            },
            _ => {
                let string_size = &line[..line.find(" ").unwrap()];
                let size: u32 = string_size.parse().unwrap();

                for path in &paths {
                    add_size_to_folder(&mut folders, path, size);
                }
            }
        }
    }

    let mut smallest_to_delete_for_space = u32::MAX; //the path that we will delete
    let available_space = 70000000 - folders["//"]; //get available space

    for (_key, value) in folders {
        if available_space + value > 30000000 { //if we delete said folder, we need to have at least 30000000
            if value < smallest_to_delete_for_space { //if folder is smaller than the previous one
                smallest_to_delete_for_space = value;
            }
        }
    }

    println!("{:?}", smallest_to_delete_for_space);
}
