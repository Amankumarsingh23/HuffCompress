#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>


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