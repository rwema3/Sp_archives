/*
Author: Bagirishya Rwema Dominique

The Solution reads fixation points from an input file, sorts them based on their coordinates, and writes the sorted points to an output file.
It handles multiple test cases independently. Input is provided via "input.txt", with test cases containing fixation points' identifiers,
x-coordinates, and y-coordinates. Output is written to "output.txt" with sorted fixation points separated by asterisks.

I employed the bubble sort algorithm to sort fixation points. then iterates through the array, comparing adjacent points based on their coordinates,
 and swaps if necessary to achieve ascending order. Testing included various scenarios with different fixation point counts, coordinates, and edge cases like empty files.
The bubble sort algorithm has a time complexity of O(n^2) in the worst-case scenario, where n is the number of fixation points. Despite its simplicity,
it's space-efficient with O(1) complexity, making it suitable for small datasets like this one.


*/

#include <iostream>
#include <fstream>

struct FixationPoint {
    int number;
    int x;
    int y;
};

void bubbleSort(FixationPoint fixationPoints[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (fixationPoints[j].x > fixationPoints[j + 1].x || 
                (fixationPoints[j].x == fixationPoints[j + 1].x && fixationPoints[j].y > fixationPoints[j + 1].y)) {
                FixationPoint temp = fixationPoints[j];
                fixationPoints[j] = fixationPoints[j + 1];
                fixationPoints[j + 1] = temp;
            }
        }
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
        FixationPoint fixationPoints[100]; // assuming maximum 100 fixation points

        int fixationId, x, y;
        int count = 0;

        inputFile >> fixationId >> x >> y;

        while (x != -1 || y != -1) {
            fixationPoints[count++] = {fixationId, x, y};
            inputFile >> fixationId >> x >> y;
        }

        bubbleSort(fixationPoints, count);

        for (int i = 0; i < count; ++i) {
            outputFile << fixationPoints[i].number << " " << fixationPoints[i].x << " " << fixationPoints[i].y << std::endl;
        }

        outputFile << "*************" << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
