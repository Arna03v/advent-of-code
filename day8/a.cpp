#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

int main(){

    // read the file 
    ifstream file("input.txt");

    // check if the file is open
    if(!file.is_open()) {
        cout << "Error in opening the input file" << endl;
        return 1;
    }

    string line; // read the file line by line, storing it in the variable "line"
    while(getline(file, line)){
        istringstream iss(line);

        // read the file
    }

    // close the file
    file.close();

    return 0;

}
