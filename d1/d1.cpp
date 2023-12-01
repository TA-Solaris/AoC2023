#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

int part1(string input) {
    // Removing letters
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (int i = 0; i < sizeof(chars)/sizeof(chars[0]); i++) {
        input.erase(std::remove(input.begin(), input.end(), chars[i]), input.end());
    }
    // Splitting the string
    stringstream ss(input);
    string line;
    // Summing the numbers
    int total = 0;
    while (getline(ss, line, '\n')) {
        line.erase(line.begin()+1, line.end()-1); // Making sure we only have first and last numbers
        total += stoi(line);
    }
    return total;
}

int part2(string input) {
    // Cringe Code
    input = regex_replace(input, regex("one"), "one1one");
    input = regex_replace(input, regex("two"), "two2two");
    input = regex_replace(input, regex("three"), "three3three");
    input = regex_replace(input, regex("four"), "four4four");
    input = regex_replace(input, regex("five"), "five5five");
    input = regex_replace(input, regex("six"), "six6six");
    input = regex_replace(input, regex("seven"), "seven7seven");
    input = regex_replace(input, regex("eight"), "eight8eight");
    input = regex_replace(input, regex("nine"), "nine9nine");
    return part1(input);
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
    try {
        cout << part1(input);
    } catch (...) {
        cout << "Error thrown in Part 1";
    }
    cout << endl << "--- Part 2 ---" << endl;
    cout << part2(input) << endl;
    exit(0);
}