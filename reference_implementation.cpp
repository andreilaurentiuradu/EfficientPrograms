#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cerrno> // For errno
#include <cstring> // For strerror




// std::string line;
// while (std::getline(file, line)) { // Read the file line by line
//     std::cout << line << std::endl; // Process the line (e.g., print it)
// }

// file.close(); // Close the file
// return 0;

// Helper function to read CSV files into a vector of string vectors
std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) { // Check if the file opened successfully
        std::cerr << "Error: Could not open the file." << std::endl;
        std::cerr << "Reason: " << strerror(errno) << std::endl;
    }

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ',')) {
            row.push_back(field);
        }
        data.push_back(row);
    }

    return data;
}

// Multi-way join using nested loops
std::vector<std::vector<std::string>> multiwayJoin(
    const std::string& file1, const std::string& file2, 
    const std::string& file3, const std::string& file4
) {
    auto data1 = readCSV(file1);
    auto data2 = readCSV(file2);
    auto data3 = readCSV(file3);
    auto data4 = readCSV(file4);

    std::vector<std::vector<std::string>> result;

    // Perform the join using nested loops
    for (const auto& row1 : data1) {
        for (const auto& row2 : data2) {
            if (row1[0] == row2[0]) { // Join on first field of file1 and file2
                for (const auto& row3 : data3) {
                    if (row1[0] == row3[0]) { // Join on first field of file1 and file3
                        for (const auto& row4 : data4) {
                            if (row3[1] == row4[0]) { // Join on second field of file3 and first field of file4
                                // Construct the output row
                                result.push_back({
                                    row4[0], // First field of file4
                                    row1[0], // First field of file1
                                    row1[1], // Second field of file1
                                    row2[1], // Second field of file2
                                    row4[1]  // Second field of file4
                                });
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

// Main program
int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: ./myjoin <file1> <file2> <file3> <file4>\n";
        return 1;
    }

    auto result = multiwayJoin(argv[1], argv[2], argv[3], argv[4]);
    std::cout << "HELLO\n";
    // Output the result
    for (const auto& row : result) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << row[i];
            if (i < row.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "\n";
    }

    
    return 0;
}
