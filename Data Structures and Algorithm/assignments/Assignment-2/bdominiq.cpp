#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct FixationPoint {
    int number;
    int x;
    int y;
};

bool compareFixationPoints(const FixationPoint &a, const FixationPoint &b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input.txt" << std::endl;
        return 1;
    }

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output.txt" << std::endl;
        inputFile.close();
        return 1;
    }

    outputFile << "bdominiq" << std::endl;

    int numTestCases;
    inputFile >> numTestCases;

    for (int testCase = 0; testCase < numTestCases; ++testCase) {
        std::vector<FixationPoint> fixationPoints;

        int fixationId, x, y;
        inputFile >> fixationId >> x >> y;

        while (x != -1 || y != -1) {
            fixationPoints.push_back({fixationId, x, y});
            inputFile >> fixationId >> x >> y;
        }

        std::sort(fixationPoints.begin(), fixationPoints.end(), compareFixationPoints);

        for (const auto &point : fixationPoints) {
            outputFile << point.number << " " << point.x << " " << point.y << std::endl;
        }

        outputFile << "*************" << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
