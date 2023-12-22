#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
using namespace std;

vector<int> getNumbers(string input) {
    vector<int> ns;
    stringstream ss(input);
    string n;
    while (getline(ss, n, ' ')) {
        ns.emplace_back(stoi(n));
    }
    return ns;
}

int getNext(vector<int> seq) {
    if(all_of(seq.cbegin(), seq.cend(), [](int i){ return i == 0; })) return 0;
    vector<int> diffs;
    int current = seq[0];
    for (int i = 1; i < seq.size(); i++) {
        diffs.emplace_back(seq[i] - current);
        current = seq[i];
    }
    return seq[seq.size() - 1] + getNext(diffs);
}

int part1(string input) {
    int total = 0;

    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        total += getNext(getNumbers(line));
    }

    return total;
}

int getPrevious(vector<int> seq) {
    if(all_of(seq.cbegin(), seq.cend(), [](int i){ return i == 0; })) return 0;
    vector<int> diffs;
    int current = seq[0];
    for (int i = 1; i < seq.size(); i++) {
        diffs.emplace_back(seq[i] - current);
        current = seq[i];
    }
    return seq[0] - getPrevious(diffs);
}

int part2(string input) {
    int total = 0;

    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        total += getPrevious(getNumbers(line));
    }

    return total;
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