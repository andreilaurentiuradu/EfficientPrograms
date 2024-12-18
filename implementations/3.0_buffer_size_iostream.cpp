#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <string.h>

using namespace std;




int main(int argc, char* argv[]) {
    // Input file names
    string file1Path= argv[1];
    string file2Path= argv[2];
    string file3Path= argv[3];
    string file4Path= argv[4];

    // Add buffer size for iostream
    std::ios::sync_with_stdio(false); // Disable synchronization with C I/O
    std::cin.tie(nullptr);            // Untie cin from cout

    unordered_map<string, vector<string>> file1Data; // Map of key -> {B}
    unordered_map<string, vector<string>> file2Data; // Map of key -> {C}
    unordered_map<string, vector<string>> file3Data; // Map of key -> {D}
    unordered_map<string, vector<string>> file4Data; // Map of D -> {E}

    file1Data.reserve(30000000);
    file2Data.reserve(30000000);
    file3Data.reserve(30000000);
    file4Data.reserve(30000000);

    // Read file1 and populate file1Data
    ifstream file1(file1Path);
    if (!file1.is_open()) {
        cerr << "Error opening " << file1Path << "\n";
        return 1;
    }
    string line;
    while (getline(file1, line)) {
        size_t commaPos = line.find(',');
        auto key = line.substr(0, commaPos);
        auto value = line.substr(commaPos + 1);
        file1Data[std::move(key)].emplace_back(std::move(value));
    }
    file1.close();

    // Read file2 and populate file2Data
    ifstream file2(file2Path);
    if (!file2.is_open()) {
        cerr << "Error opening " << file2Path << "\n";
        return 1;
    }
    while (getline(file2, line)) {
        size_t commaPos = line.find(',');
        auto key = line.substr(0, commaPos);
        auto value = line.substr(commaPos + 1);
        file2Data[std::move(key)].emplace_back(std::move(value));
    }
    file2.close();

    // Read file3 and populate file3Data
    ifstream file3(file3Path);
    if (!file3.is_open()) {
        cerr << "Error opening " << file3Path << "\n";
        return 1;
    }
    while (getline(file3, line)) {
        size_t commaPos = line.find(',');
        auto key = line.substr(0, commaPos);
        auto value = line.substr(commaPos + 1);
        file3Data[std::move(key)].emplace_back(std::move(value));    }
    file3.close();

    // Read file4 and populate file4Data
    ifstream file4(file4Path);
    if (!file4.is_open()) {
        cerr << "Error opening " << file4Path << "\n";
        return 1;
    }
    while (getline(file4, line)) {
        size_t commaPos = line.find(',');
        auto key = line.substr(0, commaPos);
        auto value = line.substr(commaPos + 1);
        file4Data[std::move(key)].emplace_back(std::move(value));    }
    file4.close();

    
    // Perform joins and output results
    for (const auto &file1Entry : file1Data) {
        const string &A = file1Entry.first;      // Key from File1
        const vector<string> &Bs = file1Entry.second; // Values from File1

        if (file2Data.find(A) != file2Data.end()) {
            const vector<string> &Cs = file2Data[A]; // Values from File2

            if (file3Data.find(A) != file3Data.end()) {
                const vector<string> &Ds = file3Data[A]; // Values from File3

                for (const string &D : Ds) {
                    if (file4Data.find(D) != file4Data.end()) {
                        const vector<string> &Es = file4Data[D]; // Values from File4

                        // Produce output
                        for (const string &B : Bs) {
                            for (const string &C : Cs) {
                                for (const string &E : Es) {
                                    cout << D << "," << A << "," << B << "," << C << "," << E << "\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
