#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

// Helper function to split a string by a delimiter
vector<string> split(const string &line, char delimiter) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char* argv[]) {
    // Input file names
    string file1Path= argv[1];
    string file2Path= argv[2];
    string file3Path= argv[3];
    string file4Path= argv[4];


    unordered_multimap<string, string> file1Data; // key: A, value: B
    unordered_multimap<string, string> file2Data; // key: A, value: C
    unordered_multimap<string, string> file3Data; // key: A, value: D
    unordered_multimap<string, string> file4Data; // key: D, value: E

    // Read file1 and populate file1Data
    ifstream file1(file1Path);
    if (!file1.is_open()) {
        cerr << "Error opening " << file1Path << "\n";
        return 1;
    }
    string line;
    while (getline(file1, line)) {
        vector<string> fields = split(line, ',');
        if (fields.size() < 2) continue;
        file1Data.emplace(fields[0], fields[1]);
    }
    file1.close();

    // Read file2 and populate file2Data
    ifstream file2(file2Path);
    if (!file2.is_open()) {
        cerr << "Error opening " << file2Path << "\n";
        return 1;
    }
    while (getline(file2, line)) {
        vector<string> fields = split(line, ',');
        if (fields.size() < 2) continue;
        file2Data.emplace(fields[0], fields[1]);
    }
    file2.close();

    // Read file3 and populate file3Data
    ifstream file3(file3Path);
    if (!file3.is_open()) {
        cerr << "Error opening " << file3Path << "\n";
        return 1;
    }
    while (getline(file3, line)) {
        vector<string> fields = split(line, ',');
        if (fields.size() < 2) continue;
        file3Data.emplace(fields[0], fields[1]);
    }
    file3.close();

    // Read file4 and populate file4Data
    ifstream file4(file4Path);
    if (!file4.is_open()) {
        cerr << "Error opening " << file4Path << "\n";
        return 1;
    }
    while (getline(file4, line)) {
        vector<string> fields = split(line, ',');
        if (fields.size() < 2) continue;
        file4Data.emplace(fields[0], fields[1]);
    }
    file4.close();

    // Perform the joins and output results
    for (const auto &file1Entry : file1Data) {
        const string &A = file1Entry.first;  // Key from File1
        const string &B = file1Entry.second; // Value from File1

        // Find matches in File2
        auto file2Range = file2Data.equal_range(A);
        for (auto it2 = file2Range.first; it2 != file2Range.second; ++it2) {
            const string &C = it2->second; // Value from File2

            // Find matches in File3
            auto file3Range = file3Data.equal_range(A);
            for (auto it3 = file3Range.first; it3 != file3Range.second; ++it3) {
                const string &D = it3->second; // Value from File3

                // Find matches in File4
                auto file4Range = file4Data.equal_range(D);
                for (auto it4 = file4Range.first; it4 != file4Range.second; ++it4) {
                    const string &E = it4->second; // Value from File4

                    // Output the result in the required format
                    cout << D << "," << A << "," << B << "," << C << "," << E << "\n";
                }
            }
        }
    }

    return 0;
}
