#include <iostream>
#include <fstream>

int main() {
    std::ofstream outputFile("output.txt"); // Assuming you want to write to an output file named "output.txt"

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output.txt for writing. Check if the program has the necessary permissions." << std::endl;
        return 1; // Return with an error code
    }

    // Write one or more integers to the file
    int num1 = 92;
    int num2 = 72;

    // Write the integers to the file
    outputFile << num1 << " " << num2 << std::endl;

    // Close the file
    outputFile.close();

    std::cout << "Integers written to output.txt successfully." << std::endl;

    return 0; // Return success
}
