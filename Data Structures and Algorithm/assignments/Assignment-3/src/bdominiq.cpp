#include <iostream>
#include <fstream>
#include <string>
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
    int uniqueWordCount; 

    void calculateProbes(TreeNode* node, int& totalProbes, int& maxProbes, int currentProbe) {
        if (node == nullptr) return;
        calculateProbes(node->left, totalProbes, maxProbes, currentProbe + 1);
        totalProbes += currentProbe;
        maxProbes = std::max(maxProbes, currentProbe);
        calculateProbes(node->right, totalProbes, maxProbes, currentProbe + 1);
    }

    void writeTraverseInOrder(TreeNode* node, std::ofstream& outputFile, int currentProbe) {
        if (node == nullptr) return;
        writeTraverseInOrder(node->left, outputFile, currentProbe + 1);
        outputFile << node->word << " " << node->count << " (" << currentProbe << ")" << std::endl;
        writeTraverseInOrder(node->right, outputFile, currentProbe + 1);
    }

public:
    BST() : root(nullptr), uniqueWordCount(0) {}

    void insert(const std::string& word) {
        TreeNode** current = &root;
        while (*current != nullptr) {
            if (word < (*current)->word) {
                current = &((*current)->left);
            } else if (word > (*current)->word) {
                current = &((*current)->right);
            } else {
                (*current)->count++;
                return;
            }
        }
        *current = new TreeNode(word);
        uniqueWordCount++;
    }

    void calculateStats(int& totalProbes, int& maxProbes) {
        totalProbes = 0;
        maxProbes = 0;
        calculateProbes(root, totalProbes, maxProbes, 1); // Start from 1
    }

    void traverseAndWrite(std::ofstream& outputFile) {
        writeTraverseInOrder(root, outputFile, 1); // Start from 1
    }

    int getUniqueWordCount() const {
        return uniqueWordCount;
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

int main() {
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output.txt" << std::endl;
        return 1;
    }

    const char* inputFiles[] = {"../data/textfile1.txt", "../data/textfile2.txt"};
    const int numFiles = 2;

    outputFile << "bdominiq" << std::endl;

    for (int i = 0; i < numFiles; ++i) {
        std::ifstream inFile(inputFiles[i]);
        if (!inFile.is_open()) {
            std::cerr << "Error opening " << inputFiles[i] << std::endl;
            continue;
        }

        BST bst;
        std::string line;
        while (std::getline(inFile, line)) {
            std::string word;
            int start = 0;
            for (int i = 0; i <= line.size(); ++i) {
                if (i == line.size() || !std::isalnum(line[i])) {
                    if (i > start) {
                        word = line.substr(start, i - start);
                        for (char& c : word) {
                            c = std::tolower(c);
                        }
                        bst.insert(word);
                    }
                    start = i + 1;
                }
            }
        }

        int totalProbes = 0, maxProbes = 0;
        bst.calculateStats(totalProbes, maxProbes);

        outputFile << inputFiles[i] << std::endl;
        outputFile << "Maximum number of probes: " << maxProbes << std::endl;
        outputFile << "Average number of probes: " << (bst.getUniqueWordCount() > 0 ? static_cast<double>(totalProbes) / bst.getUniqueWordCount() : 0) << std::endl;

        bst.traverseAndWrite(outputFile);

        outputFile << "--------------------" << std::endl;

        inFile.close();
    }

    outputFile.close();
    return 0;
}
