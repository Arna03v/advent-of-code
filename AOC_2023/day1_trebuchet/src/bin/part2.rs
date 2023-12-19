use std::{io, thread::sleep};

fn sum(array : &Vec<u32>) -> u32 {
    let mut sum = 0;
    for element in array {
        sum += element;
    }

    sum
}

fn process_string(string : &str) -> u32{
    // let mut index = 0;
    let mut it = (0..string.len()).filter_map(|index| {
        let reduced_line = &string[index..];
        let result = if reduced_line.starts_with("one") {
            '1'
        } else if reduced_line.starts_with("two") {
            '2'
        } else if reduced_line.starts_with("three") {
            '3'
        } else if reduced_line.starts_with("four") {
            '4'
        } else if reduced_line.starts_with("five") {
            '5'
        } else if reduced_line.starts_with("six") {
            '6'
        } else if reduced_line.starts_with("seven") {
            '7'
        } else if reduced_line.starts_with("eight") {
            '8'
        } else if reduced_line.starts_with("nine") {
            '9'
        } else {
            reduced_line.chars().next().unwrap()
        };

        result.to_digit(10)
    });
    let first = it.next().expect("should be a number");

    match it.last() {
        Some(num) => format!("{first}{num}"),
        None => format!("{first}{first}"),
    }
    .parse::<u32>()
    .expect("should be a valid number")

    
    
}

fn main(){
    let input = include_str!("./input1.txt");
    let output = process(input);
    dbg!(output);
}


fn process(input : &str) -> u32 {
    let mut calibration_values : Vec<u32> = Vec::new();
    for string in input.lines() {
        let number = process_string(string);       
        

        calibration_values.push(number);              

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
        assert_eq!(result, 67);
    }
}