// to run : cargo run --bin part1

use std::{io, thread::sleep};

fn sum(array : &Vec<u32>) -> u32 {
    let mut sum = 0;
    for element in array {
        sum += element;
    }

    sum
}

fn main(){
    let input = include_str!("./input1.txt");
    let output = process(input);
    dbg!(output);
}

fn process(input : &str) -> u32 {
    let mut calibration_values : Vec<u32> = Vec::new();
    for string in input.lines(){
        let calibration_value;


        let mut iterator = string.chars().filter_map(|character| {
            character.to_digit(10)
        }); // we now have the string full of numbers, we have removed the characters

        let first : u32= iterator.next().expect("should be a number");
        let last : Option<u32> = iterator.last(); // as this one might not exist

        match last {
            Some(num) => calibration_value = format!("{first}{num}"),
            None => calibration_value = format!("{first}{first}"),
        };

        calibration_values.push(calibration_value.parse::<u32>().unwrap());              

    }    
    let res = sum(&calibration_values);


    return res
}

#[cfg(test)]
mod tests {
    use super::*;


    #[test]
    fn it_works() {
        let result = process("sixsrvldfour4seven");
        assert_eq!(result, 44);
    }
}