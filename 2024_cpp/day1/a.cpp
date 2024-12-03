#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
    vector<int> left;
    vector<int> right;

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
            right.push_back(r);
        }
    }

    // close the file
    file.close();

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int distance = 0;

    for(int i=0; i<left.size(); i++){
        distance += abs(left[i] - right[i]);
    }

    cout << "The final distance is : " << distance << endl;

    return 0;

}