#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "utils.h"

struct Hash
{
    size_t operator()(const std::string& str, size_t size) const {
        unsigned h = 0;
        for (size_t i = 0; i < str.size(); i++) {
            h = h + str[i] * (31 << i);
        }
        return h % size;
    }
};

class HashTable {
    static constexpr double loadFactor = 0.5;

private:
    std::vector<std::string> table;
    size_t size;
    Hash hash;

public:
    explicit HashTable(const size_t size) : table(size, ""), size(0) {}
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
        std::cout << "\n";
    }
    void printRunsLens() {
        for (size_t i = 0; i < table.size(); i++) {
            size_t currRunLen = 0;
            while (i < table.size() && !table[i].empty()) {
                currRunLen++;
                i++;
            }
            if (currRunLen) {
                std::cout << currRunLen << " ";
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


void showClusters() {
    HashTable h(1000);
    for (int i = 0; i < 250; i++) {
        auto s = generateRandomString();
        h.insert(s);
    }
    h.printClusters();
    h.printRunsLens();

    for (int i = 0; i < 250; i++) {
        auto s = generateRandomString();
        h.insert(s);
    }
    h.printClusters();
    h.printRunsLens();

    for (int i = 0; i < 250; i++) {
        auto s = generateRandomString();
        h.insert(s);
    }
    h.printClusters();
    h.printRunsLens();
}

int main() {
    std::srand(std::time(nullptr));
    showClusters();
    return 0;
}
