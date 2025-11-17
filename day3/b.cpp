#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <map> // For our coordinate maps
#include <set>  // For finding unique adjacent numbers

using namespace std;

int main() {
    // read the file 
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Error in opening the input file" << endl;
        return 1;
    }

    // Read all lines into a vector
    vector<string> matrix;
    string line;
    while (getline(file, line)) {
        matrix.push_back(line);
    }
    file.close();

    if (matrix.empty()) return 0;

    int r = matrix.size();
    int c = matrix[0].size();

    // --- PASS 1: Find all numbers and map them ---

    // Stores {row, start_col} -> number_value
    map<pair<int, int>, int> number_map;
    
    // Stores {digit_row, digit_col} -> {number_start_row, number_start_col}
    map<pair<int, int>, pair<int, int>> digit_to_number_key;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (isdigit(matrix[i][j])) {
                // Found the start of a number
                int start_col = j;
                string num_str = "";
                
                // Read the whole number
                while (j < c && isdigit(matrix[i][j])) {
                    num_str += matrix[i][j];
                    j++;
                }

                int num_val = stoi(num_str);
                
                // Store the number's value by its start coordinate
                number_map[{i, start_col}] = num_val;
                
                // Map all digits of this number back to its start coordinate
                for (int k = start_col; k < j; ++k) {
                    digit_to_number_key[{i, k}] = {i, start_col};
                }

                // The loop will increment j, so we need to back up one
                // to start the next check at the correct position.
                j--; 
            }
        }
    }

    // --- PASS 2: Find gears ('*') and calculate ratios ---

    long long total_gear_ratio_sum = 0;

    // Define the 8 directions
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            
            // Check if this is a potential gear
            if (matrix[i][j] == '*') {
                
                // Use a set to store the keys of adjacent numbers.
                // This automatically handles duplicates.
                set<pair<int, int>> adjacent_number_keys;

                // Check all 8 directions
                for (int k = 0; k < 8; ++k) {
                    int new_i = i + dr[k];
                    int new_j = j + dc[k];

                    // Check bounds
                    if (new_i >= 0 && new_i < r && new_j >= 0 && new_j < c) {
                        // Check if this neighbor is a digit
                        if (digit_to_number_key.count({new_i, new_j})) {
                            // It is! Add its number's key to our set
                            adjacent_number_keys.insert(digit_to_number_key.at({new_i, new_j}));
                        }
                    }
                }

                // --- Check if it's a valid gear ---
                if (adjacent_number_keys.size() == 2) {
                    // Exactly two unique adjacent numbers! This is a gear.
                    
                    // Get the two keys from the set
                    auto it = adjacent_number_keys.begin();
                    pair<int, int> key1 = *it;
                    it++;
                    pair<int, int> key2 = *it;

                    // Look up their values and calculate the ratio
                    long long num1 = number_map.at(key1);
                    long long num2 = number_map.at(key2);
                    
                    total_gear_ratio_sum += (num1 * num2);
                }
            }
        }
    }

    cout << "The sum of all gear ratios is: " << total_gear_ratio_sum << endl;

    return 0;
}