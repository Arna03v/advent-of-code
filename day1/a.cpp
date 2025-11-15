#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype> // for isdigit
#include <cstdlib> // for atoi
using namespace std;

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

        // read the file
        int l = 0;
        int r = line.size()-1;

        while(!isdigit(line[l]))l++;
        while(!isdigit(line[r]))r--;

        res += ((10 * (line[l] - '0')) + (line[r] - '0'));
    }

    // close the file
    file.close();

    // printing the final result
    cout << "the final sum is : " << res << endl;

    return 0;

}
