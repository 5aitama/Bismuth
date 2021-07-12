#pragma once

#include <iostream>
#include <string>

#ifndef OK_MSG
#define OK_MSG std::cout << " \033[1;32mOk!\033[0m" << std::endl;
#endif

#ifndef FAIL_MSG
#define FAIL_MSG cout << " \033[1;31mFail!\033[0m" << endl;
#endif

struct Console {
public:
    static void Log(const char* str, const size_t& maxWidth = 64);
};