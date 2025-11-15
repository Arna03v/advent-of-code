#!/usr/bin/env bash
set -euo pipefail

# Creates directories day1 .. day30 and places a.cpp, b.cpp (with boilerplate) and input.txt in each.
for i in $(seq 1 30); do
  dir="day${i}"
  mkdir -p "$dir"

  cat > "$dir/a.cpp" <<'CPP'
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
CPP

  cat > "$dir/b.cpp" <<'CPP'
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
CPP

  # create an empty input.txt (overwrite if exists)
  : > "$dir/input.txt"
done