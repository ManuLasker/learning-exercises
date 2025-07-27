#include <bits/stdc++.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct MapDefaultValue{
    int i = -1;
};

vector<vector<int>> extract_file(string filename){
    vector<int> left;
    vector<int> right;
    string line;
    ifstream file_input(filename);
    while (getline(file_input, line))
    {
        int spacePos = line.rfind(" ");
        int left_number = stoi(line.substr(0, spacePos));
        int right_number = stoi(line.substr(spacePos + 1));
        left.push_back(left_number);
        right.push_back(right_number);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    return {left, right};
}

int part_1(vector<int> left, vector<int> right)
{
    int sum = 0;
    for (int i = 0; i < left.size(); i++)
    {
        sum += abs(right.at(i) - left.at(i));
    }
    return sum;
}

int part_2(vector<int> left, vector<int> right)
{
    map<int, MapDefaultValue> checked;
    int result = 0;
    for(int i: left){
        int cont = 0;
        int sw = checked[i].i;
        if (sw == -1) {
            for(int j: right){
                if (i == j){
                    cont += 1;
                }
            }
            checked[i].i = cont;
        } else {
            cont = sw;
        }
        result += (i * cont);
    }
    return result;
}

int main()
{
    string filename;
    cin >> filename;
    vector<vector<int>> content = extract_file(filename);
    int part_1_res = part_1(content.at(0), content.at(1));
    cout << "the answer for part_1 is " << part_1_res << "\n";
    int part_2_res = part_2(content.at(0), content.at(1));
    cout << "the answer for part_1 is " << part_2_res << "\n";
}
