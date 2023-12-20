// make a struct card having 2 fields, cards_we_have and winning_cards
// parse the input and store everything in a hashset of cards. Use hashets instead of vectors as additions are faster
// for eah card, check how many hits (work on this logic)
// can do the intersection of the two hashets to get the number of hits
// store the sum in res vector
// sum the res vector and print it

// we use nom as a parser

use std::collections::HashSet;

use nom::{
    bytes::complete::tag,
    character::complete::{
        self, digit1, line_ending, space0, space1,
    },
    multi::{fold_many1, separated_list1},
    sequence::{
        delimited, separated_pair, terminated, tuple,
    },
    IResult, Parser,
};

#[derive(Debug)]
struct Card {
    winning_numbers: HashSet<u32>,
    numbers_we_have: HashSet<u32>,
}

impl Card {
    // to get the score of each card
    fn score(&self) -> u32{
        let power = self.winning_numbers.intersection(&self.numbers_we_have).count() as u32;
        if power == 0 {
            0
        } else {
            2u32.pow(power-1)
        }

    }
}

fn set(input : &str) -> IResult<&str, HashSet<u32>>{
    // to make set of the left and right halves of the card
    fold_many1( // we are iterating multipel times over the data type y32 that ends with a space0 (min spaces after complettion == 0)
        terminated(complete::i32, space0),
        HashSet::new, // we create a hashset to put the values into
        |mut acc: HashSet<_>, item| {
            acc.insert(item as u32); // ervytime we come across such a value, we insert it into the hashset
            acc
        },
    ) (input)

}

fn card(input : &str)-> IResult<&str, Card>{
    let (input, _) = delimited(tuple((tag("Card"),space1)) , digit1, tuple((tag(":"), space1)))(input)?;
    separated_pair(set, tuple((tag("|"), space1)), set).map(|(winning_numbers, numbers_we_have)| Card{
        winning_numbers,
        numbers_we_have
    }).parse(input)
}

fn cards(input : &str) -> IResult<&str, Vec<Card>> {
    // to separate the input into cards
    
    separated_list1(line_ending, card)(input)   
    
}

fn main(){
    let input = include_str!("input.txt");
    let (_, card_data) = cards(&input).expect("parsing is valid");
    let result = card_data.iter().map(|card| card.score()).sum::<u32>();

    println!("The result is {}", result);

    
}