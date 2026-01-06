#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// The building block of our Huffman Tree
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Module 1 Function: Count character frequencies in a file
unordered_map<char, int> countFrequency(string fileName) {
    unordered_map<char, int> freqMap;
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file!" << endl;
        return freqMap;
    }

    char ch;
    // Use .get() to catch spaces and newlines!
    while (inputFile.get(ch)) {
        freqMap[ch]++;
    }

    inputFile.close();
    return freqMap;
}

int main() {
    string fileName = "input.txt";
    
    // Step 1: Count Frequencies
    unordered_map<char, int> frequencies = countFrequency(fileName);

    // Display for testing
    cout << "Character Frequencies:" << endl;
    for (auto pair : frequencies) {
        cout << "'" << pair.first << "' : " << pair.second << endl;
    }

    return 0;
}