#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <cmath>
using namespace std;

// card card_number: [list of winning numbers] | [list of numbers I have]
// first match = 1 point, every other match in the card doubles the score
// return sum of score

int main(){

    // read the file 
    ifstream file("input.txt");

    // check if the file is open
    if(!file.is_open()) {
        cout << "Error in opening the input file" << endl;
        return 1;
    }

    int res = 0;

    string line; // read the file line by line, storing it in the variable "line"
    while(getline(file, line)){
        stringstream curr_line(line);

        // lets parse away till the colon
        string segment;
        curr_line >> segment;
        curr_line >> segment;

        string remaining_line;
        getline(curr_line, remaining_line);

        // storing the winning numbers in the set
        unordered_set<int> winning_numbers;

        // find the position of the pipe
        int pipe_position = remaining_line.find('|');
        
        // now parsing the winning numbers
        string winning = remaining_line.substr(0, pipe_position);
        stringstream winning_stream(winning);

        // now wxtract numbers from this winning stream
        int curr_number;
        while(winning_stream >> curr_number){
            winning_numbers.insert(curr_number);
        }

        // now to parse the second half of the stream
        string my_numbers = remaining_line.substr(pipe_position+1); // till the end if nothing is specified

        // stream for my numbers
        stringstream my_numbers_stream(my_numbers);
        int curr_line_score = 0;

        while(my_numbers_stream >> curr_number){
            if(winning_numbers.find(curr_number) != winning_numbers.end()){
                // we found this number in the winning set
                curr_line_score++;
            }
        }

        if(curr_line_score > 0){
            res += pow(2.0, (curr_line_score-1));
        }

    }

    // close the file
    file.close();

    cout << "the final score is : " << res << endl;
    return 0;

}
