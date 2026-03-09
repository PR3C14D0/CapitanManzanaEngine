#pragma once
#include <iostream>

#define LOG_INFO(x)  std::cout << "[INFO] " << x << std::endl
#define LOG_WARN(x)  std::cout << "\033[33m[WARN] " << x << "\033[0m (" << __FILE__ << ":" << __LINE__ << ")" << std::endl
#define LOG_ERROR(x) std::cerr << "\033[31m[ERROR] " << x << "\033[0m (" << __FILE__ << ":" << __LINE__ << ")" << std::endl