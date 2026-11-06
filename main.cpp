#include <iostream>
#include <cstring>
#include <limits>
#include <climits>
#include "bit_lab.h"

int main() {
    printSizes();

    printInt(12);
    printInt(-12);
    printInt(0);
    printUnsigned(12u);
    printUnsigned(0u);
    printUnsigned(UINT_MAX);

    printFloat(3.14f);
    printFloat(-2.5f);
    printFloat(0.0f);
    printFloat(std::numeric_limits<float>::denorm_min());
    printFloat(std::numeric_limits<float>::infinity());

    unsigned int original = 12u;
    std::cout << "Set bit 0: " << changeBit(original, 0, 1) << '\n';
    std::cout << "Clear bit 2: " << changeBit(original, 2, 0) << '\n';
    std::cout << "Toggle bit 3: " << changeBit(original, 3, 2) << '\n';

    float example = 1.5f;
    unsigned int bits;
    std::memcpy(&bits, &example, sizeof(bits));
    bits = changeBit(bits, 31, 2);
    std::memcpy(&example, &bits, sizeof(example));
    printFloat(example);

    int number;
    std::cout << "\nbool (0 or 1): ";
    if (!(std::cin >> number) || (number != 0 && number != 1)) {
        return 1;
    }
    bool b = number;
    if (!editNumber(&b, sizeof(b), true)) {
        return 1;
    }
    std::cout << "Result: " << b << '\n';

    std::cout << "\nchar (" << CHAR_MIN << ".." << CHAR_MAX << "): ";
    if (!(std::cin >> number) || number < CHAR_MIN || number > CHAR_MAX) {
        return 1;
    }
    char c = static_cast<char>(number);
    if (!editNumber(&c, sizeof(c), false)) {
        return 1;
    }
    std::cout << "Result: " << static_cast<int>(c) << '\n';

    short int s;
    std::cout << "\nshort int: ";
    if (!(std::cin >> s) || !editNumber(&s, sizeof(s), false)) {
        return 1;
    }
    std::cout << "Result: " << s << '\n';

    int i;
    std::cout << "\nint: ";
    if (!(std::cin >> i) || !editNumber(&i, sizeof(i), false)) {
        return 1;
    }
    std::cout << "Result: " << i << '\n';
    printInt(i);

    long int l;
    std::cout << "\nlong int: ";
    if (!(std::cin >> l) || !editNumber(&l, sizeof(l), false)) {
        return 1;
    }
    std::cout << "Result: " << l << '\n';

    float f;
    std::cout << "\nfloat: ";
    if (!(std::cin >> f) || !editNumber(&f, sizeof(f), false)) {
        return 1;
    }
    std::cout << "Result: " << f << '\n';
    printFloat(f);

    double d;
    std::cout << "\ndouble: ";
    if (!(std::cin >> d) || !editNumber(&d, sizeof(d), false)) {
        return 1;
    }
    std::cout << "Result: " << d << '\n';

    long double ld;
    std::cout << "\nlong double: ";
    if (!(std::cin >> ld) || !editNumber(&ld, sizeof(ld), false)) {
        return 1;
    }
    std::cout << "Result: " << ld << '\n';
    if (!individualTask()) {
        return 1;
    }
    return 0;
}
