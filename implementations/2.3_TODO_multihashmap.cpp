#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Helper function to split a string by a delimiter
pair<string, string> split(const string &line, char delimiter) {
    size_t commaPos = line.find(delimiter);
    if (commaPos == string::npos) return {};
    return {line.substr(0, commaPos), line.substr(commaPos + 1)};
}

int main(int argc, char* argv[]) {
    // Input file names
    string file1Path = argv[1];
    string file2Path = argv[2];
    string file3Path = argv[3];
    string file4Path = argv[4];

    unordered_multimap<string, string> file1Data; // Map of key -> value B
    unordered_multimap<string, string> file2Data; // Map of key -> value C
    unordered_multimap<string, string> file3Data; // Map of key -> value D
    unordered_multimap<string, string> file4Data; // Map of D -> value E

    string line;

    // Read file1 and populate file1Data
    ifstream file1(file1Path);
    while (getline(file1, line)) {
        auto [key, value] = split(line, ',');
        if (!key.empty() && !value.empty()) file1Data.emplace(key, value);
    }
    file1.close();

    // Read file2 and populate file2Data
    ifstream file2(file2Path);
    while (getline(file2, line)) {
        auto [key, value] = split(line, ',');
        if (!key.empty() && !value.empty()) file2Data.emplace(key, value);
    }
    file2.close();

    // Read file3 and populate file3Data
    ifstream file3(file3Path);
    while (getline(file3, line)) {
        auto [key, value] = split(line, ',');
        if (!key.empty() && !value.empty()) file3Data.emplace(key, value);
    }
    file3.close();

    // Read file4 and populate file4Data
    ifstream file4(file4Path);
    while (getline(file4, line)) {
        auto [key, value] = split(line, ',');
        if (!key.empty() && !value.empty()) file4Data.emplace(key, value);
    }
    file4.close();

    // Perform joins and output results
    for (const auto &file1Entry : file1Data) {
        const string &A = file1Entry.first;  // Key from File1
        const string &B = file1Entry.second; // Value B from File1

        auto file2Range = file2Data.equal_range(A);
        auto file3Range = file3Data.equal_range(A);

        for (auto it2 = file2Range.first; it2 != file2Range.second; ++it2) {
            const string &C = it2->second; // Value C from File2

            for (auto it3 = file3Range.first; it3 != file3Range.second; ++it3) {
                const string &D = it3->second; // Value D from File3

                auto file4Range = file4Data.equal_range(D);
                for (auto it4 = file4Range.first; it4 != file4Range.second; ++it4) {
                    const string &E = it4->second; // Value E from File4

                    // Output the results
                    cout << D << "," << A << "," << B << "," << C << "," << E << "\n";
                }
            }
        }
    }

    return 0;
}
