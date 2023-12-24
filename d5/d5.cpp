#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include <algorithm>
#include <limits>
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

long int part1(string input) {
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

struct Range {
    long int start;
    long int end;
};

void printRange(Range r) {
    cout << "(" + to_string(r.start) + ", " + to_string(r.end) + ")";
}

struct Mapping {
    Range range;
    long int destination;
};

long int getMapValue(Mapping m) {
    return m.destination - m.range.start;
}

void printMapping(Mapping m) {
    cout << "(" + to_string(m.range.start) + ", " + to_string(m.range.end) + ") -> (" + to_string(m.range.start + getMapValue(m)) + ", " + to_string(m.range.end + getMapValue(m)) + ")";
}

vector<Range> getRanges(string rangestr) {
    vector<Range> rs;
    vector<long int> ns = getNumbers(rangestr);
    for (int i = 0; i < ns.size(); i += 2) {
        Range r = {ns[i], ns[i] + ns[i + 1] - 1};
        rs.emplace_back(r);
    }
    return rs;
}

vector<Mapping> getMappings(string input) {
    vector<Mapping> ms;
    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        vector<long int> ns = getNumbers(line);
        Mapping m = {{ns[1], ns[1] + ns[2] - 1}, ns[0]};
        ms.emplace_back(m);
    }
    return ms;
}

pair<Range, vector<Range>> mapRange(Range r, vector<Mapping> ms) {
    vector<Range> repeatrs;
    for (auto m : ms) {
        if (r.start >= m.range.start && r.end <= m.range.end) { // Fully contained
            r.start += getMapValue(m);
            r.end += getMapValue(m);
            return make_pair(r, repeatrs);
        }
        if (r.start >= m.range.start && r.end > m.range.end && r.start <= m.range.end) { // Top Heavy
            Range repeatr = {m.range.end + 1, r.end};
            repeatrs.emplace_back(repeatr); // TOP SIDE
            r.end = m.range.end;
            r.start += getMapValue(m);
            r.end += getMapValue(m);
            return make_pair(r, repeatrs);
        }
        if (r.start < m.range.start && r.end <= m.range.end && r.end >= m.range.start) { // Bottom Heavy
            Range repeatr = {r.start, m.range.start - 1};
            repeatrs.emplace_back(repeatr); // BOTTOM SIDE
            r.start = m.range.start;
            r.start += getMapValue(m);
            r.end += getMapValue(m);
            return make_pair(r, repeatrs);
        }
        if (r.start < m.range.start && r.end > m.range.end) { // Both Heavy
            Range repeatr1 = {m.range.end + 1, r.end};
            repeatrs.emplace_back(repeatr1); // TOP SIDE
            Range repeatr2 = {r.start, m.range.start - 1};
            repeatrs.emplace_back(repeatr2); // BOTTOM SIDE
            r.start = m.range.start;
            r.end = m.range.end;
            r.start += getMapValue(m);
            r.end += getMapValue(m);
            return make_pair(r, repeatrs);
        }
    }
    return make_pair(r, repeatrs);
}

long int part2(string input) {
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

    vector<Range> rs = getRanges(input.substr(0, input.find(":")));
    input.erase(input.begin(), input.begin() + input.find(":") + 1);

    // Making the maps
    vector<vector<Mapping>> ms;
    stringstream ss(input);
    string map_str;
    while (getline(ss, map_str, '-')) {
        ms.emplace_back(getMappings(map_str));
    }

    pair<Range, vector<Range>> result;
    for (auto m : ms) {
        vector<Range> newrs;
        while(rs.size() > 0) {
            result = mapRange(rs[0], m);
            rs.erase(rs.begin());
            newrs.emplace_back(result.first);
            for (auto r : result.second) rs.emplace_back(r);
        }
        rs = newrs;
    }

    long int output = numeric_limits<long int>::max();
    for (Range r : rs) output = min(output, r.start);

    return output;
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