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

    void traverseInOrder(TreeNode* node, std::ofstream& outputFile) {
        if (node == nullptr) return;
        traverseInOrder(node->left, outputFile);
        outputFile << node->word << " " << node->count << " (" << node->count - 1 << ")" << std::endl;
        traverseInOrder(node->right, outputFile);
    }

    int calculateProbes(TreeNode* node, const std::string& word, int probes) {
        if (node == nullptr) return probes;
        if (word < node->word) {
            return calculateProbes(node->left, word, probes + 1);
        } else if (word > node->word) {
            return calculateProbes(node->right, word, probes + 1);
        } else {
            return probes + 1;
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(const std::string& word) {
        insertWord(root, word);
    }

    void traverseAndWrite(std::ofstream& outputFile) {
        traverseInOrder(root, outputFile);
    }

    void calculateProbeStats(const std::string& word, int& totalProbes, int& maxProbes) {
        int probes = calculateProbes(root, word, 0);
        totalProbes += probes;
        maxProbes = std::max(maxProbes, probes);
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
        int wordCount = 0;

        while (std::getline(inFile, line)) {
            extractWords(line, bst);
        }

        bst.traverseAndWrite(outputFile);

        outputFile << "Maximum number of probes: " << maxProbes << std::endl;
        outputFile << "Average number of probes: " << (wordCount > 0 ? static_cast<double>(totalProbes) / wordCount : 0) << std::endl;
        outputFile << "--------------------" << std::endl;

        inFile.close();
    }

    outputFile.close();
    return 0;
}
