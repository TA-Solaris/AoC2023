#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <regex>
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
    if (m.find(current) == m.end()) return -1; // So that Part 2 can run

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

int getSteps(string current, map<string, pair<string, string>> m, string directions) {
    int steps = 0;
    while (current[2] != 'Z') {
        if (directions[steps % directions.size()] == 'L') {
            current = m[current].first;
        } else {
            current = m[current].second;
        }
        steps++;
    }
    return steps;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int part2(string input) {
    string directions = input.substr(0, input.find("\n\n"));
    input.erase(input.begin(), input.begin() + input.find("\n\n") + 2);
    map<string, pair<string, string>> m = getMap(input);

    vector<int> steps;
    for (const auto& [key, value] : m) if (key[2] == 'A') steps.emplace_back(getSteps(key, m, directions));

    int r = 1;
    for (int i = 0; i < steps.size(); i++) r = (((steps[i] * r)) / (gcd(steps[i], r)));

    return r;
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