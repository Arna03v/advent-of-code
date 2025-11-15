#include <iostream>
#include <fstream>
#include <string>
#include <vector>    // We'll use this for our digit words
#include <cctype> 

using namespace std;// For isdigit()

int main() {
    vector<pair<string, int>> wordDigits = {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
        {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return 1;
    }

    int total_sum = 0;
    string line;

    while (getline(file, line)) {
        int firstDigit = -1;
        int lastDigit = -1;

        // Loop through every character in the line
        for (int i = 0; i < line.length(); ++i) {
            int currentDigit = -1;

            // 1. Check if the character is a digit
            if (isdigit(line[i])) {
                currentDigit = line[i] - '0'; // Convert char '5' to int 5
            } else {
                // 2. If not, check if a spelled-out digit starts here
                for (const auto& pair : wordDigits) {
                    const string& word = pair.first;
                    // Check if the substring starting at 'i' matches the word
                    // and ensure we don't go out of bounds
                    if (i + word.length() <= line.length() && line.substr(i, word.length()) == word) {
                        currentDigit = pair.second;
                        break; // Found a word, stop checking other words
                    }
                }
            }

            // If we found any digit (numeric or word)
            if (currentDigit != -1) {
                if (firstDigit == -1) {
                    firstDigit = currentDigit; // This only happens once
                }
                lastDigit = currentDigit; // This always gets updated
            }
        }

        // After checking the whole line, add the combined number to the sum
        if (firstDigit != -1) {
            total_sum += (firstDigit * 10 + lastDigit);
        }
    }

    file.close();

    cout << "The final sum is : " << total_sum << endl;

    return 0;
}