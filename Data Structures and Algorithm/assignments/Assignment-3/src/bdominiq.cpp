#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

struct TreeNode {
    string word;
    int count;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string w) : word(w), count(1), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    void insert(TreeNode*& node, const string& word) {
        if (node == nullptr) {
            node = new TreeNode(word);
        } else if (word < node->word) {
            insert(node->left, word);
        } else if (word > node->word) {
            insert(node->right, word);
        } else {
            node->count++;
        }
    }

    void traverse(TreeNode* node, ofstream& outFile, int& totalProbes, int currentProbes) {
        if (node == nullptr) return;
        traverse(node->left, outFile, totalProbes, currentProbes + 1);
        outFile << node->word << " " << node->count << " (" << currentProbes << ")" << endl;
        totalProbes += currentProbes;
        traverse(node->right, outFile, totalProbes, currentProbes + 1);
    }

    int maxDepth(TreeNode* node) {
        if (node == nullptr) return 0;
        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);
        return 1 + max(leftDepth, rightDepth);
    }

public:
    BST() : root(nullptr) {}

    void insert(const string& word) {
        string lowercase_word = word;
        transform(lowercase_word.begin(), lowercase_word.end(), lowercase_word.begin(), ::tolower);
        insert(root, lowercase_word);
    }

    void writeToFile(ofstream& outFile, const string& filename) const {
        outFile << filename << endl;
        int totalProbes = 0;
        int totalWords = 0;
        traverse(root, outFile, totalProbes, 0);
        totalWords = totalCount();
        outFile << "Maximum number of probes: " << maxDepth(root) << endl;
        outFile << "Average number of probes: " << fixed << setprecision(1) << (double)totalProbes / totalWords << endl;
        outFile << "--------------------" << endl;
    }

    int totalCount() const {
        return totalCount(root);
    }

    int totalCount(TreeNode* node) const {
        if (node == nullptr) return 0;
        return node->count + totalCount(node->left) + totalCount(node->right);
    }
};

string extractWord(const string& str) {
    string word;
    for (char c : str) {
        if (isalnum(c) || (c == '-' && !word.empty())) {
            word += tolower(c);
        } else {
            break;
        }
    }
    return word;
}

int main() {
    vector<string> filenames;
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        filenames.push_back(line);
    }

    unordered_map<string, BST> fileWords;

    for (size_t i = 0; i < filenames.size(); ++i) {
        ifstream file(filenames[i]);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filenames[i] << endl;
            continue;
        }

        string word;
        while (file >> word) {
            string cleaned_word;
            for (char c : word) {
                if (isalnum(c) || (c == '-' && !cleaned_word.empty())) {
                    cleaned_word += tolower(c);
                } else {
                    break;
                }
            }
            if (!cleaned_word.empty()) {
                fileWords[filenames[i]].insert(cleaned_word);
            }
        }
        file.close();
    }

    for (const auto& entry : fileWords) {
        entry.second.writeToFile(outputFile, entry.first);
    }

    inputFile.close();
    outputFile.close();

    cout << "Output has been written to output.txt." << endl;

    return 0;
}
