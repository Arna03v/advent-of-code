#include <iostream>
#include <fstream>
#include <istream>
#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> operations;
set<int> numbers;

bool check(string& line, int& i){
    if(line[i] == 'm' && line[i+1] == 'u' && line[i+2] == 'l' && line[i+3] == '('){
        i=i+4;
        string num1 = "";
        string num2 = "";
        int number1;
        int number2;

        while(isdigit(line[i])){
            num1 += line[i];
            i++;
        }

        number1 = stoi(num1);

        if(line[i] == ','){
            i++;           

            while(isdigit(line[i])){
                num2 += line[i];
                i++;
            }
        }else{
            return false;
        }

        number2 = stoi(num2);

        if(line[i] == ')'){
            operations.push_back({number1, number2});
            return true;
        }else{
            return false;
        }

    } else {
        return false;
    }
}

int main(){
    // parse input.txt and store the correct operation in the vector
    ifstream file("input.txt");
    for(int i=0; i<9; i++) numbers.insert(i);

    if(!file.is_open()){
        cout << "Error reading the input file";
        return 1;
    }

    string line;
    while(getline(file, line)){
        int i = 0;
        
        while(i<line.size()){
            if(line[i] != 'm') i++;
            if(line[i] == 'm'){
                (check(line, i));
                i++;               
            }
        }
    }

    // now we have the operations
    int res = 0;
    for(pair<int,int>& numbers : operations){
        res += numbers.first * numbers.second;
    }

    cout << "Res is: " << res << endl;
    return 0;
}