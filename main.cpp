#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <bitset>



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

    // This makes the priority_queue a MIN-heap (smallest freq on top)
    bool operator>(const Node& other) const {
        return freq > other.freq;
    }
};

// Custom comparator for pointers (since we will store Node pointers)
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
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

// Map to store character and its corresponding Huffman code
unordered_map<char, string> huffmanCodeMap;

void generateCodes(Node* root, string str) {
    if (!root) return;

    // If it's a leaf node, it contains a character
    if (root->ch != '$') {
        huffmanCodeMap[root->ch] = str;
    }

    // Traverse left and right
    generateCodes(root->left, str + "0");
    generateCodes(root->right, str + "1");
}


Node* buildHuffmanTree(unordered_map<char, int>& freqMap) {
    // Create a min heap of pointers to Nodes
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Step 1: Create a leaf node for each character and add it to the heap
    for (auto pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Step 2: Iterate until the heap size is 1
    while (minHeap.size() > 1) {
        // Pop the two lowest frequency nodes
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        // Step 3: Create a new internal node with sum of frequencies
        // '$' is a special marker for internal nodes
        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }
     return minHeap.top();

}

    // The remaining node is the root of the Huffman Tree




void compressFile(string inputFileName, string outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName, ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return;
    }

    // 1. Write the "Header" (Frequency Map) so we can rebuild the tree later
    // For simplicity in this module, we write the size and then each entry
    size_t mapSize = huffmanCodeMap.size();
    outputFile.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));
    for (auto const& [ch, code] : huffmanCodeMap) {
        outputFile.put(ch);
        size_t codeLen = code.length();
        outputFile.write(reinterpret_cast<const char*>(&codeLen), sizeof(codeLen));
        outputFile.write(code.c_str(), codeLen);
    }

    // 2. Encode the actual text
    string bitString = "";
    char ch;
    inputFile.clear();
    inputFile.seekg(0); // Go back to start of input file
    while (inputFile.get(ch)) {
        bitString += huffmanCodeMap[ch];
    }

    // 3. Bit Packing
    // Add padding to make it a multiple of 8
    int padding = 8 - (bitString.length() % 8);
    if (padding == 8) padding = 0;
    
    for (int i = 0; i < padding; i++) bitString += '0';

    // Save padding info so we can ignore it during decompression
    outputFile.put(static_cast<char>(padding));

    // Write bits as bytes
    for (size_t i = 0; i < bitString.length(); i += 8) {
        bitset<8> byte(bitString.substr(i, 8));
        unsigned char charToWrite = static_cast<unsigned char>(byte.to_ulong());
        outputFile.put(charToWrite);
    }

    inputFile.close();
    outputFile.close();
    cout << "Compression complete! Check: " << outputFileName << endl;
}


void decompressFile(string inputFileName, string outputFileName) {
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return;
    }

    // 1. Read Metadata (The Huffman Map)
    size_t mapSize;
    inputFile.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
    unordered_map<string, char> reverseCodeMap; // We want Code -> Char now

    for (size_t i = 0; i < mapSize; i++) {
        char ch = inputFile.get();
        size_t codeLen;
        inputFile.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen));
        char* buffer = new char[codeLen + 1];
        inputFile.read(buffer, codeLen);
        buffer[codeLen] = '\0';
        reverseCodeMap[string(buffer)] = ch;
        delete[] buffer;
    }

    // 2. Read Padding and Bits
    char paddingChar;
    inputFile.get(paddingChar);
    int padding = static_cast<int>(paddingChar);

    string bitString = "";
    char byte;
    while (inputFile.get(byte)) {
        bitString += bitset<8>(static_cast<unsigned char>(byte)).to_string();
    }

    // 3. Remove Padding
    if (padding > 0 && bitString.length() >= padding) {
        bitString.erase(bitString.length() - padding);
    }

    // 4. Translate Bits to Characters
    string currentCode = "";
    for (char bit : bitString) {
        currentCode += bit;
        if (reverseCodeMap.find(currentCode) != reverseCodeMap.end()) {
            outputFile.put(reverseCodeMap[currentCode]);
            currentCode = ""; // Reset for next character
        }
    }

    inputFile.close();
    outputFile.close();
    cout << "Decompression complete! Check: " << outputFileName << endl;
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

    Node* root = buildHuffmanTree(frequencies);
    cout << "Huffman Tree built successfully! Root frequency: " << root->freq << endl;

    // 3. Generate Codes
    generateCodes(root, "");

    // Display the codes
    cout << "\n--- Huffman Codes ---" << endl;
    for (auto pair : huffmanCodeMap) {
        cout << "'" << pair.first << "' : " << pair.second << endl;
    }
    

    return 0;
}