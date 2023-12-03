#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <regex>
#include <cstring>
using namespace std;

const char* numbers = "0123456789";

vector<tuple<int, int>> getSymbolPositions(string input) {
    vector<tuple<int, int>> positions;
    int y = 0;
    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        int x = 0;
        for (auto &chr : line) {
            if (strchr(numbers, chr) == NULL && !(chr == '.')) {
                positions.emplace_back(x, y);
                positions.emplace_back(x - 1, y);
                positions.emplace_back(x - 1, y - 1);
                positions.emplace_back(x - 1, y + 1);
                positions.emplace_back(x + 1, y);
                positions.emplace_back(x + 1, y - 1);
                positions.emplace_back(x + 1, y + 1);
                positions.emplace_back(x, y - 1);
                positions.emplace_back(x, y + 1);
            }
            x++;
        }
        y++;
    }
    return positions;
}

vector<tuple<int, int>> getNumberPositions(string input) {
    vector<tuple<int, int>> positions;
    int y = 0;
    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        int x = 0;
        for (auto &chr : line) {
            if (strchr(numbers, chr) != NULL) {
                positions.emplace_back(x, y);
            }
            x++;
        }
        y++;
    }
    return positions;
}

bool isElement(tuple<int, int> e, vector<tuple<int, int>> v) {
    for(auto ve: v){
        if (get<0>(ve) == get<0>(e) && get<1>(ve) == get<1>(e)) return true;
    }
    return false;
}

vector<tuple<int, int>> getValidNumberPositions(string input) {
    vector<tuple<int, int>> positions;
    vector<tuple<int, int>> symbolPositions = getSymbolPositions(input);
    vector<tuple<int, int>> numberPositions = getNumberPositions(input);
    for(auto pos: numberPositions){
        if (isElement(pos, symbolPositions)) {
            int x = get<0>(pos);
            int y = get<1>(pos);
            while (isElement(make_tuple(x, y), numberPositions)) {
                x--;
            }
            while (isElement(make_tuple(x + 1, y), numberPositions)) {
                x++;
                if (!isElement(make_tuple(x, y), positions)) positions.emplace_back(x, y);
            }
        }
    }
    return positions;
}

char getChar(int tx, int ty, string input) {
    int y = 0;
    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        int x = 0;
        for (auto &chr : line) {
            if (tx == x && ty == y) {
                return chr;
            }
            x++;
        }
        y++;
    }
    return ' ';
}

int part1(string input) {
    vector<tuple<int, int>> positions = getValidNumberPositions(input);
    tuple<int, int> previous;
    bool previousSet = false;
    string numbers = "";
    for(auto pos: positions){
        if (previousSet) {
            if (!(get<0>(previous) == get<0>(pos) - 1 && get<1>(previous) == get<1>(pos))) {
                numbers.push_back('\n');
            }
        }
        numbers.push_back(getChar(get<0>(pos), get<1>(pos), input));
        previousSet = true;
        previous = make_tuple(get<0>(pos), get<1>(pos));
    }
    // Splitting the string
    stringstream ss(numbers);
    string number;
    // Summing the numbers
    int total = 0;
    while (getline(ss, number, '\n')) {
        total += stoi(number);
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