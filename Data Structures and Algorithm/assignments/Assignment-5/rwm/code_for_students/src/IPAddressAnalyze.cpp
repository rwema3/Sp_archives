
/*
 *      Author: kompalli
 */

// Including necessary header file for IPAddressAnalyze.h
#include "IPAddressAnalyze.h"

// Function to customize a string by copying characters from initialization to host
void strCustomizer(char *host, const char *initialization, size_t n) {
    // Initialize a counter to keep track of the number of characters copied
    size_t u = 0;
    // Iterate over the characters in the initialization string
    do {
        // If the current character in initialization is null terminator, exit the loop
        if (initialization[u] == '\0') {
            break;
        }
        // Copy the current character from initialization to host
        host[u] = initialization[u];
        // Move to the next character in both strings
        u++;
    } while (u < n); // Repeat until n characters are copied or null terminator is encountered

    // Fill the remaining space in the host string with null characters
    while (u < n) {
        host[u] = '\0';
        u++;
    }
}


// Function to evaluate two strings lexicographically
int strEvaluatorcultr(const char *string_n_1, const char *string_n_2)
{
    // Iterate over each character in the strings
    do {
        // Check the current character of string_n_1
        switch (*string_n_1) {
            // If the current character is null terminator
            case '\0':
                // Check if string_n_2 also ends here
                if (*string_n_2 == '\0')
                    return 0; // Both strings are equal
                else
                    return -1; // string_n_1 is shorter than string_n_2
            // If the current characters are different
            default:
                if (*string_n_1 != *string_n_2)
                    // Return the difference between the ASCII values of the characters
                    return *string_n_1 - *string_n_2;
                // Move to the next characters in both strings
                string_n_1++;
                string_n_2++;
                break;
        }
    // Repeat indefinitely (until a return statement is reached)
    } while (true);
}


// Structure to represent a node in the associative array
struct node_Enumeration {
    char the_point[80];         // IP address stored in the node
    unsigned int weight_datum;  // Frequency count associated with the IP address
    node_Enumeration *following; // Pointer to the next node in the linked list
    
    // Constructor for node_Enumeration
    // Initializes the node with the given IP address and frequency count
    node_Enumeration(const char *theP, unsigned int wyt) : weight_datum(wyt), following(nullptr)
    {
        // Copy the IP address string into the node's the_point array
        size_t u = 0;
        do {
            the_point[u] = theP[u];
            u++;
        } while (u < 16 && theP[u] != '\0'); // Copy up to 15 characters or until the null terminator
        
        // Fill the remaining space in the_point array with null characters
        while (u < 16) {
            the_point[u] = '\0';
            u++;
        }
    }
};

// Class for managing associative array of IP addresses
class Associative_Array
{
	static const int Array_T_Size = 4096;
	node_Enumeration *table[Array_T_Size];

	// Function to calculate hash value for IP address
	int messageDigest(const char *the_point)
{
    unsigned long chypher = 5381;
    int the_long;

    do {
        switch (*the_point) {
            case '\0':
                break;
            default:
                chypher = ((chypher << 5) + chypher) + *the_point;
                the_point++;
                break;
        }
    } while (*the_point);

    return chypher % Array_T_Size;
}

// Public methods of Associative_Array class
public:

// Constructor: Initializes the associative array by setting all table entries to nullptr
Associative_Array()
{
    for (int u = 0; u < Array_T_Size; ++u)
    {
        table[u] = nullptr;
    }
}

// Destructor: Deallocates memory by deleting all nodes in the associative array
~Associative_Array()
{
    // Iterate over each entry in the table
    int u = 0;
    do {
        // Get the entry at index u
        node_Enumeration *entry = table[u];
        // Iterate over the linked list of entries at index u
        while (entry != nullptr)
        {
            // Store the current entry's pointer to delete it later
            node_Enumeration *prev = entry;
            // Move to the next entry in the linked list
            entry = entry->following;
            // Delete the previous entry
            delete prev;
        }
        // Move to the next index in the table
        u++;
    } while (u < Array_T_Size); // Continue until the end of the table is reached
}


// Function to add an entry to the associative array
void addEntry(const char *the_point, unsigned int weight_datum)
{
    // Calculate the hash value for the given point (IP address)
    int hashValue = messageDigest(the_point);
    // Retrieve the entry at the calculated hash value from the table
    node_Enumeration *entry = table[hashValue];
    // Keep track of the previous entry in the linked list
    node_Enumeration *prev = nullptr;

    // Initialize flags to track whether the entry is added or found
    bool entryAdded = false; // Flag to indicate if the entry is added to the table
    bool entryFound = false; // Flag to indicate if the entry is found in the table

    // Iterate until the entry is added to the table
    do {
        // Check the status of entryAdded flag
        switch (entryAdded) {
            // If entry is not yet added
            case false:
                // If the entry at the calculated hash value is null
                if (entry == nullptr) {
                    // Create a new entry with the given point and weight_datum
                    entry = new node_Enumeration(the_point, weight_datum);
                    // If prev is null, set the table[hashValue] to the new entry
                    if (prev == nullptr)
                        table[hashValue] = entry;
                    // Otherwise, set the following of prev to the new entry
                    else
                        prev->following = entry;
                    // Set entryAdded flag to true indicating entry is added
                    entryAdded = true;
                } else {
                    // Check if the point of the current entry matches the given point
                    entryFound = (strEvaluatorcultr(entry->the_point, the_point) == 0);
                    // If the entry is found
                    if (entryFound) {
                        // Update the weight_datum of the existing entry
                        entry->weight_datum += weight_datum;
                        // Set entryAdded flag to true indicating entry is added
                        entryAdded = true;
                    } else {
                        // Move to the next entry in the linked list
                        prev = entry;
                        entry = entry->following;
                    }
                }
                break;
            default:
                break;
        }
    } while (!entryAdded); // Continue until entry is added
}


int receive_entire_N(node_Enumeration **entire_N, int reach_N)
{
    // Initialize variables to keep track of the number of nodes and the current index
    int numberingNd = 0; // Number of nodes added to entire_N
    int u = 0;           // Current index in the table

    // Iterate through the table until the end or until reach_N nodes are added
    do {
        // Get the node at index u in the table
        node_Enumeration *entry = table[u];
        // Iterate through the linked list of nodes at index u
        while (entry != nullptr)
        {
            // Check if the number of nodes added is less than reach_N
            if (numberingNd < reach_N)
            {
                // Add the current node to the entire_N array and increment the count
                entire_N[numberingNd++] = entry;
            }
            // Move to the next node in the linked list
            entry = entry->following;
        }
        // Move to the next index in the table
        u++;
    } while (u < Array_T_Size && numberingNd < reach_N); // Repeat until the end of table or reach_N nodes are added

    // Return the number of nodes added to entire_N
    return numberingNd;
}

};

// Function to parse log file and add IP addresses to associative array
void parseLog(const char *inputFilePath, Associative_Array *addressCatalogIp)
{
    // Open the log file for reading
    FILE *file = fopen(inputFilePath, "r");
    // Check if the file is successfully opened
    if (!file)
    {
        // If opening the file fails, throw an exception with an error message
        throw std::ios_base::failure("There's an Error in the opening of file: " + std::string(inputFilePath));
    }

    // Initialize variables to store data from each line of the log file
    char horizontal[1024]; // Buffer to store each line of the file
    char theAdrrs[80];     // Buffer to store IP address
    unsigned int numering; // Variable to store frequency count

    // Read lines from the file until the end of file is reached
    do {
        // Read a line from the file into the horizontal buffer
        if (!fgets(horizontal, sizeof(horizontal), file))
            break;

        // Extract IP address and frequency count from the line
        if (sscanf(horizontal, "%15s %u", theAdrrs, &numering) != 2)
        {
            // If the line doesn't contain valid data, skip it and continue to the next line
            continue;
        }
        // Add the extracted IP address and frequency count to the associative array
        addressCatalogIp->addEntry(theAdrrs, numering);
    } while (!feof(file)); // Repeat until end of file is reached

    // Close the file
    fclose(file);
}


// Function to swap two nodes in a linked list
void permuteListNode(node_Enumeration **x, node_Enumeration **y)
{
    if (*x != *y) {
        (*x) = (node_Enumeration *)((uintptr_t)(*x) ^ (uintptr_t)(*y));
        (*y) = (node_Enumeration *)((uintptr_t)(*x) ^ (uintptr_t)(*y));
        (*x) = (node_Enumeration *)((uintptr_t)(*x) ^ (uintptr_t)(*y));
    }
}

// Function to partition array of nodes based on weight_datum
int segmenting(node_Enumeration *Collection_arr[], int down, int upper)
{
    unsigned int thresholdValue = Collection_arr[upper]->weight_datum;
    const char *axisKey = Collection_arr[upper]->the_point;
    int u = down - 1;
    int t = down;
    
    do {
        bool hasMoreOccurrences = Collection_arr[t]->weight_datum > thresholdValue;
        bool exactOccurrencesOrUnderIP = Collection_arr[t]->weight_datum == thresholdValue && strEvaluatorcultr(Collection_arr[t]->the_point, axisKey) < 0;

        if (hasMoreOccurrences || exactOccurrencesOrUnderIP)
        {
            u++;
            permuteListNode(&Collection_arr[u], &Collection_arr[t]);
        }
        t++;
    } while (t <= upper - 1);

    permuteListNode(&Collection_arr[u + 1], &Collection_arr[upper]);
    return u + 1;
}

// Function to perform quicksort on array of nodes
void incrementalSort(node_Enumeration *Collection_arr[], int down, int upper)

{
	if (down < upper)
	{
		int qurr = segmenting(Collection_arr, down, upper);

		incrementalSort(Collection_arr, down, qurr - 1);
		incrementalSort(Collection_arr, qurr + 1, upper);
	}
}


// Function to perform insertion sort on array of nodes
void nestedSort(node_Enumeration *Collection_arr[], int the_beggining, int the_closure)
{
	// Initialize the variable u to start from the beginning index + 1
	int u = the_beggining + 1;

	// Iterate through the array from the second element to the closure
	do {
		// Store the current node to be sorted
		node_Enumeration *the_point = Collection_arr[u];
		// Initialize a variable t to the index before the current element
		int t = u - 1;
		// Shift elements greater than the current node to the right
		// until finding the correct position for the current node
		while (t >= the_beggining && strEvaluatorcultr(Collection_arr[t]->the_point, the_point->the_point) > 0)
		{
			Collection_arr[t + 1] = Collection_arr[t];
			t = t - 1;
		}
		// Place the current node in its correct position
		Collection_arr[t + 1] = the_point;
		// Move to the next element
		u++;
	} while (u <= the_closure); // Continue until reaching the closure index
}

// Function to classify IP addresses based on their frequency
void classifyTheAddreses(node_Enumeration *Collection_arr[], int numering)
{
	// Sort the Collection_arr based on the frequency of IP addresses
	incrementalSort(Collection_arr, 0, numering - 1);
	// Initialize the beginning index of a group of IP addresses with the same frequency
	int the_beggining = 0;
	// Iterate through the Collection_arr
	for (int u = 1; u <= numering; u++)
	{
		// Check if we've reached the end of the array or if the frequency of the current IP address differs from the previous one
		if (u == numering || Collection_arr[u]->weight_datum != Collection_arr[the_beggining]->weight_datum)
		{
			// If there's more than one IP address with the same frequency, sort them
			if (u - the_beggining > 1)
			{
				nestedSort(Collection_arr, the_beggining, u - 1);
			}
			// Update the beginning index for the next group of IP addresses
			the_beggining = u;
		}
	}
}

// Function to serialize the top N IP addresses to a file
void serializeToDestination(const char *outputFilePath, node_Enumeration *topN[], int n)
{
	// Open the output file for writing
	FILE *outFile = fopen(outputFilePath, "w");
	// Check if the file is successfully opened
	if (!outFile)
	{
		// If opening the file fails, construct an error message and throw an exception
		char throwing_msg[1024];
		sprintf(throwing_msg, "Cannot open output file for writing: %s", outputFilePath);
		throw std::ios_base::failure(throwing_msg);
	}

	// Initialize variables to keep track of ranking and counts
	unsigned int lastCount = UINT_MAX; // Keep track of the last count
	int finalPosition = 1;              // Final position of the IP address
	int presentranking = 1;             // Current ranking of the IP address

	int u = 0;
	// Loop through the top N IP addresses or until the counts are the same as the previous one
	do {
		// Update the final position if the count changes
		if (topN[u]->weight_datum != lastCount)
		{
			finalPosition = presentranking;
		}
		// Write the IP address along with its position and count to the output file
		fprintf(outFile, "%d, %s %u\n", finalPosition, topN[u]->the_point, topN[u]->weight_datum);

		// Update lastCount with the current count of the IP address
		lastCount = topN[u]->weight_datum;
		// Increment the ranking
		presentranking++;
		// Move to the next IP address
		u++;
	} while (u < n || (u > 0 && topN[u]->weight_datum == topN[u - 1]->weight_datum));

	// Close the output file
	fclose(outFile);
}


// Function to get most frequent IP addresses from a log file
void IPAddressAnalyzer::getMostFrequentIPAddress(char *inputFilePath, char *outputFilePath, int n)
{
	// Create an associative array to store IP addresses and their frequencies
	Associative_Array addressCatalogIp;

	try
	{
		// Parse the log file and populate the associative array with IP addresses
		parseLog(inputFilePath, &addressCatalogIp);
		
		// Define a maximum quota for IP addresses
		const int IP_QUOTA = 1000000;
		// Declare an array to hold pointers to nodes of the associative array
		node_Enumeration *entire_N[IP_QUOTA] = {nullptr};
		// Retrieve all nodes from the associative array and store them in entire_N
		int numberingNd = addressCatalogIp.receive_entire_N(entire_N, IP_QUOTA);
		// Classify the addresses based on their frequencies
		classifyTheAddreses(entire_N, numberingNd);

		// Check the number of addresses found
		switch (numberingNd) {
			// If no addresses found, log a message indicating so
			case 0:
				LogManager::writePrintfToLog(LogManager::Level::Status,
									 "IPAddressAnalyzer::getMostFrequentIPAddress",
									 "No IP addresses found in the log file: %s", inputFilePath);
				break;
			// If addresses are found, serialize them to the output file
			default:
				serializeToDestination(outputFilePath, entire_N, std::min(n, numberingNd));
				// Log a message indicating successful processing of the file
				LogManager::writePrintfToLog(LogManager::Level::Status,
									 "IPAddressAnalyzer::getMostFrequentIPAddress",
									 "Done Processing The Files %s", inputFilePath);
				break;
		}
	}
	// Catch any exceptions that occur during the process and handle them
	catch (const std::exception &e)
	{
		// Log the exception message
		std::cerr << "There is a mistake at: " << e.what() << std::endl;
	}
}
