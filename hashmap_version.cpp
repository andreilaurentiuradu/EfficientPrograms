#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

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

    unordered_map<string, vector<string>> file1Data; // Map of key -> {B}
    unordered_map<string, vector<string>> file2Data; // Map of key -> {C}
    unordered_map<string, vector<string>> file3Data; // Map of key -> {D}
    unordered_map<string, vector<string>> file4Data; // Map of D -> {E}

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
        file1Data[fields[0]].push_back(fields[1]);
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
        file2Data[fields[0]].push_back(fields[1]);
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
        file3Data[fields[0]].push_back(fields[1]);
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
        file4Data[fields[0]].push_back(fields[1]);
    }
    file4.close();

    // Perform the joins and output results
    for (const auto &file1Entry : file1Data) {
        const string &A = file1Entry.first; // First field of File1
        const vector<string> &Bs = file1Entry.second; // Second fields of File1

        if (file2Data.find(A) != file2Data.end()) {
            const vector<string> &Cs = file2Data[A]; // Second fields of File2

            if (file3Data.find(A) != file3Data.end()) {
                const vector<string> &Ds = file3Data[A]; // Second fields of File3

                for (const string &D : Ds) {
                    if (file4Data.find(D) != file4Data.end()) {
                        const vector<string> &Es = file4Data[D]; // Second fields of File4

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
