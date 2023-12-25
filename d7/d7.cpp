#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include <algorithm>
using namespace std;

const vector<char> CARD_VALUES = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

int getCardValue(char c) {
    return find(CARD_VALUES.begin(), CARD_VALUES.end(), c) - CARD_VALUES.begin();
}

struct Hand { 
    int value;
    map<char, int> cards;
    string cards_str;
};

bool cmp(pair<char, int>& a, pair<char, int>& b) {
    if (a.second > b.second) return true;
    if (a.second < b.second) return false;
    if (getCardValue(a.first) > getCardValue(b.first)) return true;
    if (getCardValue(a.first) < getCardValue(b.first)) return false;
    return false;
}

bool compareHands(Hand h1, Hand h2) {
    
    vector<pair<char, int>> h1vec;
    for (const auto& [key, value] : h1.cards) h1vec.emplace_back(make_pair(key, value));
    sort(h1vec.begin(), h1vec.end(), cmp);
    vector<pair<char, int>> h2vec;
    for (const auto& [key, value] : h2.cards) h2vec.emplace_back(make_pair(key, value));
    sort(h2vec.begin(), h2vec.end(), cmp);

    // First ordering (THIS IS ALL WRONG, TYPING IS FAR SIMPLER)
    bool fullhouse = false;
    bool twopair = false;
    char prevcard1;
    char prevcard2;
    for (int i = 0; i < min(h1vec.size(), h2vec.size()); i++) {
        if ((fullhouse || twopair) && h1vec[i].second == 2 && h2vec[i].second == 2 && (prevcard1 != prevcard2)) {
            if (getCardValue(prevcard1) > getCardValue(prevcard2)) return false;
            if (getCardValue(prevcard1) < getCardValue(prevcard2)) return true;
        } else if (h1vec[i].second == 3 && h2vec[i].second == 3) {
            fullhouse = true;
            prevcard1 = h1vec[i].first;
            prevcard2 = h2vec[i].first;
        } else if (h1vec[i].second == 2 && h2vec[i].second == 2 && !(fullhouse || twopair)) {
            twopair = true;
            prevcard1 = h1vec[i].first;
            prevcard2 = h2vec[i].first;
        } else {
            if (h1vec[i].second > h2vec[i].second) return false;
            if (h1vec[i].second < h2vec[i].second) return true;
            if (h1vec[i].second == h2vec[i].second) {
                if (getCardValue(h1vec[i].first) > getCardValue(h2vec[i].first)) return false;
                if (getCardValue(h1vec[i].first) < getCardValue(h2vec[i].first)) return true;
            }
        }
    }

    // Second ordering
    for (int i = 0; i < h1.cards_str.size(); i++) {
        if (getCardValue(h1.cards_str[i]) > getCardValue(h2.cards_str[i])) return false;
        if (getCardValue(h1.cards_str[i]) < getCardValue(h2.cards_str[i])) return true;
    }

    return false;
}

vector<Hand> getHands(string input) {
    vector<Hand> hands;
    stringstream ss(input);
    string line;
    while (getline(ss, line, '\n')) {
        string cards_str = line.substr(0, line.find(" "));
        map<char, int> cards;
        for (char chr : cards_str) {
            if (cards.find(chr) == cards.end()) {
                cards[chr] = 1;
            } else {
                cards[chr]++;
            }
        }
        line.erase(line.begin(), line.begin() + line.find(" ") + 1);
        Hand hand = {stoi(line), cards, cards_str};
        hands.emplace_back(hand);
    }
    return hands;
}

long int part1(string input) {
    vector<Hand> hands = getHands(input);

    sort(hands.begin(), hands.end(), compareHands);

    for (Hand h : hands) cout << h.cards_str << " " << to_string(h.value) << endl;

    long int total = 0;
    for (int i = 0; i < hands.size(); i++) {
        total += (i + 1) * hands[i].value;
    }

    return total;
}

long int part2(string input) {
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