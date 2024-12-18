#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Add a function to reduce code duplication and improve maintainability
void readFileIntoMap(const string& filePath, unordered_map<string, vector<string>>& data) {
    ifstream file(filePath, ios::in | ios::binary); // Binary mode for better performance
    if (!file.is_open()) {
        throw runtime_error("Error opening " + filePath);
    }
    
    // Use larger buffer for better I/O performance
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
    // Verify arguments
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " file1 file2 file3 file4\n";
        return 1;
    }

    // Optimize I/O operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Pre-allocate output buffer
    string outputBuffer;
    outputBuffer.reserve(1 << 24);  // Reserve 16MB initially
    
    try {
        // Data containers with pre-allocated space
        unordered_map<string, vector<string>> file1Data, file2Data, file3Data, file4Data;
        for (auto& map : {&file1Data, &file2Data, &file3Data, &file4Data}) {
            map->reserve(30000000);
        }

        // Read files
        readFileIntoMap(argv[1], file1Data);
        readFileIntoMap(argv[2], file2Data);
        readFileIntoMap(argv[3], file3Data);
        readFileIntoMap(argv[4], file4Data);

        // Process data with optimized loops
        for (const auto& [A, Bs] : file1Data) {
            if (auto it2 = file2Data.find(A); it2 != file2Data.end()) {
                const auto& Cs = it2->second;
                if (auto it3 = file3Data.find(A); it3 != file3Data.end()) {
                    const auto& Ds = it3->second;
                    
                    for (const auto& D : Ds) {
                        if (auto it4 = file4Data.find(D); it4 != file4Data.end()) {
                            const auto& Es = it4->second;
                            
                            // Loop unrolling for better performance
                            size_t i = 0;
                            for (; i + 1< Bs.size(); i += 2) {
                                const auto& B = Bs[i];
                                for (const auto& C : Cs) {
                                    for (const auto& E : Es) {
                                        outputBuffer.append(D).append(",")
                                                  .append(A).append(",")
                                                  .append(B).append(",")
                                                  .append(C).append(",")
                                                  .append(E).append("\n");
                                    }
                                }
                                // Handle odd number of elements
                                const auto& B2 = Bs[i + 1];
                                for (const auto& C : Cs) {
                                    for (const auto& E : Es) {
                                        outputBuffer.append(D).append(",")
                                                      .append(A).append(",")
                                                      .append(B2).append(",")
                                                      .append(C).append(",")
                                                      .append(E).append("\n");
                                    }
                                }
                            }
                            if (i < Bs.size()) {
                                const auto& B = Bs[i];
                                for (const auto& C : Cs) {
                                    for (const auto& E : Es) {
                                        outputBuffer.append(D).append(",")
                                                  .append(A).append(",")
                                                  .append(B).append(",")
                                                  .append(C).append(",")
                                                  .append(E).append("\n");
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