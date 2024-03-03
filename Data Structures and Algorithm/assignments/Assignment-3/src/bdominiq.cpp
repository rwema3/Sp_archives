#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

struct TreeNode {
    std::string word;
    int count;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& w) : word(w), count(1), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    void insertWord(TreeNode*& node, const std::string& word) {
        if (node == nullptr) {
            node = new TreeNode(word);
        } else if (word < node->word) {
            insertWord(node->left, word);
        } else if (word > node->word) {
            insertWord(node->right, word);
        } else {
            node->count++;
        }
    }

    void traverseInOrder(TreeNode* node, std::ofstream& outputFile, int& totalProbes, int& maxProbes, int currentProbe) {
        if (node == nullptr) return;
        traverseInOrder(node->left, outputFile, totalProbes, maxProbes, currentProbe + 1);
        outputFile << node->word << " " << node->count << " (" << currentProbe << ")" << std::endl;
        totalProbes += currentProbe;
        maxProbes = std::max(maxProbes, currentProbe);
        traverseInOrder(node->right, outputFile, totalProbes, maxProbes, currentProbe + 1);
    }

public:
    BST() : root(nullptr) {}

    void insert(const std::string& word) {
        insertWord(root, word);
    }

    void traverseAndWrite(std::ofstream& outputFile, int& totalProbes, int& maxProbes) {
        int currentProbe = 0;
        traverseInOrder(root, outputFile, totalProbes, maxProbes, currentProbe);
    }

    void clear() {
        clear(root);
    }

    ~BST() {
        clear();
    }

private:
    void clear(TreeNode* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

void extractWords(const std::string& line, BST& bst) {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
        std::string sanitizedWord;
        for (char c : word) {
            if (std::isalnum(c) || c == '-') {
                sanitizedWord += std::tolower(c);
            }
        }
        if (!sanitizedWord.empty()) {
            bst.insert(sanitizedWord);
        }
    }
}

int main() {
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output.txt" << std::endl;
        return 1;
    }

    std::vector<std::string> inputFiles = {"../data/textfile1.txt", "../data/textfile2.txt"};

    for (const std::string& inputFile : inputFiles) {
        std::ifstream inFile(inputFile);
        if (!inFile.is_open()) {
            std::cerr << "Error opening " << inputFile << std::endl;
            continue;
        }

        outputFile << "bdominiq" << std::endl;
        outputFile << inputFile << std::endl;

        BST bst;
        std::string line;
        int totalProbes = 0;
        int maxProbes = 0;

        while (std::getline(inFile, line)) {
            extractWords(line, bst);
        }

        bst.traverseAndWrite(outputFile, totalProbes, maxProbes);

        int wordCount = 0; // Count the number of words for average probe calculation
        inFile.clear();
        inFile.seekg(0); // Reset file stream for word counting

        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                wordCount++;
            }
        }

        outputFile << "Maximum number of probes: " << maxProbes << std::endl;
        outputFile << "Average number of probes: " << (wordCount > 0 ? static_cast<double>(totalProbes) / wordCount : 0) << std::endl;
        outputFile << "--------------------" << std::endl;

        inFile.close();
    }

    outputFile.close();
    return 0;
}
