#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string.h>

std::string generateRandomString() {
    std::string randomString;
    for (int i = 0; i < 2; ++i) {
        char randomChar = 'A' + std::rand() % 62;
        if (randomChar > 'Z' && randomChar < 'a') randomChar += 6;
        if (randomChar > 'z') randomChar -= 75;
        randomString += randomChar;
    }
    return randomString;
}

#endif //UTILS_H
