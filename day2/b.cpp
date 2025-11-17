#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> // We'll use std::max

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    // Use long long for the sum, as the powers can get large.
    long long total_power_sum = 0;
    std::string line;

    // Read the file line by line
    while (std::getline(file, line)) {
        
        // --- 1. Find the maximums for THIS game ---
        // Reset the max counts for each new game (line)
        int max_red = 0;
        int max_green = 0;
        int max_blue = 0;

        std::stringstream line_stream(line);
        std::string segment;

        // Skip the "Game X:" part.
        // We can read everything up to the colon and discard it.
        std::getline(line_stream, segment, ':');

        // --- 2. Parse the sets (same as before) ---
        std::string all_sets;
        std::getline(line_stream, all_sets); // e.g., " 6 green, 3 blue; 3 red, 1 green"

        std::stringstream set_stream(all_sets);
        std::string set_str;

        // Split the line by semicolons
        while (std::getline(set_stream, set_str, ';')) {
            // Now set_str is e.g., " 6 green, 3 blue"

            // --- 3. Parse the Colors (same as before) ---
            std::stringstream color_stream(set_str);
            std::string color_count_str;

            // Split the set by commas
            while (std::getline(color_stream, color_count_str, ',')) {
                // Now color_count_str is e.g., " 6 green"
                
                std::stringstream ss(color_count_str);
                int count = 0;
                std::string color;
                ss >> count >> color; // e.g., count=6, color="green"

                // --- 4. The New Logic: Update maximums ---
                if (color == "red") {
                    max_red = std::max(max_red, count);
                } else if (color == "green") {
                    max_green = std::max(max_green, count);
                } else if (color == "blue") {
                    max_blue = std::max(max_blue, count);
                }
            }
        }

        // --- 5. Calculate Power and Add to Total ---
        // After checking all sets, calculate the power for this game
        // Cast one to long long to ensure the multiplication doesn't overflow
        long long power = (long long)max_red * max_green * max_blue;
        total_power_sum += power;
    }

    file.close();

    std::cout << "The sum of the power of these sets is: " << total_power_sum << std::endl;

    return 0;
}