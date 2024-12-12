#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cerrno>
#include <cstring>

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

vector<vector<string>> hashMerge(
    vector<vector<string>> &a, 
    vector<vector<string>> &b,
    int f_ind_1,
    int f_ind_2
) {
    unordered_map<string, vector<vector<string>>> join_map;
    
    // swap a and b if b is larger
    if (a.size() < b.size()) {
        swap(a,b);
        swap(f_ind_1, f_ind_2);
    }

    // loop over all rows in the smaller table
    for (const auto &row : a) {
        // Populate the hashmap
        join_map[row[f_ind_1]].emplace_back(row);
    }

    // now we have the hashmap
    // create intermediate result storage
    vector<vector<string>> result;

    // loop over all rows in b
    for (const auto &b_row: b) {
        // if this row contains the join key
        if (join_map.find(b_row[f_ind_2]) != join_map.end()) {
            // then join these 
            for (const auto a_row: join_map[b_row[f_ind_2]]) {
                // for each matching tuple in a
                vector<string> buf = a_row;
                // add all fields from b
                for (const auto st: b_row) {
                    buf.push_back(st);
                }
                // add this to the result
                result.push_back(move(buf));
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {

    auto f1 = readCSV(argv[1]);
    auto f2 = readCSV(argv[2]);
    auto f3 = readCSV(argv[3]);
    auto f4 = readCSV(argv[4]);

    auto ab = hashMerge(f1,f2, 0, 0);
    auto abc = hashMerge(ab, f3, 0, 0);
    auto abcd = hashMerge(abc, f4, 5, 0);

    for (const auto &row : abcd) {
        cout << row[6] << ','; // d
        cout << row[0] << ','; // a
        cout << row[1] << ','; // b
        cout << row[3] << ','; // d
        cout << row[7] << '\n'; // e
    }
}
