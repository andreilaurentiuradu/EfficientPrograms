#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cerrno> // For errno
#include <cstring> // For strerror
#include <algorithm>

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


void sortCollumn(
    std::vector<std::vector<std::string>>& vec,
    const int colId
) {
    std::sort(vec.begin(), vec.end(), [colId](const std::vector<std::string>& a, const std::vector<std::string>& b) {
        if (a.empty() || b.empty()) {
            std::cout << "empty";
            return false;
        }
        return a[colId] < b[colId];  
    }); 
}

std::vector<std::vector<std::string>> multiwayJoin(
    const std::string& file1, const std::string& file2, 
    const std::string& file3, const std::string& file4
) {
    auto A = readCSV(file1);
    auto B = readCSV(file2);
    auto C = readCSV(file3);
    auto D = readCSV(file3);
    auto E = readCSV(file4);

    sortCollumn(A, 0);
    sortCollumn(B, 0);
    sortCollumn(C, 0);
    sortCollumn(D, 1);
    sortCollumn(E, 0);

    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;

    std::vector<std::vector<std::string>> result;

    while (p4 < D.size()) {
        p1 = 0;
        while (p1 < A.size()) {
            p2 = 0;
            while (p2 < B.size() && A[p1][0] > B[p2][0]) {
                p2++;
            }
            while (p2 < B.size() && A[p1][0] == B[p2][0]) {
                p3 = 0;
                while (p3 < C.size() && A[p1][0] > C[p3][0]) {
                    p3++;
                }
                while (p3 < C.size() && A[p1][0] == C[p3][0]) {
                    p5 = 0;
                    while (p5 < E.size() && D[p4][1] > E[p5][0]) {
                        p5++;
                    }
                    while (p5 < E.size() && D[p4][1] == E[p5][0]) {
                        result.push_back({
                            D[p4][1],
                            A[p1][0],
                            A[p2][1],
                            B[p3][1],
                            E[p5][1]
                        });
                        p5++;
                    }
                    p3++;
                }
                p2++;
            }
            std::string last = A[p1][0];
            p1++;
            while (p1 < A.size() && A[p1][0] == last) {
                p1++;
            }
        }
        // Find next unique index
        std::string last = D[p4][1];
        p4++;
        while (p4 < D.size() && D[p4][1] == last) {
            p4++;
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
    std::cout << "Terminated!\n";
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
