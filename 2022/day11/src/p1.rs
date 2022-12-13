use std::collections::VecDeque;
use std::fs::File;
use std::io::{BufRead, BufReader};

#[derive(Debug, Clone)]
enum OperationKind {
    Addition,
    Multiplication
}

impl OperationKind {
    pub fn from(value: &str) -> Self {
        match value {
            "+" => OperationKind::Addition,
            "*" => OperationKind::Multiplication,
            _ => panic!("bad symbol!")
        }
    }
}

#[derive(Debug, Clone)]
struct Monkey {
    pub items: VecDeque<u32>,
    pub operation_kind: OperationKind,
    pub operation_value: Option<u32>,
    pub test_divisible: u32,
    pub test_true_to_monkey: usize,
    pub test_false_to_monkey: usize,
    pub inspects: usize
}

pub fn run() {
    let file = File::open("day11.txt").unwrap();
    let reader = BufReader::new(file);

    let mut monkeys = Vec::new();

    let mut starting_items = VecDeque::new();
    let mut operation_kind = OperationKind::Addition;
    let mut operation_value = None;
    let mut test_divisible = 0;
    let mut test_true_to_monkey = 0;
    let mut test_false_to_monkey = 0;

    for line_result in reader.lines() {
        let line = line_result.unwrap();

        if line.is_empty() {
            monkeys.push(Monkey {
                items: starting_items.clone(),
                operation_kind: operation_kind.clone(),
                operation_value,
                test_divisible,
                test_true_to_monkey,
                test_false_to_monkey,
                inspects: 0
            });

            continue;
        }

        if &line[..6] == "Monkey" {
            continue;
        }

        if &line[..18] == "  Starting items: " {
            starting_items = line[18..].split(", ")
                .map(|v| v.parse::<u32>().unwrap())
                .collect();

            continue;
        }

        if &line[..21] == "  Test: divisible by " {
            test_divisible = line[21..].parse().unwrap();

            continue;
        }

        if &line[..23] == "  Operation: new = old " {
            operation_kind = OperationKind::from(&line[23..24]);

            let operation_value_string = &line[25..];
            operation_value = match operation_value_string {
                "old" => None,
                _ => Some(operation_value_string.parse().unwrap())
            };

            continue;
        }

        if &line[..29] == "    If true: throw to monkey " {
            test_true_to_monkey = line[29..].parse().unwrap();

            continue;
        }

        if &line[..30] == "    If false: throw to monkey " {
            test_false_to_monkey = line[30..].parse().unwrap();

            continue;
        }
    }

    monkeys.push(Monkey {
        items: starting_items.clone(),
        operation_kind: operation_kind.clone(),
        operation_value,
        test_divisible,
        test_true_to_monkey,
        test_false_to_monkey,
        inspects: 0
    });

    let rounds = 20;

    for _ in 0..rounds {
        for monkey_index in 0..monkeys.len() {
            let monkey = monkeys[monkey_index].clone();
            for item in &monkey.items {
                let applied_value = match monkey.operation_value {
                    Some(v) => v,
                    None => *item
                };

                let mut new_value = *item;

                match monkey.operation_kind {
                    OperationKind::Addition => new_value += applied_value,
                    OperationKind::Multiplication => new_value *= applied_value
                }

                new_value /= 3;

                if new_value % monkey.test_divisible == 0 { //it is divisible
                    monkeys[monkey.test_true_to_monkey].items.push_back(new_value);
                }
                else { //it is not
                    monkeys[monkey.test_false_to_monkey].items.push_back(new_value);
                }
            }

            monkeys[monkey_index] = Monkey {
                items: VecDeque::new(),
                operation_kind: monkey.operation_kind,
                operation_value: monkey.operation_value,
                test_divisible: monkey.test_divisible,
                test_true_to_monkey: monkey.test_true_to_monkey,
                test_false_to_monkey: monkey.test_false_to_monkey,
                inspects: monkey.inspects + monkey.items.len()
            }
        }
    }

    monkeys.sort_by(|a, b| b.inspects.cmp(&a.inspects));

    let monkey_business = monkeys[0].inspects * monkeys[1].inspects;
    println!("{monkey_business}");
}
