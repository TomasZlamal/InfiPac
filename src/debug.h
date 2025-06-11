#pragma once
#ifdef DEBUG_MODE_ON
#include <iostream>
#endif

#ifdef DEBUG_MODE_ON
#define DEBUG_PRINT(x) std::cout << x << std::endl;
#else
#define DEBUG_PRINT(x)
#endif
