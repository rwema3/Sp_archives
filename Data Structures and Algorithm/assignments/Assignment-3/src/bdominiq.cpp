#include <iostream>
#include <fstream>

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
    int uniqueWordCount; // To track the number of unique words

    void traverseInOrder(TreeNode* node, std::ofstream& outputFile, int& totalProbes, int& maxProbes, int currentProbe) {
        if (node == nullptr) return;
        traverseInOrder(node->left, outputFile, totalProbes, maxProbes, currentProbe + 1);
        outputFile << node->word << " " << node->count << " (" << currentProbe << ")" << std::endl;
        totalProbes += currentProbe;
        maxProbes = std::max(maxProbes, currentProbe);
        traverseInOrder(node->right, outputFile, totalProbes, maxProbes, currentProbe + 1);
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

    void traverseAndWrite(std::ofstream& outputFile, int& totalProbes, int& maxProbes) {
        int currentProbe = 1; // Start counting from 1 instead of 0
        traverseInOrder(root, outputFile, totalProbes, maxProbes, currentProbe);
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

    // Assuming data/textfile1.txt and data/textfile2.txt exist in the current directory
    const char* inputFiles[] = {"../data/textfile1.txt", "../data/textfile2.txt"};
    const int numFiles = 2;

    outputFile << "bdominiq" << std::endl;

    for (int i = 0; i < numFiles; ++i) {
        std::ifstream inFile(inputFiles[i]);
        if (!inFile.is_open()) {
            std::cerr << "Error opening " << inputFiles[i] << std::endl;
            continue;
        }

        outputFile << inputFiles[i] << std::endl;

        BST bst;
        std::string line;
        int totalProbes = 0;
        int maxProbes = 0;

        while (std::getline(inFile, line)) {
            std::string word;
            int start = 0;
            for (int i = 0; i <= line.size(); ++i) {
                if (i == line.size() || !std::isalnum(line[i]) || line[i] == '-') {
                    if (i > start) {
                        std::string sanitizedWord = line.substr(start, i - start);
                        for (char& c : sanitizedWord) {
                            c = std::tolower(c);
                        }
                        if (!sanitizedWord.empty()) {
                            bst.insert(sanitizedWord);
                        }
                    }
                    start = i + 1;
                }
            }
        }

        bst.traverseAndWrite(outputFile, totalProbes, maxProbes);

        outputFile << "Maximum number of probes: " << maxProbes << std::endl;
        outputFile << "Average number of probes: " << (bst.getUniqueWordCount() > 0 ? static_cast<double>(totalProbes) / bst.getUniqueWordCount() : 0) << std::endl;

        outputFile << "--------------------" << std::endl;

        inFile.close();
    }

    outputFile.close();
    return 0;
}
