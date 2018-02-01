#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "colors.h"
#define NPOS std::string::npos
#define PRINT_ERROR true
#define ERROR if (PRINT_ERROR) std::cerr
#define PRINT_DEBUG true
#define DEBUG if (PRINT_DEBUG) std::cerr
#define PRINT_OUT true
#define OUT if (PRINT_OUT) std::cout
#define ABS(x) (x) < 0 ? -(x) : (x)

void success(std::string message);
void failure(std::string message);

#endif

