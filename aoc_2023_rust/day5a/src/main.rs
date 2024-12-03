// UNDERSTANDING THE QUESTION

// all numbers are assigned relative to their field, that is soil 1 != water 1 and so on
// seed to soil mapping : tells us how to convert seed number (source) to soil number (destination)
// The maps describe entire ranges of numbers that can be converted.
// (destination range start, source range start, range length)

// Consider again the example seed-to-soil map:

// 50 98 2
// 52 50 48

// The first line has a destination range start of 50, a source range start of 98, and a range length of 2. This line means that the source range starts at 98 and contains two values: 98 and 99. The destination range is the same length, but it starts at 50, so its two values are 50 and 51. With this information, you know that seed number 98 corresponds to soil number 50 and that seed number 99 corresponds to soil number 51.
// The second line means that the source range starts at 50 and contains 48 values: 50, 51, ..., 96, 97. This corresponds to a destination range starting at 52 and also containing 48 values: 52, 53, ..., 98, 99. So, seed number 53 corresponds to soil number 55.
// Any source numbers that aren't mapped correspond to the same destination number. So, seed number 10 corresponds to soil number 10.

// we need to find the location numbers of each seed.
// What is the lowest location number that corresponds to any of the initial seed number?

// using nom_supreme instead of nom for the parser
use nom::IResult;
use nom_supreme::{tag::complete::tag,ParserExt};
use std::ops::Range;

struct SeedMap{
    mappings : Vec<(Range<u32>,Range<u32)>>

}

impl SeedMap{
    fn translate(source : u32) -> u32{
        todo!("implement translatation from a source to destination")
    }
}

fn line(input :&str) -> IResult<&str, (Range<u32>, Range<u32>)>{
    let (input, (destination, source, num)) =tuple((
        complete::u32.preceded_by(tag(" ")),
        complete::u32.preceded_by(tag(" ")),
        complete::u32,

    ))(input)?;

    Ok((input, (source..source+num, destination..destination+num)))
    // we flip the order of source and destination as we want to map source to destination 
    // easier for me to work with this way

}

fn main(){
    let input = include_str!("input.txt");

    // make a function to take in input and do 1-1 mapping
    // build seed to soil for the input seeds
    // build soil to fertilizer for the input seeds
    // build fertilizer to water for the input seeds
    // build water to light for the input seeds
    // build light to temp for the input seeds
    // build temp to humidity for the input seeds
    // build humidity to location for the input seeds
    // find the lowest lcation number among the initial seeds

    let (input, seeds) = tag("seeds: ")
        .precedes(separated_list1(space1, complete::u32))
        .parse(input)?
        .expect("valid parsing");

    let (input, maps) = take_until("map:")
        .precedes(tag("map:"))
        .precedes(many1(line_ending.precedes(line)).map(|mappings| SeedMap { mappings })
        )
        .parse(input)?

    



}