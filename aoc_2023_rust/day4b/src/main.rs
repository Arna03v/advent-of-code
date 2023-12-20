// make a struct card having 2 fields, cards_we_have and winning_cards
// parse the input and store everything in a hashset of cards. Use hashets instead of vectors as additions are faster
// for eah card, check how many hits (work on this logic)
// can do the intersection of the two hashets to get the number of hits
// store the sum in res vector
// sum the res vector and print it

// we use nom as a parser

use std::collections::{HashSet,BTreeMap};

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
    // fn score(&self) -> u32{
    //     let power = self.matches() as u32;
    //     if power == 0 {
    //         0
    //     } else {
    //         2u32.pow(power-1)
    //     }

    // }
    
    // as we use the number of matches instead of the powers of 2 for numbre of matches in this question
    fn matches(&self) -> usize{
        self.winning_numbers.intersection(&self.numbers_we_have).count()
    
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
    let (_, card_data) = cards(&input).expect("parsing is valid"); // card data is storing struct card for each index in a vec
    let data = card_data.iter().map(|card| card.matches()).collect::<Vec<_>>(); // storing number of matches of each card in a vec

    let store = (0..card_data.len())
        .map(|index| (index,1))
        .collect::<BTreeMap<usize, u32>>(); // each index is mapped to 1 in a BTreeMap. {0: 1, 1: 1, 2: 1, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1} and so on
    // will be used as number of iterations once we increment the value appropriately

    // we use enumerate to get the index of each element in the vec, in this case, the card number
    // which means after the above line, we have one of every card

    let result = data
        .iter()
        .enumerate()
        .fold(store, |mut acc, (index, num_of_matches)| { // card_score is the number of matches
            let to_add = *acc.get(&index).unwrap();  // we get the number of cards of the current card. so if we are working with C1 and want to increment 2 and 3, if we have 2 C1 we need to it twice, so here we are storing the value of 2 from 2 C1
            for i in (index + 1) .. (index + 1 + *num_of_matches as usize) { // next card inwards is incremented
                acc.entry(i).and_modify(|value| {
                    *value += to_add;
                });
            }
            acc
        })
        .values()
        .sum::<u32>();


    

    println!("{:?}", result);

    
}