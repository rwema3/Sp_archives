#include <iostream>
#include <fstream>
#include <utility>

struct FixationPoint {
    int id;
    int x;
    int y;
};

// Function to process fixation points and return the number of distinct points
int processFixationPoints(std::ifstream& inputFile, FixationPoint fixationPoints[]) {
    int count = 0;
    int fixationId, x, y;

    inputFile >> fixationId >> x >> y;

    while (x != -1 || y != -1) {
        // Check if the point is distinct
        bool isDistinct = true;
        for (int i = 0; i < count; ++i) {
            if (fixationPoints[i].x == x && fixationPoints[i].y == y) {
                isDistinct = false;
                break;
            }
        }

        if (isDistinct) {
            fixationPoints[count++] = {count, x, y};
        }

        inputFile >> fixationId >> x >> y;
    }

    return count;
}

// Function to write distinct fixation points to the output file
void writeDistinctFixationPoints(std::ofstream& outputFile, const FixationPoint fixationPoints[], int count) {
    for (int i = 0; i < count; ++i) {
        outputFile << fixationPoints[i].id << " " << fixationPoints[i].x << " " << fixationPoints[i].y << std::endl;
    }
}

int main() {
    // Open input file
    std::ifstream inputFile("data/input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input.txt" << std::endl;
        return 1;
    }

    // Open output file
    std::ofstream outputFile("data/output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output.txt" << std::endl;
        inputFile.close();
        return 1;
    }

    // Output the Andrew ID
    outputFile << "bdominiq" << std::endl;

    int numTestCases;
    inputFile >> numTestCases;

    for (int testCase = 0; testCase < numTestCases; ++testCase) {
        // Process fixation points for the current test case
        const int maxSize = 100; // Adjust the size based on your requirements
        FixationPoint fixationPoints[maxSize];
        int count = processFixationPoints(inputFile, fixationPoints);

        // Output the distinct fixation points for the current test case
        writeDistinctFixationPoints(outputFile, fixationPoints, count);

        // Output the line of dashes to separate test cases
        outputFile << "**********" << std::endl;
    }

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}
