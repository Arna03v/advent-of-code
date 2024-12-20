#include <fstream>
#include <sstream>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

vector<int> topologicalSort(const vector<int>& query, const unordered_map<int, vector<int>>& rules) {
    // Build adjacency list and in-degree count for numbers in this query
    unordered_map<int, vector<int>> adj;
    unordered_map<int, int> inDegree;
    
    // Initialize for numbers in this query
    for (int num : query) {
        adj[num] = vector<int>();
        inDegree[num] = 0;
    }
    
    // Add edges from rules that are relevant to this query
    for (int from : query) {
        for (int to : query) {
            if (from != to) {
                // Check if there's a rule from->to
                auto it = rules.find(from);
                if (it != rules.end() && 
                    find(it->second.begin(), it->second.end(), to) != it->second.end()) {
                    adj[from].push_back(to);
                    inDegree[to]++;
                }
            }
        }
    }
    
    // Topological sort using Kahn's algorithm
    queue<int> q;
    vector<int> result;
    
    for (auto& pair : inDegree) {
        if (pair.second == 0) {
            q.push(pair.first);
        }
    }
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        result.push_back(curr);
        
        for (int next : adj[curr]) {
            inDegree[next]--;
            if (inDegree[next] == 0) {
                q.push(next);
            }
        }
    }
    
    return (result.size() == query.size()) ? result : query;
}

bool isCorrectOrder(const vector<int>& query, const unordered_map<int, vector<int>>& rules) {
    for (int i = 0; i < query.size(); i++) {
        for (int j = i + 1; j < query.size(); j++) {
            // For each pair of numbers, check if later number should come before earlier number
            auto it = rules.find(query[j]);  // Changed from query[i]
            if (it != rules.end() && 
                find(it->second.begin(), it->second.end(), query[i]) != it->second.end()) {
                return false;  // Found a violation - later number should come before earlier number
            }
        }
    }
    return true;
}

int main() {
    unordered_map<int, vector<int>> rules;  // stores what numbers should come after each number
    vector<vector<int>> queries;

    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Error opening the input" << endl;
        return 1;
    }

    string line;
    int emptyLines = 0;

    while (getline(file, line)) {
        if (line.empty()) {
            emptyLines++;
            continue;
        }

        if (emptyLines == 0) {
            size_t barPos = line.find('|');
            if (barPos != string::npos) {
                int before = stoi(line.substr(0, barPos));
                int after = stoi(line.substr(barPos + 1));
                rules[before].push_back(after);
            }
        } else if (emptyLines == 1) {
            istringstream iss(line);
            string number;
            vector<int> query;

            while (getline(iss, number, ',')) {
                query.push_back(stoi(number));
            }
            queries.push_back(query);
        }
    }

    file.close();

    // First identify incorrect queries
    set<int> incorrect_queries;
    for (int i = 0; i < queries.size(); i++) {
        if (!isCorrectOrder(queries[i], rules)) {
            incorrect_queries.insert(i);
        }
    }

    // Then only reorder the incorrect ones
    int result = 0;
    for (int i : incorrect_queries) {
        vector<int> reordered = topologicalSort(queries[i], rules);
        
        int midIndex = reordered.size() / 2;
        result += reordered[midIndex];
        
        // Debug output
        cout << "Reordered query " << i << ": ";
        for (int num : reordered) {
            cout << num << " ";
        }
        cout << " (middle: " << reordered[midIndex] << ")" << endl;
    }

    cout << "Final result: " << result << endl;
    return 0;
}