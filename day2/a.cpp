#include <iostream>
#include <fstream>
#include <sstream>
#include <string> // for isdigit
using namespace std;


// for each line
// each game is seprataed by a `;`
// for each game, check if constraints red <=12, green <=13, blue <=14 are true
    // if no, then discard the line
    // else 
        // continue on the line
        // if the games are over, add the line number to the sum
int main(){

    // read the file 
    ifstream file("input.txt");

    int res = 0;

    // check if the file is open
    if(!file.is_open()) {
        cout << "Error in opening the input file" << endl;
        return 1;
    }

    string line; // read the file line by line, storing it in the variable "line"
    while(getline(file, line)){
        // read the file

        stringstream line_stream(line);
        string segment; // to track the game id

        int game_id = 0;
        bool valid_line = true;

        line_stream >> segment; // now segment == 'Game'
        
        // now reading the game_id
        line_stream >> segment; // segment == 'x:'

        game_id = stoi(segment.substr(0, segment.find(':'))); // substr(starting index, length)

        // now lets parse one set at a time
        string all_sets;
        getline(line_stream, all_sets); // now all_sets contains the rest of the line_stream

        // converting this into a stringstream
        stringstream set_stream(all_sets);

        // lets store the curr_set
        string curr_set;
        while(getline(set_stream, curr_set, ';')){

            // set_stream is the entire stream
            // from it we are selecting the current set
            // which is delimited by the ';'

            if(!valid_line) break;

            // now lets parse indivudal colors
            stringstream color_stream(curr_set);
            string color_count_str;

            while(getline(color_stream, color_count_str, ',')){
                // color_count_str is now e.g., " 6 green"
                
                stringstream ss(color_count_str);
                int count = 0;
                string color;

                ss >> count >> color; // e.g., count = 6, color = "green"

                if (color == "red" && count > 12) {
                    valid_line = false;
                    break; // Stop checking this set
                }
                if (color == "green" && count > 13) {
                    valid_line = false;
                    break; // Stop checking this set
                }
                if (color == "blue" && count > 14) {
                    valid_line = false;
                    break; // Stop checking this set
                }
            }
        }

        // After checking all sets, if the line is still valid, add the ID
        if (valid_line) {
            res += game_id;
        }

    }

    // close the file
    file.close();

    cout << "final res is : " << res << endl;
    return 0;

}
