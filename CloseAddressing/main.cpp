#include <iostream>
#include <vector>
#include <forward_list>

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
    static constexpr size_t tableSize = 20;
private:
    std::vector<std::forward_list<std::string>> table;
    Hash hash;
public:
    HashTable() : table(tableSize) {}
    void insert(const std::string& str) {
        auto h = hash(str, table.size());
        if (std::find(table[h].begin(), table[h].end(), str) == table[h].end()) {
            table[h].push_front(str);
        }
    }

    [[nodiscard]] bool find(const std::string& str) const {
        auto h = hash(str, table.size());
        if (!table[h].empty()) {
            for (const auto& s : table[h]) {
                if (str == s) {
                    return true;
                }
            }
        }
        return false;
    }
    void remove(const std::string& str) {
        auto h = hash(str, table.size());
        if (!table[h].empty()) {
            table[h].remove(str);
        }
    }

    void print() const {
        for (const auto& l : table) {
            if (!l.empty()) {
                for (const auto& v : l) {
                    std::cout << v << ", ";
                }
                std::cout << std::endl;
            }
        }
    }
};


int main() {
    HashTable t;
    t.insert("abc");
    t.insert("acb");
    t.insert("cba");
    t.insert("cba");

    std::cout << t.find("abc") << std::endl;
    t.remove("cba");
    t.print();
    return 0;
}
