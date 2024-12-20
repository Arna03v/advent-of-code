#include <fstream>
#include <istream>
#include <bits/stdc++.h>
using namespace std;

int main(){
    // store it in a map
    unordered_map<int, vector<int>> m; // for each number, store what numbers should appear before it
    vector<vector<int>> queries;

    ifstream file("input.txt");

    if(!file.is_open()){
        cout << "Error opening the input" << endl;
        return 1;
    }

    string line;
    int number_of_empty_lines = 0;

    while(getline(file, line)){
        if(line.empty()){
            number_of_empty_lines++;
            continue;
        }

        if(number_of_empty_lines == 0){
            // cout << "hitting" << endl;
            size_t position_of_bar = line.find('|'); // get from "find()" documentation
            if (position_of_bar != string :: npos){
                int x = stoi(line.substr(0, position_of_bar)); // from 0 till the bar
                int y = stoi(line.substr(position_of_bar + 1)); // from bar till the end

                m[y].push_back(x);
            }
        }else if(number_of_empty_lines == 1){
            istringstream iss(line);
            string number;
            vector<int> query;

            while(getline(iss, number, ',')){
                query.push_back({stoi(number)});
            }

            queries.push_back(query);
        }       
        
    }

    // for(vector<int>& query : queries){
    //     for(int i=0; i<query.size(); i++){
    //         cout << query[i] << " ";
    //     }
    //     cout << endl;
    // }

    file.close();

    // return 0;

    set<int> correct_queries; // storing the index of the correct queries

    // for each query
    int num = 0;
    for(vector<int>& query : queries){
        bool is_correct = true;
        // for each number in the query
        for(int i=query.size()-2; i>=0; i--){
            int curr = query[i];            

            for(int j=i+1; j<query.size(); j++){
                if(find(m[curr].begin(), m[curr].end(), query[j]) != m[curr].end()){
                    // the number that is supposed to appear before the current number is appearing after it
                    cout << "the issue is with " << curr << " and " << query[j]  << "for query: " << num+1 << endl;

                    is_correct = false;
                }

                if(!is_correct){
                    break;
                }
            }

            
        }
        if(is_correct){
            correct_queries.insert(num);
        }
        num++;

    }

    // now for each correct query, find the middle element

    int res = 0;

    for(int i : correct_queries){
        cout << "i is :" << i << endl;
        int size_of_query = queries[i].size();
        int middle_element = queries[i][size_of_query/2];
        res += middle_element;
    }

    cout << "res is : " << res << endl;


}

