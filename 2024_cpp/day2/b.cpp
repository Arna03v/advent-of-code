#include <iostream>
#include <fstream>
#include <istream>
#include <bits/stdc++.h>
using namespace std;

bool is_safe(vector<int>& report){
    if (report.size() < 2) return true;

    bool increasing = report[1] > report[0];
    for (int i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3 || (increasing && diff < 0) || (!increasing && diff > 0)) {
            return false;
        }
    }
    return true;
}

bool is_safe_with_removal(vector<int>& report){
    for (int i = 0; i < report.size(); ++i) {
        vector<int> modified_report = report;
        modified_report.erase(modified_report.begin() + i);
        if (is_safe(modified_report)) {
            return true;
        }
    }
    return false;
}

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

        if(is_safe(report) || is_safe_with_removal(report)){
            safe_reports++;
        }
    }

    cout << "number of safe reports is: " << safe_reports << endl;
    return 0;
}