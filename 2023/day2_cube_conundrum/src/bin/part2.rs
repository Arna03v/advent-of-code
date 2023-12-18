use std::{collections::BTreeMap, ops::Not};

use nom::{
    bytes::complete::tag,
    character::complete::{
        self, alpha1, digit1, line_ending,
    },
    multi::separated_list1,
    sequence::{preceded, separated_pair},
    IResult,
};

// use crate::custom_error::AocError;

#[derive(Debug)]
struct Cube<'a> {
    color: &'a str,
    amount: u32,
}

#[derive(Debug)]
struct Game<'a> {
    id: &'a str,
    rounds: Vec<Vec<Cube<'a>>>,
}

impl<'a> Game<'a> {
    // fn valid_for_cube_set(
    //     &self,
    //     map: &BTreeMap<&str, u32>,
    // ) -> Option<u32> {
    //     self.rounds
    //         .iter()
    //         .any(|round| {
    //             round.iter().any(|shown_cube| {
    //                 shown_cube.amount
    //                     > *map
    //                         .get(shown_cube.color)
    //                         .expect("a valid cube")
    //             })
    //         })
    //         .not()
    //         .then_some(
    //             self.id.parse::<u32>().expect(
    //                 "game id should a parsable u32",
    //             ),
    //         )
    // }

    fn minimum_cube_set(&self) -> u32{
        let map = BTreeMap::from([
            ("red", 0),
            ("green", 0),
            ("blue", 0),
        ]);
        // let res: u32;
        self.rounds.iter().fold(map, |mut acc, round| {
            //folding over the rounds
            for cube in round.iter()
            {
                // for each cube in a round
                acc.entry(cube.color).and_modify(|e|{
                    *e = (*e).max(cube.amount);
                })
                .or_insert(cube.amount);
            }
            acc

        })
        .values()
        .product() // as we want the product of the miniumum possible values
    }
}

// 4 red
fn cube(input: &str) -> IResult<&str, Cube> {
    let (input, (amount, color)) =
        separated_pair(complete::u32, tag(" "), alpha1)(
            input,
        )?;
    Ok((input, Cube { color, amount }))
}
// 3 blue, 4 red
fn round(input: &str) -> IResult<&str, Vec<Cube>> {
    let (input, cubes) =
        separated_list1(tag(", "), cube)(input)?;
    Ok((input, cubes))
}
// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue;
// 2 green
fn game(input: &str) -> IResult<&str, Game> {
    let (input, id) =
        preceded(tag("Game "), digit1)(input)?;
    let (input, rounds) = preceded(
        tag(": "),
        separated_list1(tag("; "), round),
    )(input)?;
    Ok((input, Game { rounds, id }))
}
fn parse_games(input: &str) -> IResult<&str, Vec<Game>> {
    let (input, games) =
        separated_list1(line_ending, game)(input)?;
    Ok((input, games))
}

fn main(){
    let input = include_str!("./input1.txt");
    let output = process(input);
    dbg!(output);
}

fn process(
    input: &str,
) -> Result<String, &str> {
    // let map = BTreeMap::from([
    //     ("red", 12),
    //     ("green", 13),
    //     ("blue", 14),
    // ]);
    let games = parse_games(input).expect("should parse");

    Ok(games
        .1
        .iter()
        .map(|game| game.minimum_cube_set())
        .sum::<u32>()
        .to_string())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() -> Result<(), Box<dyn std::error::Error>> {
        let input = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
        Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
        Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
        Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
        Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
        assert_eq!("2286", process(input)?);
        Ok(())
    }
}