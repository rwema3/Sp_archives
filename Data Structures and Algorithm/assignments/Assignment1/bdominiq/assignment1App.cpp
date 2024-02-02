#include <iostream>
#include <fstream>

int main() {
    std::ifstream inputFile("input.txt"); // Assuming you have an input file named "input.txt"
    std::ofstream outputFile("output.txt"); // Assuming you want to write to an output file named "output.txt"

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files. Check if the files exist and the program has the necessary permissions." << std::endl;
        return 1; // Return with an error code
    }

    int number_of_test_cases;
    int i;
    float t, x, y;

    // Read the number of test cases from the file
    if (!(inputFile >> number_of_test_cases)) {
        std::cerr << "Error reading the number of test cases from input.txt." << std::endl;
        inputFile.close();
        outputFile.close();
        return 1; // Return with an error code
    }

    // Write the test case number to the output file
    i = 1;
    outputFile << "Test case " << i << std::endl;

    // Read the location data from the file
    if (!(inputFile >> t >> x >> y)) {
        std::cerr << "Error reading location data from input.txt." << std::endl;
        inputFile.close();
        outputFile.close();
        return 1; // Return with an error code
    }

    // Echo the input data to the terminal
    std::cout << "Location data: " << t << " " << x << " " << y << std::endl;

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0; // Return success
}
