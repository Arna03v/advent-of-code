#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <numeric> // For std::accumulate

using namespace std;

int main() {

    // Open the input file
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Error in opening the input file" << endl;
        return 1;
    }

    // --- PASS 1: Read file and get match counts for each card ---

    vector<int> match_counts; // Stores the number of matches for each card (e.g., card 1 -> index 0)
    string line;

    while (getline(file, line)) {
        stringstream curr_line(line);

        // Parse away "Card" and "1:"
        string segment;
        curr_line >> segment; // "Card"
        curr_line >> segment; // "1:"

        string remaining_line;
        getline(curr_line, remaining_line); // " 98 16 ... | 85 15 ..."

        // Find the position of the pipe
        size_t pipe_position = remaining_line.find('|');

        // 1. Get the winning numbers part (before the pipe)
        string winning_part = remaining_line.substr(0, pipe_position);
        stringstream winning_stream(winning_part);
        unordered_set<int> winning_numbers;
        
        int curr_number;
        while (winning_stream >> curr_number) {
            winning_numbers.insert(curr_number);
        }

        // 2. Get your numbers part (after the pipe)
        string my_numbers_part = remaining_line.substr(pipe_position + 1);
        stringstream my_numbers_stream(my_numbers_part);

        int current_card_matches = 0;
        while (my_numbers_stream >> curr_number) {
            // Check if your number is in the winning set
            if (winning_numbers.count(curr_number)) {
                current_card_matches++;
            }
        }

        // Store the number of matches for this card
        match_counts.push_back(current_card_matches);
    }

    // Close the file, we are done reading
    file.close();

    // --- END OF PASS 1 ---


    // --- PASS 2: Process card copies ---

    int num_original_cards = match_counts.size();
    
    // This vector will store the *quantity* of each card.
    // Initialize all counts to 1 (for the original set).
    vector<int> card_quantities(num_original_cards, 1);

    // Iterate through our cards
    for (int i = 0; i < num_original_cards; ++i) {
        
        int num_matches = match_counts[i];      // Get matches for the current card (e.g., card 1 has 4 matches)
        int current_quantity = card_quantities[i]; // Get how many of *this* card we have (e.g., we have 1 of card 1)

        // Add copies to the *next* cards
        for (int j = 1; j <= num_matches; ++j) {
            
            // Safety check: Don't go past the end of the card list
            if (i + j < num_original_cards) {
                
                // Add `current_quantity` copies to the (i + j)-th card
                // e.g., if we have 4 of card 3 (current_quantity=4) and it wins 2 cards,
                // we add 4 copies to card 4 and 4 copies to card 5.
                card_quantities[i + j] += current_quantity;
            }
        }
    }

    // --- END OF PASS 2 ---


    // --- FINAL CALCULATION ---

    // Sum up all the values in the card_quantities vector
    // We can use std::accumulate from <numeric> or a simple loop
    
    long long total_scratchcards = 0; // Use long long just in case
    for (int count : card_quantities) {
        total_scratchcards += count;
    }

    // Alternative using std::accumulate:
    // long long total_scratchcards = std::accumulate(card_quantities.begin(), card_quantities.end(), 0LL);
    // (0LL means a long long literal zero)

    cout << "The total number of scratchcards is: " << total_scratchcards << endl;
    return 0;
}