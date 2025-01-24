#include <iostream>
#include <unordered_map>
#include <vector>

unsigned fib1(unsigned N) {
    if (N <= 1) {
        return N;
    }
    return fib1(N-1) + fib1(N-2);
}


std::unordered_map<unsigned, unsigned> m;
unsigned fib2(unsigned N) {
    if (N <= 1) {
        return 1;
    }
    if (N == 2) return 2;
    if (N == 3) return 3;
    if (N == 4) return 5;

    if (m.contains(N)) {
        return m[N];
    }
    if (N % 2 == 0) {
        unsigned res1 = fib2(N/2 - 1);
        m[N/2 - 1] = res1;
        unsigned res2 = fib2(N/2);
        m[N/2] = res2;
        return res1*res1 + res2*res2;
    } else {
        unsigned res1 = fib2(N/2 - 1);
        m[N/2 - 1] = res1;
        unsigned res2 = fib2(N/2);
        m[N/2] = res2;
        unsigned res3 = fib2(N/2 + 1);
        m[N/2 + 1] = res3;
        return res2*(res1 + res3);
    }

}

void testFib() {
    std::cout << fib2(0) << "\n";
    std::cout << fib2(1) << "\n";
    std::cout << fib2(2) << "\n";
    std::cout << fib2(3) << "\n";
    std::cout << fib2(4) << "\n";
    std::cout << fib2(5) << "\n";
    std::cout << fib2(6) << "\n";
}


unsigned getAllPathsCount(const std::vector<std::vector<int>>& m) {
    int rows = m.size();
    int cols = m[0].size();
    std::vector<std::vector<int>> pathsCount(rows, std::vector<int>(cols, 0));
    for (int i = rows - 1; i >= 0; i--) {
        if (m[i][cols-1] == 0) {
            break;
        }
        pathsCount[i][cols-1] = 1;
    }

    for (int j = cols - 1; j >= 0; j--) {
        if (m[rows - 1][j] == 0) {
            break;
        }
        pathsCount[rows - 1][j] = 1;
    }

    for (int i = rows - 2; i >= 0; i--) {
        for (int j = cols - 2; j >= 0; j--) {
            if (m[i][j] == 0) {
                continue;
            }
            pathsCount[i][j] = pathsCount[i][j+1] + pathsCount[i+1][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << pathsCount[i][j] << " ";
        }
        std::cout << "\n";
    }
    return pathsCount[0][0];
}

void testAllPathsCount() {
    std::vector<std::vector<int>> m1 = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        };
    std::cout << getAllPathsCount(m1) << "\n";

    std::vector<std::vector<int>> m2 = {
        {1, 1, 0, 1, 1},
        {1, 1, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1},
        };
    std::cout << getAllPathsCount(m2) << "\n";
}

int main() {
    testAllPathsCount();
    return 0;
}