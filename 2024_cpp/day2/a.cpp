#include <iostream>
#include <fstream>
#include <istream>
#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> reports;

    ifstream file("input.txt");
    if(!file.is_open()){
        cout << "Error opening the file" << endl;
        return 1;
    }

    string line;
    while(getline(file, line)){
        istringstream iss(line);
        vector<int> current_report;
        int number;

        while(iss >> number){
            current_report.push_back(number);
        }

        reports.push_back(current_report);
    }

    int safe_reports = 0;

    for(vector<int>& report : reports){

        if(report.size() < 2) continue;        

        bool increasing  = report[1] > report[0];
        bool safe = true;

        for(int i=1; i<report.size(); i++){
            int difference = report[i] - report[i-1];
            if(abs(difference) < 1 || abs(difference) > 3 || (increasing && difference < 0) || (!increasing && difference > 0)){
                safe = false;
                break;
            }
        }

        if(safe == true){
            safe_reports++;
        }
    }

    cout << "number of safe reports is: " << safe_reports << endl;
    return 0;
}