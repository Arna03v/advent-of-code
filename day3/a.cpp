#include <iostream>
#include <fstream>
// #include <sstream> // Not used
#include <vector>
#include <string> // Added for string
#include <cctype> // Added for isdigit

using namespace std;

// for each number
// check all 8 directions
// if there is a symbol
    // mark the number as valid add the entire number to the res, not just the character
// else move on to next character

// every character == number || == '.' is not a symbol
// everything else is a symbol


vector<vector<int>> directions = {{1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {0,1}, {1,1}, {-1,1}};
int r;
int c;

// Renamed this function for clarity and fixed the boundary check
// It checks if a *single* cell (i, j) is a symbol
bool isSymbol(int i, int j, vector<string>& input){
    if(i < 0 || i >= r || j < 0 || j >= c ) return false;
    if(isdigit(input[i][j]) || input[i][j] == '.') return false;
    return true;
}

int main(){

    // read the file 
    ifstream file("input.txt");

    // check if the file is open
    if(!file.is_open()) {
        cout << "Error in opening the input file" << endl;
        return 1;
    }

    string line; // read the file line by line, storing it in the variable "line"
    vector<string> input;
    while(getline(file, line)){
        input.push_back(line);
    }

    r = input.size();
    c = input[0].size();

    long long res = 0;

    for(int i=0; i < r; i++){ // i is the row
        for(int j=0; j < c; j++){ // j is the col
            
            // Look for the start of a number
            if(isdigit(input[i][j])){
                
                // Found the start of a number
                int starting_index = j;
                string curr_num_str = "";
                
                // Build the entire number
                while(j < c && isdigit(input[i][j])){
                    curr_num_str += input[i][j];
                    j++;
                }
                
                // We now have the number, e.g., "617"
                // It starts at col 'starting_index' and ends at 'j-1'
                
                bool is_part_number = false;
                
                // Check all 8 neighbors for EACH digit of the number
                for(int k = starting_index; k < j; k++){
                    // k is the column of the current digit we are checking
                    
                    for(const auto& dir : directions){
                        int new_i = i + dir[0];
                        int new_j = k + dir[1];
                        
                        if(isSymbol(new_i, new_j, input)){
                            is_part_number = true;
                            break; // Found a symbol, no need to check other directions
                        }
                    }
                    
                    if(is_part_number){
                        break; // Found a symbol, no need to check other digits
                    }
                }
                
                if(is_part_number){
                    res += stoi(curr_num_str);
                }
                
                // The outer j loop will continue at 'j', 
                // which is already past the end of the number we just processed.
            }
        }
    }

    cout << "The final sum is: " << res << endl;

    // close the file
    file.close();

    return 0;

}