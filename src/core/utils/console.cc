#include "console.h"

using namespace std;

void Console::Log(const char* str, const size_t& maxWidth) {
    char* x = new char[maxWidth];

    for (size_t i = 0; i < maxWidth; i++) {
        if (*str != '\0')
        {
            x[i] = *str;
            str++;
        } else {
            x[i] = '.';
        }
    }

    x[maxWidth - 1] = '\0';

    cout << x;
    delete[] x;
}