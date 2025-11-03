//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}
// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // Creates MinHeap and pushes all leaf node indices
    // Pops two smallest nodes and creates parent with combined weight
    // Sets left/right pointers and pushes parent back into heap
    // Returns index of final root node
    MinHeap heap;

    for (int i = 0; i < nextFree; i++) {
        heap.push(i, weightArr);
    }

    int nodeIndex = nextFree;

    while (heap.size > 1) {
        int leftIdx = heap.pop(weightArr);
        int rightIdx = heap.pop(weightArr);

        weightArr[nodeIndex] = weightArr[leftIdx] + weightArr[rightIdx];
        leftArr[nodeIndex] = leftIdx;
        rightArr[nodeIndex] = rightIdx;
        charArr[nodeIndex] = '\0';

        heap.push(nodeIndex, weightArr);
        nodeIndex++;
    }

    int root = heap.pop(weightArr);
    return root;
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // Uses stack to simulate DFS traversal of encoding tree
    // Left edges add '0' to code, right edges add '1'
    // Stores code when reaching leaf nodes with characters
    stack<pair<int, string>> nodeStack;
    nodeStack.push({root, ""});

    while (!nodeStack.empty()) {
        auto current = nodeStack.top();
        nodeStack.pop();
        int nodeIdx = current.first;
        string currentCode = current.second;

        if (charArr[nodeIdx] != '\0') {
            char ch = charArr[nodeIdx];
            codes[ch - 'a'] = currentCode;
        }

        if (leftArr[nodeIdx] != -1) {
            nodeStack.push({leftArr[nodeIdx], currentCode + "0"});
        }

        if (rightArr[nodeIdx] != -1) {
            nodeStack.push({rightArr[nodeIdx], currentCode + "1"});
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}