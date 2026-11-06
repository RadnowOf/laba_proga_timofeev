#include "bit_lab.h"
#include <iostream>
#include <cstring>
#include <climits>

void printSizes() {
    std::cout << "Type | Bytes | Description\n";
    std::cout << "bool | " << sizeof(bool) << " | logical value\n";
    std::cout << "char | " << sizeof(char) << " | character / small integer\n";
    std::cout << "short int | " << sizeof(short int) << " | short integer\n";
    std::cout << "int | " << sizeof(int) << " | integer\n";
    std::cout << "long int | " << sizeof(long int) << " | long integer\n";
    std::cout << "float | " << sizeof(float) << " | single precision\n";
    std::cout << "double | " << sizeof(double) << " | double precision\n";
    std::cout << "long double | " << sizeof(long double) << " | extended type\n";
}

void print32(unsigned int bits, int mode) {
    for (int i = 31; i >= 0; i--) {
        std::cout << ((bits >> i) & 1u);
        if (mode == 1 && i == 31) {
            std::cout << " | ";
        }
        if (mode == 2 && (i == 31 || i == 23)) {
            std::cout << " | ";
        }
    }
    std::cout << '\n';
}

void printInt(const int& value) {
    std::cout << "int: " << value << "\nSign | other bits\n";
    unsigned int bits;
    std::memcpy(&bits, &value, sizeof(bits));
    print32(bits, 1);
}

void printUnsigned(const unsigned int& value) {
    std::cout << "unsigned int: " << value << "\nAll bits are value bits\n";
    print32(value, 0);
}

void printFloat(const float& value) {
    std::cout << "float: " << value << "\nSign | exponent (8) | fraction (23)\n";
    unsigned int bits;
    std::memcpy(&bits, &value, sizeof(bits));
    print32(bits, 2);
}

unsigned int changeBit(unsigned int value, int position, int operation) {
    if (position < 0 || position > 31 || operation < 0 || operation > 2) {
        return value;
    }
    unsigned int mask = 1u << position;
    if (operation == 0) {
        value &= ~mask;
    }
    else if (operation == 1) {
        value |= mask;
    }
    else {
        value ^= mask;
    }
    return value;
}

void printMemory(const void* address, int size) {
    const unsigned char* bytes = static_cast<const unsigned char*>(address);
    for (int i = size * 8 - 1; i >= 0; i--) {
        std::cout << ((bytes[i / 8] >> (i % 8)) & 1u);
        if (i % 8 == 0 && i != 0) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
}

bool editNumber(void* address, int size, bool isBool) {
    unsigned char* bytes = static_cast<unsigned char*>(address);
    printMemory(address, size);
    int position;
    int operation;
    std::cout << "Bit position (0.." << size * 8 - 1 << "): ";
    if (!(std::cin >> position)) {
        return false;
    }
    std::cout << "Operation (0: clear, 1: set, 2: toggle): ";
    if (!(std::cin >> operation)) {
        return false;
    }
    if (position < 0 || position >= size * 8 || operation < 0 || operation > 2) {
        std::cout << "Invalid position or operation\n";
        return false;
    }
    int byte = position / 8;
    unsigned int result = changeBit(bytes[byte], position % 8, operation);
    if (isBool && result > 1) {
        std::cout << "Invalid bool representation; change cancelled\n";
        return false;
    }
    bytes[byte] = static_cast<unsigned char>(result);
    printMemory(address, size);
    return true;
}

int roundDownToEven(int value) {
    return value & ~1;
}

bool individualTask() {
    std::cout << "\nIndividual task: round down to an even integer\n";
    int examples[] = {7, 8, -7, -8, 0, INT_MIN, INT_MAX};

    for (int i = 0; i < 7; i++) {
        std::cout << examples[i] << " -> "
            << roundDownToEven(examples[i]) << '\n';
    }

    int value;
    std::cout << "Enter an integer: ";
    if (!(std::cin >> value)) {
        return false;
    }

    printInt(value);
    value = roundDownToEven(value);
    std::cout << "Even number: " << value << '\n';
    printInt(value);
    return true;
}
