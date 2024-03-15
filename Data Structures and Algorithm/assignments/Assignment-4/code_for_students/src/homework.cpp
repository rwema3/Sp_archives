/*
 * homework.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: kompalli
 */

#include "homework.h"

int main(int argc, char** argv) {
	LogManager::resetLogFile();
	LogManager::writePrintfToLog(LogManager::Level::Status, "main", "In main file.");
	printf("Usage:\n\n");
	printf("./homework testCodeGeneration trainFilePath\n\n");
	printf("./homework testEncoding testASCIIFilePath huffmanCodeFilePath\n\n");
	printf("./homework testDecoding testEncodedFilePath huffmanCodeFilePath\n\n");

	if (argc < 2)
		return 0;

	int peakMem1 = getPeakRSS();
	int currMem1 = getCurrentRSS();
	printf("peakRSS = %d, currMem=%d\n", peakMem1, currMem1);
	printf("sizeof(bool) = %d \n", (int)sizeof(bool));
	printf("sizeof(int) = %d \n", (int)sizeof(int));
	printf("sizeof(char) = %d \n", (int)sizeof(char));
	printf("INT_MIN = %d, INT_MAX =%d\n", INT_MIN, INT_MAX);

	auto start = std::chrono::high_resolution_clock::now();

	if (strcmp(argv[1], "testCodeGeneration") == 1){
		/**
		 * When you initiate a memory call, always check that the memory was allotted
		 * If not, throw an error, or send an error message.
		 */
		char inputTrainFilePath[1024], outputHuffmanCodePath[1024];
		sprintf(inputTrainFilePath, "%s", argv[1]);
		sprintf(outputHuffmanCodePath, "%s.huffman.txt", inputTrainFilePath);

		if (!inputTrainFilePath){
			printf("allocation of inputPath failed\n");
			return -1;
		}
		if (!outputHuffmanCodePath){
			printf("allocation of outputPath failed\n");
			return -1;
		}

		HuffmanEncoding::generateAlphabetCode(inputTrainFilePath, outputHuffmanCodePath);
	}
	if (strcmp(argv[1], "testEncoding") == 1){
		char testASCIIFilePath[1024], huffmanCodeFilePath[1024], outFile[1024];
		sprintf(testASCIIFilePath, "%s", argv[2]);
		sprintf(huffmanCodeFilePath, "%s", argv[3]);
		sprintf(outFile, "%s.encode.txt", testASCIIFilePath);

		HuffmanEncoding::encodeText(testASCIIFilePath, huffmanCodeFilePath, outFile);
	}
	if (strcmp(argv[1], "testDecoding") == 1){
		char testEncodedFilePath[1024], huffmanCodeFilePath[1024], outFile[1024];
		sprintf(testEncodedFilePath, "%s", argv[2]);
		sprintf(huffmanCodeFilePath, "%s", argv[3]);
		sprintf(outFile, "%s.ascii.txt", testEncodedFilePath);

		HuffmanEncoding::encodeText(testEncodedFilePath, huffmanCodeFilePath, outFile);
	}
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	printf("run time =%d microseconds\n", (int) duration.count());


	int peakMem2 = getPeakRSS();
	int currMem2 = getCurrentRSS();
	printf("peakRSS = %d, currMem=%d\n", peakMem2, currMem2);
	printf("Diff peakRSS = %d, currMem=%d\n", peakMem2-peakMem1, currMem2-currMem1);

}
