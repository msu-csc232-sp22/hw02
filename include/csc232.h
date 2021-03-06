/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2022
 *
 * @file    csc232.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Macros, libraries and definitions for use in csc232 assignments.
 * @version 0.2022.02.12
 * @date    02/12/2022
 *
 * @copyright Copyright (c) 2021 James R. Daehn
 */

#ifndef CSC232_COMMON_H__
#define CSC232_COMMON_H__

#define FALSE 0
#define TRUE 1

#define WORKING_ON_TASK1 FALSE
#define WORKING_ON_TASK2 FALSE
#define WORKING_ON_TASK3 FALSE
#define WORKING_ON_TASK4 FALSE
#define WORKING_ON_TASK5 FALSE

#define TASK1_COMPLETED FALSE
#define TASK2_COMPLETED FALSE
#define TASK3_COMPLETED FALSE
#define TASK4_COMPLETED FALSE
#define TASK5_COMPLETED FALSE

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <memory>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <stdexcept>
#include <utility>
#include <vector>

#include "expanded_templates.h"

#if TASK1_COMPLETED

#include "point.h"

#endif

 /** Common iostream objects */
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/** Common iomanip objects */
using std::left;
using std::right;
using std::setprecision;
using std::setw;
using std::setfill;

/**
 * @brief Common namespace for CSC232 identifiers.
 */
namespace csc232
{
    // Add any user-defined functions prescribed in your assignment below

#if WORKING_ON_TASK1

    // There is no work to do in this file for TASK1 ... 
    // You should be working in/on new files: /include/point.h and /src/point.cpp
    // Please note: The GitHub actions treat these file names in a case-sensitive manner.

#endif // WORKING_ON_TASK1

#if WORKING_ON_TASK2

    // TODO: Define int rotations_needed(Point p) below

#endif // WORKING_ON_TASK2

#if WORKING_ON_TASK3

    // TODO: Define void rotate_to_upper_right(Point& p) below

#endif // WORKING_ON_TASK3

#if WORKING_ON_TASK4

    // TODO: Define double distance(const Point& p1, const Point& p2) below

#endif // WORKING_ON_TASK4

#if WORKING_ON_TASK5

    // TODO: Define Point middle(const Point& p1, const Point& p2) below
    
#endif // WORKING_ON_TASK5

    // DO NOT Modify anything below this line

    /**
     * @brief Generate a quasi-random UUID.
     * @return A string representation of a quasi-random UUID.
     */
    std::string GenerateUuid()
    {
        static std::random_device random_device;
        static std::mt19937 random_number_generator(random_device());

        std::uniform_int_distribution<int> dist(0, 15);

        const char* uuid_alphabet = "0123456789abcdef";
        const bool dash[] = { false, false, false, false, true, false, true, false,
                             true, false, true, false, false, false, false, false };

        std::string uuid;
        for (bool dash_location : dash)
        {
            if (dash_location)
                uuid += "-";
            uuid += uuid_alphabet[dist(random_number_generator)];
            uuid += uuid_alphabet[dist(random_number_generator)];
        }
        return uuid;
    }
} // namespace csc232

#endif // CSC232_COMMON_H__
