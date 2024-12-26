#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "robin_hood.h"

using namespace std;

// Add a function to reduce code duplication and improve maintainability
void readFileIntoMap(const string& filePath, robin_hood::unordered_map<size_t,vector<pair<string, string>>>& data) {
    ifstream file(filePath, ios::in | ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Error opening " + filePath);
    }

    constexpr size_t BUFFER_SIZE = 1 << 16;  // 64KB buffer
    char buffer[BUFFER_SIZE];
    file.rdbuf()->pubsetbuf(buffer, BUFFER_SIZE);

    string line;
    line.reserve(1024);
    std::hash<std::string> hasher;

    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        string key(line.begin(), line.begin() + commaPos);
        string value(line.begin() + commaPos + 1, line.end());

        size_t hashedKey = hasher(key);
        // printf("%s\n", "hashing output");
        // printf("%s\n",to_string(hasher("54ZQNV419SLRN5645U")));
        // printf("%s\n",to_string(hasher("54ZQNV419SLRN5645U")));
        data[hashedKey].emplace_back(std::move(key), std::move(value));
    }
}


int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " file1 file2 file3 file4\n";
        return 1;
    }

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string outputBuffer;
    outputBuffer.reserve(1 << 24);  // Reserve 16MB initially

    try {
        robin_hood::unordered_map<size_t, vector<pair<string, string>>> file1Data, file2Data, file3Data, file4Data;
        file1Data.reserve(30000000);
        file2Data.reserve(30000000);
        file3Data.reserve(30000000);
        file4Data.reserve(30000000);

        readFileIntoMap(argv[1], file1Data);
        readFileIntoMap(argv[2], file2Data);
        readFileIntoMap(argv[3], file3Data);
        readFileIntoMap(argv[4], file4Data);

        std::hash<std::string> hasher;

        for (const auto& [A_hashed, Bs] : file1Data) {
            // Retrieve the original string from the hash map
            const string& A = Bs[0].first; // The first element's key is the original string A

            if (auto it2 = file2Data.find(A_hashed); it2 != file2Data.end()) {
                const auto& Cs = it2->second;
                if (auto it3 = file3Data.find(A_hashed); it3 != file3Data.end()) {
                    const auto& Ds = it3->second;

                    for (const auto& D_pair : Ds) {
                        const string& D = D_pair.first; // The first element's key is the original string D
                        size_t D_hashed = hasher(D);
                        if (auto it4 = file4Data.find(D_hashed); it4 != file4Data.end()) {
                            const auto& Es = it4->second;
                            string precomputedPrefix = D + "," + A + ",";

                            size_t i = 0;
                            for (; i + 1 < Bs.size(); i += 2) {
                                const auto& B = Bs[i];
                                const auto& B2 = Bs[i + 1];

                                string precomputedB = precomputedPrefix + B.first + ",";
                                string precomputedB2 = precomputedPrefix + B2.first + ",";

                                for (const auto& C_pair : Cs) {
                                    const string& C = C_pair.first; // C's original key
                                    string precomputedBC = precomputedB + C + ",";
                                    string precomputedB2C = precomputedB2 + C + ",";

                                    for (const auto& E_pair : Es) {
                                        const string& E = E_pair.first; // E's original key
                                        outputBuffer.append(precomputedBC + E + "\n");
                                        outputBuffer.append(precomputedB2C + E + "\n");
                                    }
                                }
                            }

                            // Handle odd number of Bs
                            if (i < Bs.size()) {
                                const auto& B = Bs[i];
                                string precomputedB = precomputedPrefix + B.first + ",";
                                for (const auto& C_pair : Cs) {
                                    const string& C = C_pair.first; // C's original key
                                    string precomputedBC = precomputedB + C + ",";
                                    for (const auto& E_pair : Es) {
                                        const string& E = E_pair.first; // E's original key
                                        outputBuffer.append(precomputedBC + E + "\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        cout << outputBuffer;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

