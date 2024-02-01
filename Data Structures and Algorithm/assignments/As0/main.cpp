#include <iostream>
#include <fstream>

int main() {
    // Open the input file
    std::ifstream inputFile("input.txt");

    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input.txt" << std::endl;
        return 1; // Return with an error code
    }

    // Read and print each line from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }

    // Close the file
    inputFile.close();

    return 0; // Return success
}
