#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

bool isValid(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int countXMAS(std::vector<std::string>& grid) {
    int count = 0;
    int n = grid.size();
    int m = grid[0].size();
    
    // 8 directions: right, down-right, down, down-left, left, up-left, up, up-right
    int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 'X') {
                // Check all 8 directions
                for(int dir = 0; dir < 8; dir++) {
                    bool found = true;
                    string target = "XMAS";
                    
                    // Check if "XMAS" can be formed in this direction
                    for(int k = 0; k < 4; k++) {
                        int newX = i + dx[dir] * k;
                        int newY = j + dy[dir] * k;
                        
                        if(!isValid(newX, newY, n, m) || 
                           grid[newX][newY] != target[k]) {
                            found = false;
                            break;
                        }
                    }
                    if(found) count++;
                }
            }
        }
    }
    return count;
}

int main() {
    ifstream file("input.txt");
    vector<string> grid;
    string line;
    
    // Read input
    while(getline(file, line)) {
        grid.push_back(line);
    }
    
    cout << countXMAS(grid) << endl;
    return 0;
}