#include <iostream>
#include <fstream>

struct FixationPoint {
    int id;
    int x;
    int y;
};

int processFixationPoints(std::ifstream& inputFile, FixationPoint fixationPoints[]) {
    int count = 0;
    int fixationId, x, y;

    inputFile >> fixationId >> x >> y;

    while (x != -1 || y != -1) {
        bool isDistinct = true;
        for (int i = 0; i < count; ++i) {
            if (fixationPoints[i].x == x && fixationPoints[i].y == y) {
                isDistinct = false;
                break;
            }
        }

        if (isDistinct) {
            fixationPoints[count].id = count + 1;
            fixationPoints[count].x = x;
            fixationPoints[count].y = y;
            count++;
        }

        inputFile >> fixationId >> x >> y;
    }

    return count;
}

void writeDistinctFixationPoints(std::ofstream& outputFile, const FixationPoint fixationPoints[], int count) {
    for (int i = 0; i < count; ++i) {
        outputFile << fixationPoints[i].id << " " << fixationPoints[i].x << " " << fixationPoints[i].y << std::endl;
    }
}

int main() {
    std::ifstream inputFile("data/input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input.txt" << std::endl;
        return 1;
    }

    std::ofstream outputFile("data/output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output.txt" << std::endl;
        inputFile.close();
        return 1;
    }

    outputFile << "bdominiq" << std::endl;

    int numTestCases;
    inputFile >> numTestCases;

    for (int testCase = 0; testCase < numTestCases; ++testCase) {
        const int maxSize = 100;
        FixationPoint fixationPoints[maxSize];
        int count = processFixationPoints(inputFile, fixationPoints);
        writeDistinctFixationPoints(outputFile, fixationPoints, count);
        outputFile << "**********" << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
