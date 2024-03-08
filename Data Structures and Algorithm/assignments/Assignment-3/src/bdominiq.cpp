#include <iostream>
#include <fstream>

struct TreeNode {
    char* word;
    int count;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const char* w) : count(1), left(nullptr), right(nullptr) {
        int len = 0;
        const char* temp = w;
        while (*temp++) len++;
        word = new char[len + 1];
        for (int i = 0; i <= len; ++i) {
            word[i] = std::tolower(w[i]);
        }
    }

    ~TreeNode() {
        delete[] word;
    }
};

class BST {
private:
    TreeNode* root;
    int uniqueWordCount; 

    void calculateProbes(TreeNode* node, int& totalProbes, int& maxProbes, int currentProbe) {
        if (node == nullptr) return;
        calculateProbes(node->left, totalProbes, maxProbes, currentProbe + 1);
        totalProbes += currentProbe;
        if (currentProbe > maxProbes)
            maxProbes = currentProbe;
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

    void insert(const char* word) {
        TreeNode** current = &root;
        while (*current != nullptr) {
            int cmp = compareStrings(word, (*current)->word);
            if (cmp < 0) {
                current = &((*current)->left);
            } else if (cmp > 0) {
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
        calculateProbes(root, totalProbes, maxProbes, 1);
    }

    void traverseAndWrite(std::ofstream& outputFile) {
        writeTraverseInOrder(root, outputFile, 1);
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

    int compareStrings(const char* str1, const char* str2) {
        while (*str1 && std::tolower(*str1) == std::tolower(*str2)) {
            ++str1;
            ++str2;
        }
        return std::tolower(*str1) - std::tolower(*str2);
    }
};

bool isDelimiter(char ch, const char* delim) {
    while (*delim) {
        if (ch == *delim++)
            return true;
    }
    return false;
}

char* my_strtok(char* str, const char* delim, char** saveptr) {
    if (!str && !(*saveptr))
        return nullptr;
    char* token;
    if (str)
        *saveptr = str;
    token = *saveptr;
    while (**saveptr && !isDelimiter(**saveptr, delim))
        ++(*saveptr);
    if (**saveptr) {
        **saveptr = '\0';
        ++(*saveptr);
    } else
        *saveptr = nullptr;
    return token;
}

int main() {
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output.txt" << std::endl;
        return 1;
    }

    const char* inputFiles[] = {"../data/textfile1.txt", "../data/textfile2.txt", "../data/textfile3.txt", "../data/textfile4.txt"};
    const int numFiles = 4;

    outputFile << "bdominiq" << std::endl;

    for (int i = 0; i < numFiles; ++i) {
        std::ifstream inFile(inputFiles[i]);
        if (!inFile.is_open()) {
            std::cerr << "Error opening " << inputFiles[i] << std::endl;
            continue;
        }

        BST bst;
        char line[1024];
        char* context = nullptr;
        while (inFile.getline(line, 1024)) {
            char* word = my_strtok(line, " ,.-", &context);
            while (word != nullptr) {
                bst.insert(word);
                word = my_strtok(nullptr, " ,.-", &context);
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
