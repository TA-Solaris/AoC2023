#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
using namespace std;

vector<string> getPMap(string input) {
    vector<string> pmap;
    stringstream ss(input);
    string s;
    while (getline(ss, s, '\n')) {
        pmap.emplace_back(s.insert(0, 1, '.').insert(s.end() - s.begin(), 1, '.')); // this is a fix (just adding whitespace around map)
    }
    return pmap;
}

pair<int, int> getNext(vector<string> pmap, pair<int, int> current, pair<int, int> next) {
    // Move Down
    if (pmap[next.second][next.first] == '|' && current.second < next.second
    ||  pmap[next.second][next.first] == '7' && current.first < next.first
    ||  pmap[next.second][next.first] == 'F' && current.first > next.first)
        return make_pair(next.first, next.second + 1);
    // Move Up
    if (pmap[next.second][next.first] == '|' && current.second > next.second
    ||  pmap[next.second][next.first] == 'J' && current.first < next.first
    ||  pmap[next.second][next.first] == 'L' && current.first > next.first)
        return make_pair(next.first, next.second - 1);
    // Move Right
    if (pmap[next.second][next.first] == '-' && current.first < next.first
    ||  pmap[next.second][next.first] == 'L' && current.second < next.second
    ||  pmap[next.second][next.first] == 'F' && current.second > next.second)
        return make_pair(next.first + 1, next.second);
    // Move Left
    if (pmap[next.second][next.first] == '-' && current.first > next.first
    ||  pmap[next.second][next.first] == '7' && current.second > next.second
    ||  pmap[next.second][next.first] == 'J' && current.second < next.second)
        return make_pair(next.first - 1, next.second);
    throw std::invalid_argument("Invalid map point reached! (" + to_string(current.first) + ", " + to_string(current.second) + ") -> (" + to_string(next.first) + ", " + to_string(next.second) + ")");
}

int part1(string input) {
    vector<string> pmap = getPMap(input);

    // Getting initial conditions
    pair<int, int> current1 = make_pair(-1, -1);
    pair<int, int> next1 = make_pair(-1, -1);
    pair<int, int> current2 = make_pair(-1, -1);
    pair<int, int> next2 = make_pair(-1, -1);
    for (int y = 0; y < pmap.size(); y++) {
        for (int x = 0; x < pmap[0].size(); x++) {
            if (pmap[y][x] == 'S') {
                current1 = make_pair(x, y);
                current2 = make_pair(x, y);
                if ((pmap[y - 1][x] == '|' || pmap[y - 1][x] == 'F' || pmap[y - 1][x] == '7') && next1.first == -1) {
                    next1 = make_pair(x, y - 1);
                } else {
                    next2 = make_pair(x, y - 1);
                }
                if ((pmap[y + 1][x] == '|' || pmap[y + 1][x] == 'L' || pmap[y + 1][x] == 'J') && next1.first == -1) {
                    next1 = make_pair(x, y + 1);
                } else {
                    next2 = make_pair(x, y + 1);
                }
                if ((pmap[y][x - 1] == '-' || pmap[y][x - 1] == 'F' || pmap[y][x - 1] == 'L') && next1.first == -1) {
                    next1 = make_pair(x - 1, y);
                } else {
                    next2 = make_pair(x - 1, y);
                }
                if ((pmap[y][x + 1] == '-' || pmap[y][x + 1] == 'J' || pmap[y][x + 1] == '7') && next1.first == -1) {
                    next1 = make_pair(x + 1, y);
                } else {
                    next2 = make_pair(x + 1, y);
                }
            }
        }
    }

    int count = 1;
    pair<int, int> temp;
    while (next1 != next2) {
        //cout << "(" + to_string(current1.first) + ", " + to_string(current1.second) + ") -> (" + to_string(next1.first) + ", " + to_string(next1.second) + ") (" + to_string(current2.first) + ", " + to_string(current2.second) + ") -> (" + to_string(next2.first) + ", " + to_string(next2.second) + ")\n";
        temp = getNext(pmap, current1, next1);
        current1 = next1;
        next1 = temp;
        temp = getNext(pmap, current2, next2);
        current2 = next2;
        next2 = temp;
        count++;
    }

    return count;
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