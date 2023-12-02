#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
using namespace std;

const int maxRed = 12;
const int maxGreen = 13;
const int maxBlue = 14;

int part1(string input) {
    // Cleaning up the input
    input = regex_replace(input, regex("Game [0-9]*:"), "");
    input = regex_replace(input, regex("red"), "R");
    input = regex_replace(input, regex("green"), "G");
    input = regex_replace(input, regex("blue"), "B");
    input = regex_replace(input, regex(" "), "");
    // Splitting the string
    stringstream ss1(input);
    string line;
    // Looping through the input
    int game = 0;
    int total = 0;
    bool validGame;
    while (getline(ss1, line, '\n')) {
        game++;
        validGame = true;
        stringstream ss2(line);
        string handfull;
        while (getline(ss2, handfull, ';')) {
            stringstream ss3(handfull);
            string colour;
            while (getline(ss3, colour, ',')) {
                int value = stoi(colour.substr(0, colour.size()-1));
                if (colour.back() == 'R' && value > maxRed) validGame = false;
                if (colour.back() == 'G' && value > maxGreen) validGame = false;
                if (colour.back() == 'B' && value > maxBlue) validGame = false;
            }
        }
        if (validGame) {
            total += game;
        }
    }
    return total;
}

int part2(string input) {
    // Cleaning up the input
    input = regex_replace(input, regex("Game [0-9]*:"), "");
    input = regex_replace(input, regex("red"), "R");
    input = regex_replace(input, regex("green"), "G");
    input = regex_replace(input, regex("blue"), "B");
    input = regex_replace(input, regex(" "), "");
    // Splitting the string
    stringstream ss1(input);
    string line;
    // Looping through the input
    int total = 0;
    while (getline(ss1, line, '\n')) {
        stringstream ss2(line);
        string handfull;
        int reds = 0;
        int greens = 0;
        int blues = 0;
        while (getline(ss2, handfull, ';')) {
            stringstream ss3(handfull);
            string colour;
            while (getline(ss3, colour, ',')) {
                int value = stoi(colour.substr(0, colour.size()-1));
                if (colour.back() == 'R' && value > reds) reds = value;
                if (colour.back() == 'G' && value > greens) greens = value;
                if (colour.back() == 'B' && value > blues) blues = value;
            }
        }
        total += reds * greens * blues;
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