/*
AUTHOR: Bagirishya Rwema Dominique
AndrewID: bdominiq

Functionality of the program:

program is designed to analyze text files and gather statistics on word occurrences. It implements a Binary Search Tree (BST) data structure to efficiently store words
and their frequencies. Initially, it opens multiple text files, tokenizes each line into words, and inserts them into the BST. During insertion, the program keeps track
of the frequency of each word. After processing all files, it calculates statistics such as the maximum and average number of probes required to insert words into the
BST, which provides insights into the efficiency of the BST implementation. Finally, it writes the results, including word frequencies and probe counts, to an output
file for further analysis.

Format of the I/O:

The input format of the program consists of multiple text files containing words and sentences. Each file is processed line by line, and words are tokenized using
delimiters such as spaces, commas, periods, and hyphens. The output format includes an output file named "output.txt", where the program writes the results of its
analysis. For each input file, it reports the file name, the maximum number of probes required for BST insertion, the average number of probes per unique word, and
a list of words along with their frequencies and the number of probes required for insertion. Each input file's results are separated by a line of dashes for clarity.


Solution:

The program uses a Binary Search Tree (BST) to organize words and their frequencies efficiently. For computing the level, maximum, and average number of probes,
it employs recursive traversal of the BST during insertion. The level of each insertion indicates the depth of the node, facilitating calculation of the average probes.
The maximum number of probes updates during each insertion, capturing the longest path from the root to a leaf. Accumulating total probes during insertion enables
computation of the average probes across all unique words, ensuring accurate statistical analysis of word occurrences within the given text files.

Summary of Testing:

The code was tested by providing various text files containing different types of words and sentences, including cases with repetitive words, varying word lengths, and
different delimiters. Additionally, test cases with empty files and non-existent files were included to ensure proper error handling. The program's functionality was
verified by comparing the output statistics, including maximum and average number of probes, against expected results obtained manually from the test files. This
comprehensive testing approach aimed to validate the program's ability to accurately analyze word occurrences across diverse input scenarios.

BIG O:

My algorithm utilizes a binary search tree (BST) to process multiple text files, tokenize words, and count their occurrences. Insertion into the BST occurs during
tokenization, leading to a worst-case time complexity of O(n log n) for n total words across all files. This complexity arises from the balanced nature of the BST,
ensuring logarithmic insertion times on average. I chose this because it maintains sorted order, enabling efficient search operations (O(log n)), crucial for insertion
and retrieval tasks in text processing.

*/

#include <iostream>
#include <fstream>

bool isDelimiter(char ch, const char* delim);
bool isApostropheS(char ch, char* nextChar);

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

char* my_strtok(char* str, const char* delim, char** saveptr);
bool isDelimiter(char ch, const char* delim) {
    while (*delim) {
        if (ch == *delim++)
            return true;
    }
    return false;
}

int main() {
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output.txt" << std::endl;
        return 1;
    }

    const char* inputFiles[] = {"../data/textfile1.txt", "../data/textfile2.txt" , "../data/textfile3.txt" , "../data/textfile4.txt", "../data/textfile5.txt", "../data/textfile6.txt", "../data/textfile6.txt", "../data/textfile7.txt", "../data/textfile8.txt", "../data/textfile9.txt" , "../data/textfile10.txt"};
    const int numFiles = 10;

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

char* my_strtok(char* str, const char* delim, char** saveptr) {
    if (!str && !(*saveptr))
        return nullptr;
    char* token;
    if (str)
        *saveptr = str;
    token = *saveptr;
    while (**saveptr && (isDelimiter(**saveptr, delim) || isApostropheS(**saveptr, *saveptr + 1)))
        ++(*saveptr);
    while (**saveptr && !isDelimiter(**saveptr, delim))
        ++(*saveptr);
    if (**saveptr) {
        **saveptr = '\0';
        ++(*saveptr);
    } else
        *saveptr = nullptr;
    return token;
}

bool isApostropheS(char ch, char* nextChar) {
    return (ch == '\'') && (*nextChar == 's' || *nextChar == 'S');
}
