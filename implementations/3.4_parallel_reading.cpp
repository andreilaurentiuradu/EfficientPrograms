#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>

using namespace std;

void readFileIntoMap(const string& filePath, unordered_map<string, vector<string>>& data) {
    ifstream file(filePath, ios::in | ios::binary); // Binary mode for better performance
    if (!file.is_open()) {
        throw runtime_error("Error opening " + filePath);
    }

    constexpr size_t BUFFER_SIZE = 1 << 16;  // 64KB buffer
    char buffer[BUFFER_SIZE];
    file.rdbuf()->pubsetbuf(buffer, BUFFER_SIZE);

    string line, key, value;
    line.reserve(1024);  // Preallocate string space

    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        key = line.substr(0, commaPos);
        value = line.substr(commaPos + 1);
        data[std::move(key)].emplace_back(std::move(value));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " file1 file2 file3 file4\n";
        return 1;
    }

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    try {
        unordered_map<string, vector<string>> file1Data, file2Data, file3Data, file4Data;

        // Reserve space for each file map
        file1Data.reserve(30000000);
        file2Data.reserve(30000000);
        file3Data.reserve(30000000);
        file4Data.reserve(30000000);

        // Read files in parallel
        thread t1([&]() { readFileIntoMap(argv[1], file1Data); });
        thread t2([&]() { readFileIntoMap(argv[2], file2Data); });
        thread t3([&]() { readFileIntoMap(argv[3], file3Data); });
        thread t4([&]() { readFileIntoMap(argv[4], file4Data); });

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        string outputBuffer;
        outputBuffer.reserve(1 << 25); // Reserve 32MB for the output buffer

        // Process data with optimized loops
        for (const auto& [A, Bs] : file1Data) {
            if (auto it2 = file2Data.find(A); it2 != file2Data.end()) {
                const auto& Cs = it2->second;
                if (auto it3 = file3Data.find(A); it3 != file3Data.end()) {
                    const auto& Ds = it3->second;
                    
                    for (const auto& D : Ds) {
                        if (auto it4 = file4Data.find(D); it4 != file4Data.end()) {
                            const auto& Es = it4->second;
                            
                            // Precompute repetitive parts of the output (CSE)
                            string precomputedPrefix = D + "," + A + ",";

                            // Loop unrolling for better performance
                            size_t i = 0;
                            for (; i + 1 < Bs.size(); i += 2) {
                                const auto& B = Bs[i];
                                const auto& B2 = Bs[i + 1];

                                string precomputedB = precomputedPrefix + B + ",";
                                string precomputedB2 = precomputedPrefix + B2 + ",";

                                for (const auto& C : Cs) {
                                    string precomputedBC = precomputedB + C + ",";
                                    string precomputedB2C = precomputedB2 + C + ",";

                                    for (const auto& E : Es) {
                                        outputBuffer.append(precomputedBC).append(E).append("\n");
                                        outputBuffer.append(precomputedB2C).append(E).append("\n");
                                    }
                                }
                            }

                            // odd number of elements
                            if (i < Bs.size()) {
                                const auto& B = Bs[i];
                                string precomputedB = precomputedPrefix + B + ",";
                                for (const auto& C : Cs) {
                                    string precomputedBC = precomputedB + C + ",";
                                    for (const auto& E : Es) {
                                        outputBuffer.append(precomputedBC).append(E).append("\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // Write output in one operation
        cout << outputBuffer;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
