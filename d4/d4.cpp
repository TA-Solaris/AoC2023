#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> intersection(vector<int> v1, vector<int> v2){
    vector<int> v3;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
    return v3;
}

vector<int> getNumbers(string input) {
    vector<int> numbers;
    stringstream ss(input);
    string number;
    while (getline(ss, number, ' ')) {
        numbers.emplace_back(stoi(number));
    }
    return numbers;
}

int part1(string input) {
    // Cleaning up the input
    input = regex_replace(input, regex(" +"), " ");
    input = regex_replace(input, regex("Card [0-9]*: "), "");

    // Seting up vars
    int total = 0;

    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        string target = line.substr(0, line.find(" | "));
        line.erase(line.begin(), line.begin() + line.find(" | ") + 3);
        int num = intersection(getNumbers(target), getNumbers(line)).size();
        if (num != 0) total += pow(2, num - 1);
    }

    return total;
}

int part2(string input) {
    return 0;
}

string file_to_string(string filename) {
    ifstream inFile;
    inFile.open(filename);
    if (inFile.fail()) {
        cerr << "Unable to open file " << filename << " for reading!" << endl;
        exit(1);
    }
    ostringstream ss;
    ss << inFile.rdbuf();
    return ss.str();
}

int main() {
    string input = file_to_string("input.txt");
    // Running AoC
    cout << "--- Part 1 ---" << endl;
    cout << part1(input);
    cout << endl << "--- Part 2 ---" << endl;
    cout << part2(input) << endl;
    exit(0);
}