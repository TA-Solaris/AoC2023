#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include <algorithm>
using namespace std;

vector<long int> getNumbers(string input) {
    vector<long int> ns;
    stringstream ss(input);
    string n;
    while (getline(ss, n, ' ')) {
        ns.emplace_back(stol(n));
    }
    return ns;
}

long int mapValue(string m, long int v) {
    stringstream ss(m);
    string line;
    while (getline(ss, line, '\n')) {
        vector<long int> ns = getNumbers(line);
        if (ns[1] <= v && ns[1] + ns[2] > v) {
            return v - ns[1] + ns[0];
        }
    }
    return v;
}

int part1(string input) {
    // Cleaning up the input
    input = regex_replace(input, regex("seeds: "), "");
    input = regex_replace(input, regex("\n\nseed-to-soil map:\n"), ":");
    input = regex_replace(input, regex("soil-to-fertilizer map:\n"), "");
    input = regex_replace(input, regex("fertilizer-to-water map:\n"), "");
    input = regex_replace(input, regex("water-to-light map:\n"), "");
    input = regex_replace(input, regex("light-to-temperature map:\n"), "");
    input = regex_replace(input, regex("temperature-to-humidity map:\n"), "");
    input = regex_replace(input, regex("humidity-to-location map:\n"), "");
    input = regex_replace(input, regex("\n\n"), "-");

    vector<long int> seeds = getNumbers(input.substr(0, input.find(":")));
    input.erase(input.begin(), input.begin() + input.find(":") + 1);

    vector<string> ms;
    stringstream ss(input);
    string map_str;
    while (getline(ss, map_str, '-')) {
        ms.emplace_back(map_str);
    }

    for (string m : ms) {
        for(int i = 0; i < seeds.size(); i++) {
            seeds[i] = mapValue(m, seeds[i]);
        }
    }

    return *min_element(seeds.begin(), seeds.end());
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