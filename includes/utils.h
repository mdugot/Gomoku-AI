#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <iterator>
#include <cmath>


#include "colors.h"
#define NPOS std::string::npos
#define PRINT_ERROR true
#define ERROR if (PRINT_ERROR) std::cerr
#define PRINT_DEBUG true
#define DEBUG if (PRINT_DEBUG) std::cerr
#define PRINT_OUT true
#define OUT if (PRINT_OUT) std::cout
#define ABS(x) (x) < 0 ? -(x) : (x)
#define MIN_INT -10000000
#define MAX_INT 10000000
#define MIN_LONG (long long)0x8000000000000000 
#define MAX_LONG (long long)0x7FFFFFFFFFFFFFFF

void success(std::string message);
void failure(std::string message);

#endif

