// if there number is from index i to i+n, if there is any symbol on i-1, i+n+1, j-1 to j+n+1, k-1 to k+n+1, then the number of valis
// j is i but in the next line
// k is i but in previous line


fn main(){
    let input = include_str!("./input.txt");
    let output = process(input);
    dbg!(output);
}

fn process( input: &str, ) -> Result<String, &str> {
    
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works()  {
        let input = "467..114..
        ...*......
        ..35..633.
        ......#...
        617*......
        .....+.58.
        ..592.....
        ......755.
        ...$.*....
        .664.598..";
        assert_eq!("4361", process(input)?);
        
    }
}