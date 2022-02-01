/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2020
 *
 * @file    Main.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Entry point of Homework03 target.
 */

#include "magic_square.h"

int main()
{
    cout << "Hello, Main!" << endl;
    int order{ 13 };
    csc232::TwoDimArray twoDimArray;
    csc232::CreateMagicSquare( twoDimArray, order );
    csc232::PrintTable( order, order, twoDimArray );
    return EXIT_SUCCESS;
}