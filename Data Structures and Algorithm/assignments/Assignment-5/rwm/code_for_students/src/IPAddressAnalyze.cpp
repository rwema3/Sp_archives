#include "IPAddressAnalyze.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Structure to store IP address and its count
struct IPAddressCount {
    char ip_address[16]; // Assuming IPv4 addresses only
    int count;
};

// Function to compare IPAddressCount structs
bool compareIPAddressCount(const IPAddressCount& a, const IPAddressCount& b) {
    if (a.count == b.count) {
        // Compare IP addresses lexicographically if counts are equal
        return std::strcmp(a.ip_address, b.ip_address) < 0;
    }
    return a.count > b.count; // Sort in descending order of count
}

void IPAddressAnalyzer::getMostFrequentIPAddress(char* inputFilePath, char* outputFilePath, int n) {
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open input file: " << inputFilePath << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file: " << outputFilePath << std::endl;
        return;
    }

    // Array to store IP addresses and their counts
    const int MAX_IP_COUNT = 1000; // Assuming a maximum of 1000 unique IP addresses
    IPAddressCount ipCounts[MAX_IP_COUNT];
    int ipCountIndex = 0;

    // Read input file line by line
    char line[256]; // Assuming maximum line length
    while (inputFile.getline(line, sizeof(line))) {
        char ip_address[16]; // Assuming IPv4 addresses only
        int count;
        if (std::sscanf(line, "%[^,], %d", ip_address, &count) == 2) {
            // Check if IP address already exists
            bool found = false;
            for (int i = 0; i < ipCountIndex; ++i) {
                if (std::strcmp(ipCounts[i].ip_address, ip_address) == 0) {
                    ipCounts[i].count += count;
                    found = true;
                    break;
                }
            }
            // If IP address not found, add it to the array
            if (!found) {
                std::strcpy(ipCounts[ipCountIndex].ip_address, ip_address);
                ipCounts[ipCountIndex].count = count;
                ipCountIndex++;
            }
        }
    }

    // Sort the array based on counts and IP addresses
    for (int i = 0; i < ipCountIndex; ++i) {
        for (int j = i + 1; j < ipCountIndex; ++j) {
            if (compareIPAddressCount(ipCounts[j], ipCounts[i])) {
                IPAddressCount temp = ipCounts[i];
                ipCounts[i] = ipCounts[j];
                ipCounts[j] = temp;
            }
        }
    }

    int current_rank = 0;
    int previous_count = -1;
    for (int i = 0; i < ipCountIndex && i < n; ++i) {
        if (ipCounts[i].count != previous_count) {
            current_rank = i + 1; // Update current rank if count changes
            previous_count = ipCounts[i].count;
        }

        outputFile << current_rank << ", " << ipCounts[i].ip_address << ", " << ipCounts[i].count << std::endl;
    }



    inputFile.close();
    outputFile.close();
}
