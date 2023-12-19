// if there number is from index i to i+n, if there is any symbol on i-1, i+n+1, j-1 to j+n+1, k-1 to k+n+1, then the number of valis
// j is i but in the next line
// k is i but in previous line

use std::collections::BTreeMap;
use std::iter::FlatMap;

enum Value {
    Symbol(char),
    Empty,
    Number(u32),
} // we use it to match


fn main(){
    let input = include_str!("./input.txt");
    let output = process(input);
    
}

// fn process( input: &str, ) -> String {
//     let map = input.lines().enumerate().flat_map(|(y_index, line)|{
//         line.chars().enumerate().map(move |(x_index, char)| {
//             (x_index, y_index) = 
//             match character {
//                 '.' => Value::Empty,
//                 c if c.is_ascii_digit() => {
//                     Value::Number(c.to_digit(10).expect("Should be a number"))
//                 },
//                 c => Value::Symbol(c),
//             }

//         })
//     }).collect::<BTreeMap<(usize, usize), Value>>();
//     // we now have a map of coordinates and the corresponding value at the corrdinate

//     // we now need to find the valid numbers
//     let mut valid_numbers = Vec::new();
//     for ((x, y), value) in map.iter() {
//         if let Value::Number(number) = value {
//             let mut valid = true;
//             for i in x-1..=x+1 {
//                 for j in y-1..=y+1 {
//                     if let Some(Value::Symbol(_)) = map.get(&(i, j)) {
//                         valid = false;
//                         break;
//                     }
//                 }
//             }
//             if valid {
//                 valid_numbers.push(number);
//             }
//         }
//     }

//     // now we need to find the sum of the values in valid_numbers
//     let sum = valid_numbers.iter().sum::<u32>();
//     sum.to_string()

// }
pub fn process(
    input: &str,
) -> Result<String, &std::error::Error> {
    // sum part numbers
    let map = input
        .lines()
        .enumerate()
        .flat_map(|(y, line)| {
            line.chars().enumerate().map(
                move |(x, character)| {
                    (
                (y as i32,x as i32),
                match character {
                    '.' => Value::Empty,
                    c if c.is_ascii_digit() => {
                        Value::Number(
                            c.to_digit(10).expect(
                                "should be a number",
                            ),
                        )
                    }
                    c => Value::Symbol(c),
                },
            )
                },
            )
        })
        .collect::<BTreeMap<(i32, i32), Value>>();

    // we now have a map of coordinates and the corresponding value at the coordinate

    let mut numbers: Vec<Vec<((i32, i32), u32)>> = vec![];
    for ((y, x), value) in map.iter() {
        if let Value::Number(num) = value {
            match numbers.iter().last() {
                Some(v) => {
                    let last_num = v.iter().last();
                    match last_num {
                        Some(((last_num_x, _), _)) => {
                            if last_num_x + 1 == *x {
                                let last = numbers
                                    .iter_mut()
                                    .last()
                                    .expect("should exist");
                                last.push(((*x, *y), *num));
                            } else {
                                numbers.push(vec![(
                                    (*x, *y),
                                    *num,
                                )]);
                            }
                        }
                        None => unimplemented!(
                            "shouldn't happen"
                        ),
                    }
                }
                None => {
                    numbers.push(vec![((*x, *y), *num)]);
                }
            }
        }
    }

    // map: entire grid
    // numbers: sequential numbers
    let mut total = 0;
    for num_list in numbers {
        // (x,y)
        let positions = [
            (1, 0),
            (1, -1),
            (0, -1),
            (-1, -1),
            (-1, 0),
            (-1, 1),
            (0, 1),
            (1, 1),
        ];
        let num_positions: Vec<(i32, i32)> = num_list
            .iter()
            .map(|((y, x), _)| (*x, *y))
            .collect();
        let pos_to_check: Vec<(i32, i32)> = num_list
            .iter()
            .flat_map(|(pos, _)| {
                positions.iter().map(|outer_pos| {
                    // outer_pos.x + pos.x, .y + .y
                    (
                        outer_pos.0 + pos.1,
                        outer_pos.1 + pos.0,
                    )
                })
            })
            .unique()
            .filter(|num| !num_positions.contains(num))
            .collect();

        // dbg!(pos_to_check.len(), pos_to_check);
        let is_part_number =
            pos_to_check.iter().any(|pos| {
                let value = map.get(pos);
                #[allow(clippy::match_like_matches_macro)]
                if let Some(Value::Symbol(_)) = value {
                    true
                } else {
                    false
                }
            });

        if is_part_number {
            total += num_list
                .iter()
                .map(|(_, num)| num.to_string())
                .collect::<String>()
                .parse::<u32>()
                .unwrap()
        }
    }

    Ok(total.to_string())
}

