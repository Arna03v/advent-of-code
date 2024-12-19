#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int countXMAS(const vector<string>& grid) {
    int tot = 0;
    
    for(int i = 1; i < grid.size() - 1; i++) {
        for(int j = 1; j < grid[i].length() - 1; j++) {
            stringstream left, right;
            left << grid[i-1][j-1] << grid[i][j] << grid[i+1][j+1];
            right << grid[i+1][j-1] << grid[i][j] << grid[i-1][j+1];
            
            string l = left.str(), r = right.str();
            if((l == "MAS" || l == "SAM") && (r == "MAS" || r == "SAM")) {
                tot++;
            }

            // cout << i << "->" << j << endl;
        }
    }
    
    return tot;
}

int main() {    

    ifstream file("input.txt");
    vector<string> grid;
    string line;

    // cout << "working2" << endl;

    int i=0;
    
    while(getline(file, line)) {
        grid.push_back(line);
        // cout << "working" << i << endl;

    }

    // cout << "working -> writing done" << endl;
    
    cout << countXMAS(grid) << endl;
    return 0;
}