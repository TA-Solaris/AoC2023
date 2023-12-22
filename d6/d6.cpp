#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
using namespace std;

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
    input = regex_replace(input, regex("Time: "), "");
    input = regex_replace(input, regex("Distance: "), "");

    vector<int> time;
    vector<int> distance;

    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        if (time.size() == 0) {
            time = getNumbers(line);
        } else {
            distance = getNumbers(line);
        }
    }

    int total = 1;
    for (int i = 0; i < time.size(); i++) {
        int way = 0;
        for (int speed = 0; speed < time[i]; speed++) {
            if ((time[i] - speed) * speed > distance[i]) way++;
        }
        total = total * way;
    }

    return total;
}

int part2(string input) {
    // Cleaning up the input
    input = regex_replace(input, regex(" +"), "");
    input = regex_replace(input, regex("Time:"), "");
    input = regex_replace(input, regex("Distance:"), "");

    long int time = 0;
    long int distance = 0;

    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        if (time == 0) {
            time = stol(line);
        } else {
            distance = stol(line);
        }
    }

    long int min = 0;
    while ((time - min) * min < distance) {
        min++;
    }

    long int max = time;
    while ((time - max) * max < distance) {
        max--;
    }

    return max - min + 1;
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