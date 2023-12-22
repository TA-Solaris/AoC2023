#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

map<string, pair<string, string>> getMap(string input) {
    map<string, pair<string, string>> m;
    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        string from = line.substr(0, line.find(" = ("));
        line.erase(line.begin(), line.begin() + line.find(" = (") + 4);
        string left = line.substr(0, line.find(", "));
        line.erase(line.begin(), line.begin() + line.find(", ") + 2);
        string right = line.substr(0, line.find(")"));
        m[from] = make_pair(left, right);
    }
    return m;
}

int part1(string input) {
    string directions = input.substr(0, input.find("\n\n"));
    input.erase(input.begin(), input.begin() + input.find("\n\n") + 2);
    map<string, pair<string, string>> m = getMap(input);

    string current = "AAA";
    int steps = 0;
    while (current != "ZZZ") {
        if (directions[steps % directions.size()] == 'L') {
            current = m[current].first;
        } else {
            current = m[current].second;
        }
        steps++;
    }

    return steps;
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