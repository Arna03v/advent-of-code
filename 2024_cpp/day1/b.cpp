#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
    vector<int> left;
    unordered_map<int,int> right;

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
        int l;
        int r;

        if(iss >> l >> r){
            left.push_back(l);
            right[r]++; // increment count of how many times a number appears in the right list
        }
    }

    // close the file
    file.close();

    int score = 0;

    for(int i=0; i<left.size(); i++){
        int count = right[left[i]];

        score += left[i]*count;
    }

    cout << "The final score is : " << score << endl;

    return 0;

}