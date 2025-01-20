#include <iostream>
#include <vector>
#include <string>
// #include <stdlib.h>
#include <ctime>

std::string generateRandomString() {
    std::string randomString;
    for (int i = 0; i < 2; ++i) {
        // Generate a random character (a-z, A-Z, 0-9)
        char randomChar = 'A' + std::rand() % 62; // Start with 'A'
        if (randomChar > 'Z' && randomChar < 'a') randomChar += 6; // Adjust to skip non-alphabet characters
        if (randomChar > 'z') randomChar -= 75; // Adjust for digits 0-9
        randomString += randomChar;
    }
    return randomString;
}

struct Hash
{
    size_t operator()(const std::string& str, size_t size) const {
        unsigned h = 0;
        for (size_t i = 0; i < str.size(); i++) {
            h = h + str[i] * (i + 1) * (i + 1);
        }
        return h % size;
    }
};

class HashTable {
    static constexpr size_t tableSize = 500;
    static constexpr double loadFactor = 0.5;

private:
    std::vector<std::string> table;
    size_t size;
    Hash hash;

public:
    HashTable() : table(tableSize, ""), size(0) {}
    void printTable() const {
        for (const auto& e : table) {
            if (!e.empty()) {
                std::cout << e << "\n";
            } else {
                std::cout << "***Empty entry***\n";
            }
        }
    }

    void printClusters() const {
        for (const auto& e : table) {
            if (!e.empty()) {
                std::cout << "* ";
            } else {
                std::cout << " ";
            }
        }
    }
    void insert(const std::string& str) {
        auto h = hash(str, table.size());
        auto attemptsCount = table.size();
        while (!table[h].empty() && attemptsCount) {
            attemptsCount--;
            h++;
            if (h == table.size()) {
                h = 0;
            }
        }
        if (table[h].empty()) {
            table[h] = str;
            size++;
        } else {
            std::cout << "The table is full\n";
        }
    }
};


void testInsert() {
    HashTable h;
    for (int i = 0; i < 400; i++) {
        auto s = generateRandomString();
        h.insert(s);
    }
    h.printClusters();
}

int main() {
    std::srand(std::time(nullptr));
    testInsert();
    return 0;
}
