#include <iostream>
#include <vector>


struct Item {
    int weight;
    int bonus;
};

int UKP_rec(const std::vector<Item> &items, const int weight) {
    // display call count of the function
    // static int x = 0;
    // x++;
    // std::cout << "UKP_rec " << x << "\n";

    if (weight <= 0)
        return 0;

    int curr_max = 0;
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].weight <= weight) {
            curr_max = std::max(
                curr_max,
                items[i].bonus + UKP_rec(items, weight - items[i].weight)
            );
        }
    }
    return curr_max;
}

int UKP_memoization(const std::vector<Item> &items, const int weight, std::vector<int> &mem) {
    // Display call count of the function
    // static int y = 0;
    // y++;
    // std::cout << "UKP_memoization " << y << "\n";

    if (weight <= 0)
        return 0;

    if (mem[weight])
        return mem[weight];

    int curr_max = 0;
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].weight <= weight) {
            curr_max = std::max(
                curr_max,
                items[i].bonus + UKP_memoization(items, weight - items[i].weight, mem)
            );
        }
    }
    mem[weight] = curr_max;
    return curr_max;
}


int UKP_DP(const std::vector<Item> &items, const int weight) {
    std::vector<int> dp(weight + 1, 0);

    for (size_t curr_weight = 0; curr_weight < dp.size(); curr_weight++) {
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i].weight <= curr_weight) {
                dp[curr_weight] = std::max(
                    dp[curr_weight],
                    dp[curr_weight - items[i].weight] + items[i].bonus
                );
            }
        }
    }
    return dp[weight];
}

int KP_01_rec(const std::vector<Item> &items, const int weight, int n) {
    if (weight <= 0 || n == 0)
        return 0;
    if (items[n-1].weight > weight) {
        return KP_01_rec(items, weight, n-1);
    }
    int res1 = KP_01_rec(items, weight, n-1);
    int res2 = items[n-1].bonus + KP_01_rec(items, weight - items[n-1].weight, n-1);

    return std::max(res1, res2);
}

int KP_01_DP(const std::vector<Item> &items, const int weight) {
    std::vector<std::vector<int>> m(items.size() + 1, std::vector<int>(weight+1, 0));
    for (size_t i = 1; i < m.size(); i++) {
        for (size_t j = 1; j < weight + 1; j++) {
            if (items[i-1].weight <= j) {
                m[i][j] = std::max(m[i-1][j], m[i-1][j - items[i-1].weight] + items[i-1].bonus);
            } else {
                m[i][j] = m[i-1][j];
            }
        }
    }
    return m[m.size()-1][weight];
}

void test_UKP_rec(const std::vector<Item>& items, const int weight) {
    std::cout << UKP_rec(items, weight) << "\n";
}

void test_UKP_memoization(const std::vector<Item>& items, const int weight) {
    std::vector<int> mem(weight + 1, 0);
    std::cout << UKP_memoization(items, weight, mem) << "\n";
    // for (auto m: mem) {
    //     std::cout << m << " ";
    // }
}

void test_UKP_DP(const std::vector<Item>& items, const int weight) {
    std::cout << UKP_DP(items, weight) << "\n";
}

void test_UKP() {
    const std::vector<Item> items = {
        // {1, 10},
        {3, 30},
        {4, 45},
        {5, 70},
    };
    constexpr int weight = 8;
    test_UKP_memoization(items, weight);
    test_UKP_rec(items, weight);
    test_UKP_DP(items, weight);
}

void test_KP_01_rec(const std::vector<Item>& items, const int weight) {
    std::cout << KP_01_rec(items, weight, items.size()) << "\n";
}

void test_KP_01_DP(const std::vector<Item>& items, const int weight) {
    std::cout << KP_01_DP(items, weight) << "\n";
}

void test_KP_01() {
    const std::vector<Item> items = {
        {10, 60},
        {20, 100},
        {30, 120},
    };
    constexpr int weight = 50;
    test_KP_01_rec(items, weight);
    test_KP_01_DP(items, weight);
}

int main() {
    test_UKP();
    test_KP_01();
}
