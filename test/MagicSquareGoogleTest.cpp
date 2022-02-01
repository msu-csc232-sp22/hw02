/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2020
 *
 * @file      MagicSquareGoogleTest.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation template.
 */

#include <iomanip>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "magic_square.h"

static int possiblePoints{ 0 };
static int earnedPoints{ 0 };
static const int MAX_CORRECTNESS_PTS{ 3 };

namespace csc232
{

    class CSC232BaseTestFixture : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            ::testing::FLAGS_gtest_death_test_style = "threadsafe";
            possiblePoints += 1;
        }

        void TearDown() override
        {
            if (!HasFailure())
            {
                earnedPoints += 1;
            }
        }

        // Reusable objects for each unit test in this test fixture
        csc232::TwoDimArray order1Table{{ 1 }};
        csc232::TwoDimArray initializedOrder3Table{{ 0, 0, 0 },
                                                   { 0, 0, 0 },
                                                   { 0, 0, 0 }};
        csc232::TwoDimArray magicOrder3Table{{ 2, 9, 4 },
                                             { 7, 5, 3 },
                                             { 6, 1, 8 }};
        csc232::TwoDimArray nonMagicOrder3Table{{ 1,  2,  3 },
                                                { 4,  5,  6 },
                                                { 70, 80, 90 }};
        csc232::TwoDimArray magicOrder5Table{{ 17, 24, 1,  8,  15 },
                                             { 23, 5,  7,  14, 16 },
                                             { 4,  6,  13, 20, 22 },
                                             { 10, 12, 19, 21, 3 },
                                             { 11, 18, 25, 2,  9 }};
        csc232::TwoDimArray magicOrder13Table{
                { 93,  108, 123, 138, 153, 168, 1,   16,  31,  46,  61,  76,  91 },
                { 107, 122, 137, 152, 167, 13,  15,  30,  45,  60,  75,  90,  92 },
                { 121, 136, 151, 166, 12,  14,  29,  44,  59,  74,  89,  104, 106 },
                { 135, 150, 165, 11,  26,  28,  43,  58,  73,  88,  103, 105, 120 },
                { 149, 164, 10,  25,  27,  42,  57,  72,  87,  102, 117, 119, 134 },
                { 163, 9,   24,  39,  41,  56,  71,  86,  101, 116, 118, 133, 148 },
                { 8,   23,  38,  40,  55,  70,  85,  100, 115, 130, 132, 147, 162 },
                { 22,  37,  52,  54,  69,  84,  99,  114, 129, 131, 146, 161, 7 },
                { 36,  51,  53,  68,  83,  98,  113, 128, 143, 145, 160, 6,   21 },
                { 50,  65,  67,  82,  97,  112, 127, 142, 144, 159, 5,   20,  35 },
                { 64,  66,  81,  96,  111, 126, 141, 156, 158, 4,   19,  34,  49 },
                { 78,  80,  95,  110, 125, 140, 155, 157, 3,   18,  33,  48,  63 },
                { 79,  94,  109, 124, 139, 154, 169, 2,   17,  32,  47,  62,  77 }};
    };

    // Run me to test your PrintTable function
    class PrintTableTestFixture : public CSC232BaseTestFixture
    {
    protected:
        void SetUp() override
        {
            ::testing::FLAGS_gtest_death_test_style = "threadsafe";
            ::testing::internal::CaptureStdout();
            possiblePoints += 1;
        }

        // Reusable objects for each unit test in this test fixture
        csc232::TwoDimArray table{{ 1, 2, 3 },
                                  { 4, 5, 6 },
                                  { 7, 8, 9 }};
    };

    TEST_F( PrintTableTestFixture, PrintFullTableTest )
    {
        // Given
        csc232::PrintTable( 3, 3, table );

        // Expect
        std::string expected{ "    1    2    3\n    4    5    6\n    7    8    9\n" };
        std::string actual{ testing::internal::GetCapturedStdout() };
        EXPECT_EQ( expected, actual );
    }

    TEST_F( PrintTableTestFixture, PrintFirstRowTableTest )
    {
        // Given
        csc232::PrintTable( 1, 3, table );

        // Expect
        std::string expected{ "    1    2    3\n" };
        std::string actual{ testing::internal::GetCapturedStdout() };
        EXPECT_EQ( expected, actual );
    }

    TEST_F( PrintTableTestFixture, PrintFirstColumnTableTest )
    {
        // Given
        csc232::PrintTable( 3, 1, table );

        // Expect
        std::string expected{ "    1\n    4\n    7\n" };
        std::string actual{ testing::internal::GetCapturedStdout() };
        EXPECT_EQ( expected, actual );
    }

    TEST_F( PrintTableTestFixture, PrintFirstTwoRowsTableTest )
    {
        // Given
        csc232::PrintTable( 2, 3, table );

        // Expect
        std::string expected{ "    1    2    3\n    4    5    6\n" };
        std::string actual{ testing::internal::GetCapturedStdout() };
        EXPECT_EQ( expected, actual );
    }

    TEST_F( PrintTableTestFixture, PrintFirstTwoColumnsTableTest )
    {
        // Given
        csc232::PrintTable( 3, 2, table );

        // Expect
        std::string expected{ "    1    2\n    4    5\n    7    8\n" };
        std::string actual{ testing::internal::GetCapturedStdout() };
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your IsMagicSquare function
    class MagicSquareTesterTestFixture : public CSC232BaseTestFixture
    {
    protected:
        // Reusable objects for each unit test in this test fixture
        csc232::TwoDimArray invalidOrder3Table{{ 1, 2, 3 },
                                               { 4, 5, 6 },
                                               { 7, 8, 9 }};
        csc232::TwoDimArray validOrder3Table{{ 2, 9, 4 },
                                             { 7, 5, 3 },
                                             { 6, 1, 8 }};
        csc232::TwoDimArray invalidOrder2Table{{ 1, 2 },
                                               { 3, 4 }};
        csc232::TwoDimArray invalidOrder1Table{{ 1 }};
        csc232::TwoDimArray invalidOrder4Table{{ 1,  2,  3,  4 },
                                               { 5,  6,  7,  8 },
                                               { 9,  10, 11, 12 },
                                               { 13, 14, 15, 16 }};
    };

    TEST_F( MagicSquareTesterTestFixture, ValidOrder3Table )
    {
        // Given
        bool expected{ true };

        // When
        bool actual{ csc232::IsMagicSquare( validOrder3Table, 3 ) };

        // Expect
        EXPECT_EQ( expected, actual );
    }

    TEST_F( MagicSquareTesterTestFixture, InvalidOrder3Table )
    {
        // Given
        bool expected{ false };

        // When
        bool actual{ csc232::IsMagicSquare( invalidOrder3Table, 3 ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( MagicSquareTesterTestFixture, InvalidOrder2Table )
    {
        EXPECT_DEATH( {
            csc232::IsMagicSquare( invalidOrder2Table, 2 );
        }, ".*failed.*" );
    }

    TEST_F( MagicSquareTesterTestFixture, InvalidOrder1Table )
    {
        EXPECT_DEATH( {
            csc232::IsMagicSquare( invalidOrder1Table, 1 );
        }, ".*failed.*" );
    }

    TEST_F( MagicSquareTesterTestFixture, InvalidOrder4Table )
    {
        EXPECT_DEATH( {
            csc232::IsMagicSquare( invalidOrder4Table, 4 );
        }, ".*failed.*" );
    }

    TEST_F( MagicSquareTesterTestFixture, InvalidOrderNegative )
    {
        EXPECT_DEATH( {
            csc232::IsMagicSquare( validOrder3Table, -3 );
        }, ".*failed.*" );
    }

    TEST_F( MagicSquareTesterTestFixture, InvalidOrderTooBig )
    {
        EXPECT_DEATH( {
            csc232::IsMagicSquare( validOrder3Table, 31 );
        }, ".*failed.*" );
    }

    // Run me to test your CalcMagicSquareSum function
    class CalculateMagicSquareSumTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( CalculateMagicSquareSumTestFixture, MagicSquareSumFailsOnNegativeOrder )
    {
        int order{ -1 };
        EXPECT_DEATH( {
            csc232::CalcMagicSquareSum( order );
        }, ".*failed.*" );
    }

    TEST_F( CalculateMagicSquareSumTestFixture, MagicSquareSumFailsOnZeroOrder )
    {
        int order{ 0 };
        EXPECT_DEATH( {
            csc232::CalcMagicSquareSum( order );
        }, ".*failed.*" );
    }

    TEST_F( CalculateMagicSquareSumTestFixture, MagicSquareSumSmallOddOrder )
    {
        // Given
        int order{ 1 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcMagicSquareSum( order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalculateMagicSquareSumTestFixture, MagicSquareSumSmallEvenOrder )
    {
        // Given
        int order{ 2 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcMagicSquareSum( order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalculateMagicSquareSumTestFixture, MagicSquareSumLargeOddOrder )
    {
        // Given
        int order{ 15 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcMagicSquareSum( order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalculateMagicSquareSumTestFixture, MagicSquareSumLargeEvenOrder )
    {
        // Given
        int order{ 16 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcMagicSquareSum( order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your CheckRows function
    class CheckRowsTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( CheckRowsTestFixture, CheckTableOrderOneWithCorrectSum )
    {
        // Given
        int order{ 1 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ true };

        // When
        bool actual{ csc232::CheckRows( order1Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckRowsTestFixture, CheckTableOrderThreeWithCorrectSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ true };

        // When
        bool actual{ csc232::CheckRows( magicOrder3Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckRowsTestFixture, CheckTableOrderThreeWithIncorrectSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ false };

        // When
        bool actual{ csc232::CheckRows( nonMagicOrder3Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckRowsTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        int order{ -1 };
        int magicSum{ 15 };

        // Expect
        EXPECT_DEATH( {
            csc232::CheckRows( magicOrder3Table, order, magicSum );
        }, ".*failed.*" );
    }

    TEST_F( CheckRowsTestFixture, CheckFailureWithNegativeMagicSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };

        // Expect
        EXPECT_DEATH( {
            csc232::CheckRows( magicOrder3Table, order, (-1 * magicSum));
        }, ".*failed.*" );
    }

    // Run me to test your CheckCols function
    class CheckColsTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( CheckColsTestFixture, CheckTableOrderOneWithCorrectSum )
    {
        // Given
        int order{ 1 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ true };

        // When
        bool actual{ csc232::CheckCols( order1Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckColsTestFixture, CheckTableOrderThreeWithCorrectSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ true };

        // When
        bool actual{ csc232::CheckCols( magicOrder3Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckColsTestFixture, CheckTableOrderThreeWithIncorrectSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ false };

        // When
        bool actual{ csc232::CheckCols( nonMagicOrder3Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckColsTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        int order{ -1 };
        int magicSum{ 15 };

        // Expect
        EXPECT_DEATH( {
            csc232::CheckCols( magicOrder3Table, order, magicSum );
        }, ".*failed.*" );
    }

    TEST_F( CheckColsTestFixture, CheckFailureWithNegativeMagicSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };

        // Expect
        EXPECT_DEATH( {
            csc232::CheckCols( magicOrder3Table, order, (-1 * magicSum));
        }, ".*failed.*" );
    }

    // Run me to test your CheckLRDiag function
    class CheckLRDiagTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( CheckLRDiagTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        int order{ -3 };
        int magicSum{ 15 };

        // Expect
        EXPECT_DEATH( {
            csc232::CheckLRDiag( magicOrder3Table, order, magicSum );
        }, ".*failed.*" );
    }

    TEST_F( CheckLRDiagTestFixture, CheckFailureWithNegativeMagicSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ -15 };

        // Expect
        EXPECT_DEATH( {
            csc232::CheckLRDiag( magicOrder3Table, order, magicSum );
        }, ".*failed.*" );
    }

    TEST_F( CheckLRDiagTestFixture, CheckTableOrderOneWithCorrectSum )
    {
        // Given
        int order{ 1 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ true };

        // When
        bool actual{ csc232::CheckLRDiag( order1Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckLRDiagTestFixture, CheckTableOrderThreeWithCorrectSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ true };

        // When
        bool actual{ csc232::CheckLRDiag( magicOrder3Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckLRDiagTestFixture, CheckTableOrderThreeWithIncorrectSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ false };

        // When
        bool actual{ csc232::CheckLRDiag( nonMagicOrder3Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your CheckRLDiag function
    class CheckRLDiagTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( CheckRLDiagTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        int order{ -3 };
        int magicSum{ 15 };

        // Expect
        EXPECT_DEATH( {
            csc232::CheckRLDiag( magicOrder3Table, order, magicSum );
        }, ".*failed.*" );
    }

    TEST_F( CheckRLDiagTestFixture, CheckFailureWithNegativeMagicSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ -15 };

        // Expect
        EXPECT_DEATH( {
            csc232::CheckRLDiag( magicOrder3Table, order, magicSum );
        }, ".*failed.*" );
    }

    TEST_F( CheckRLDiagTestFixture, CheckTableOrderOneWithCorrectSum )
    {
        // Given
        int order{ 1 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ true };

        // When
        bool actual{ csc232::CheckRLDiag( order1Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckRLDiagTestFixture, CheckTableOrderThreeWithCorrectSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ true };

        // When
        bool actual{ csc232::CheckRLDiag( magicOrder3Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CheckRLDiagTestFixture, CheckTableOrderThreeWithIncorrectSum )
    {
        // Given
        int order{ 3 };
        int magicSum{ (order * (order * order + 1)) / 2 };
        bool expected{ false };

        // When
        bool actual{ csc232::CheckRLDiag( nonMagicOrder3Table, order, magicSum ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your CalcRowTotal function
    class CalcRowTotalTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( CalcRowTotalTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        int order{ -3 };
        int row{ 0 };

        // Expect
        EXPECT_DEATH( {
            csc232::CalcRowTotal( magicOrder3Table, order, row );
        }, ".*failed.*" );
    }

    TEST_F( CalcRowTotalTestFixture, CheckFailureWithNegativeRow )
    {
        // Given
        int order{ 3 };
        int row{ -1 };

        // Expect
        EXPECT_DEATH( {
            csc232::CalcRowTotal( magicOrder3Table, order, row );
        }, ".*failed.*" );
    }

    TEST_F( CalcRowTotalTestFixture, CheckFailureWithMassiveRow )
    {
        // Given
        int order{ 3 };
        int row{ csc232::SIDE_DIMENSION };

        // Expect
        EXPECT_DEATH( {
            csc232::CalcRowTotal( magicOrder3Table, order, row );
        }, ".*failed.*" );
    }

    TEST_F( CalcRowTotalTestFixture, CheckSumOfFirstRow )
    {
        // Given
        int order{ 3 };
        int row{ 0 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcRowTotal( magicOrder3Table, order, row ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalcRowTotalTestFixture, CheckSumOfMiddleRow )
    {
        // Given
        int order{ 3 };
        int row{ order / 2 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcRowTotal( magicOrder3Table, order, row ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalcRowTotalTestFixture, CheckSumOfLastRow )
    {
        // Given
        int order{ 3 };
        int row{ order - 1 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcRowTotal( magicOrder3Table, order, row ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your CalcColTotal function
    class CalcColTotalTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed
    };

    TEST_F( CalcColTotalTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        int order{ -3 };
        int row{ 0 };

        // Expect
        EXPECT_DEATH( {
            csc232::CalcColTotal( magicOrder3Table, order, row );
        }, ".*failed.*" );
    }

    TEST_F( CalcColTotalTestFixture, CheckFailureWithNegativeRow )
    {
        // Given
        int order{ 3 };
        int row{ -1 };

        // Expect
        EXPECT_DEATH( {
            csc232::CalcColTotal( magicOrder3Table, order, row );
        }, ".*failed.*" );
    }

    TEST_F( CalcColTotalTestFixture, CheckFailureWithMassiveRow )
    {
        // Given
        int order{ 3 };
        int row{ csc232::SIDE_DIMENSION };

        // Expect
        EXPECT_DEATH( {
            csc232::CalcColTotal( magicOrder3Table, order, row );
        }, ".*failed.*" );
    }

    TEST_F( CalcColTotalTestFixture, CheckSumOfFirstRow )
    {
        // Given
        int order{ 3 };
        int row{ 0 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcColTotal( magicOrder3Table, order, row ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalcColTotalTestFixture, CheckSumOfMiddleRow )
    {
        // Given
        int order{ 3 };
        int row{ order / 2 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcColTotal( magicOrder3Table, order, row ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalcColTotalTestFixture, CheckSumOfLastRow )
    {
        // Given
        int order{ 3 };
        int row{ order - 1 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcColTotal( magicOrder3Table, order, row ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your CalcLRDiagTotal function
    class CalcLRDiagTotalTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( CalcLRDiagTotalTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        int order{ -3 };

        // Expect
        EXPECT_DEATH( {
            int total{ csc232::CalcLRDiagTotal( magicOrder3Table, order ) };
            std::cerr << "You shouldn't see this value: " << total << "\n";
        }, ".*failed.*" );
    }

    TEST_F( CalcLRDiagTotalTestFixture, CalcTotalOrderOne )
    {
        // Given
        int order{ 1 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcLRDiagTotal( order1Table, order ) };

        // Expect
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalcLRDiagTotalTestFixture, CalcTotalOrderOneEmbedded )
    {
        // Given
        int order{ 1 };
        int expected{ magicOrder3Table[ 0 ][ 0 ] };

        // When
        int actual{ csc232::CalcLRDiagTotal( magicOrder3Table, order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalcLRDiagTotalTestFixture, CalcTotalOrderThree )
    {
        // Given
        int order{ 3 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcLRDiagTotal( magicOrder3Table, order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your CalcRLDiagTotal function
    class CalcRLDiagTotalTestFixture : public CSC232BaseTestFixture
    {
    };

    TEST_F( CalcRLDiagTotalTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        int order{ -3 };

        // Expect
        EXPECT_DEATH( {
            int total{ csc232::CalcRLDiagTotal( magicOrder3Table, order ) };
            std::cerr << "You shouldn't see this value: " << total << "\n";
        }, ".*failed.*" );
    }

    TEST_F( CalcRLDiagTotalTestFixture, CalcTotalOrderOne )
    {
        // Given
        int order{ 1 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcRLDiagTotal( order1Table, order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalcRLDiagTotalTestFixture, CalcTotalOrderOneEmbedded )
    {
        // Given
        int order{ 1 };
        int expected{ magicOrder3Table[ 0 ][ order - 1 ] };

        // When
        int actual{ csc232::CalcRLDiagTotal( magicOrder3Table, order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    TEST_F( CalcRLDiagTotalTestFixture, CalcTotalOrderThree )
    {
        // Given
        int order{ 3 };
        int expected{ (order * (order * order + 1)) / 2 };

        // When
        int actual{ csc232::CalcRLDiagTotal( magicOrder3Table, order ) };

        // Then
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your InitializeMagicSquare function
    class InitializeMagicSquareTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( InitializeMagicSquareTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        csc232::TwoDimArray table{};
        int order{ -3 };

        // Expect
        EXPECT_DEATH( {
            csc232::InitializeMagicSquare( table, order );
        }, ".*failed.*" );
    }

    TEST_F( InitializeMagicSquareTestFixture, InitializeMagicSquareEmbedded )
    {
        // Given
        csc232::TwoDimArray table{};
        int order{ 3 };
        bool condition{ false };

        // When
        csc232::InitializeMagicSquare( table, order );

        // Then
        for (int row{ 0 }; row < order; ++row)
        {
            for (int col{ 0 }; col < order; ++col)
            {
                condition = (table[ row ][ col ] == 0);
            }
        }
        EXPECT_TRUE( condition );
    }

    // Run me to test your SetNextLocation function
    class SetNextLocationTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( SetNextLocationTestFixture, CheckFailureWithNegativeOrder )
    {
        // Given
        std::pair<int, int> location{ 0, 0 };
        int order{ -3 };

        // Expect
        EXPECT_DEATH( {
            csc232::SetNextLocation( magicOrder3Table, location, order );
        }, ".*failed.*" );
    }

    TEST_F( SetNextLocationTestFixture, ValidateFirstCaveat )
    {
        // Given
        int currentRow{ 0 };
        int currentCol{ 0 };
        std::pair<int, int> location{ currentRow, currentCol };
        int order{ 3 };

        // When
        csc232::SetNextLocation( magicOrder3Table, location, order );

        // Then
        std::pair<int, int> expected{ order - 1, currentCol + 1 };
        std::pair<int, int> actual{ location };
        EXPECT_EQ( expected, actual );
    }

    TEST_F( SetNextLocationTestFixture, ValidateSecondCaveat )
    {
        // Given
        int order{ 3 };
        int currentRow{ order - 1 };
        int currentCol{ order - 1 };
        std::pair<int, int> location{ currentRow, currentCol };

        // When
        csc232::SetNextLocation( magicOrder3Table, location, order );

        // Then
        std::pair<int, int> expected{ order - 2, 0 };
        std::pair<int, int> actual{ location };
        EXPECT_EQ( expected, actual );
    }

    TEST_F( SetNextLocationTestFixture, ValidateThirdCaveat )
    {
        // Given
        int order{ 3 };
        int currentRow{ 1 };
        int currentCol{ (order / 2) - 1 };
        std::pair<int, int> location{ currentRow, currentCol };

        // When
        csc232::SetNextLocation( magicOrder3Table, location, order );

        // Then
        std::pair<int, int> expected{ currentRow + 1, currentCol };
        std::pair<int, int> actual{ location };
        EXPECT_EQ( expected, actual );
    }

    TEST_F( SetNextLocationTestFixture, ValidateStandardMovement )
    {
        // Given
        int order{ 3 };
        int currentRow{ order / 2 };
        int currentCol{ order / 2 };
        std::pair<int, int> location{ currentRow, currentCol };

        // When
        csc232::SetNextLocation( initializedOrder3Table, location, order );

        // Then
        std::pair<int, int> expected{ currentRow - 1, currentCol + 1 };
        std::pair<int, int> actual{ location };
        EXPECT_EQ( expected, actual );
    }

    // Run me to test your IsValidCoordiante function
    class IsValidCoordinateTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( IsValidCoordinateTestFixture, ValidateCoordinateLowerEdgeCaseMinusOne )
    {
        // Given
        int order{ 3 };
        int coordinate{ -1 };

        // When
        bool condition{ csc232::IsValidCoordinate( coordinate, order ) };

        // Then
        EXPECT_FALSE( condition );
    }

    TEST_F( IsValidCoordinateTestFixture, ValidateCoordinateLowerEdgeCase )
    {
        // Given
        int order{ 3 };
        int coordinate{ 0 };

        // When
        bool condition{ csc232::IsValidCoordinate( coordinate, order ) };

        // Then
        EXPECT_TRUE( condition );
    }

    TEST_F( IsValidCoordinateTestFixture, ValidateCoordinateWithinValidRange )
    {
        // Given
        int order{ 3 };
        int coordinate{ order / 2 };

        // When
        bool condition{ csc232::IsValidCoordinate( coordinate, order ) };

        // Then
        EXPECT_TRUE( condition );
    }

    TEST_F( IsValidCoordinateTestFixture, ValidateCoordinateUpperEdgeCase )
    {
        // Given
        int order{ 3 };
        int coordinate{ order - 1 };

        // When
        bool condition{ csc232::IsValidCoordinate( coordinate, order ) };

        // Then
        EXPECT_TRUE( condition );
    }

    TEST_F( IsValidCoordinateTestFixture, ValidateCoordinateLessUpperEdgeCasePlusOne )
    {
        // Given
        int order{ 3 };
        int coordinate{ order };

        // When
        bool condition{ csc232::IsValidCoordinate( coordinate, order ) };

        // Then
        EXPECT_FALSE( condition );
    }

    // Run me to test your CreateMagicSquare function
    class CreateMagicSquareTestFixture : public CSC232BaseTestFixture
    {
        // No extensions needed...
    };

    TEST_F( CreateMagicSquareTestFixture, ConstructorCreatesMagicOrder3 )
    {
        // Given
        int order{ 3 };
        csc232::TwoDimArray twoDimArray;

        // When
        csc232::CreateMagicSquare( twoDimArray, order );

        // Then
        bool condition{ false };
        for (int row{ 0 }; row < order and not condition; ++row)
        {
            for (int col{ 0 }; col < order and not condition; ++col)
            {
                condition = (twoDimArray[ row ][ col ] == magicOrder3Table[ row ][ col ]);
            }

        }
        EXPECT_TRUE( condition );
    }

    TEST_F( CreateMagicSquareTestFixture, ConstructorCreatesMagicOrder5 )
    {
        // Given
        int order{ 5 };
        csc232::TwoDimArray twoDimArray;

        // When
        csc232::CreateMagicSquare( twoDimArray, order );

        // Then
        bool condition{ false };
        for (int row{ 0 }; row < order and not condition; ++row)
        {
            for (int col{ 0 }; col < order and not condition; ++col)
            {
                condition = (twoDimArray[ row ][ col ] == magicOrder5Table[ row ][ col ]);
            }

        }
        EXPECT_TRUE( condition );
    }

    TEST_F( CreateMagicSquareTestFixture, ConstructorCreatesMagicOrder13 )
    {
        // Given
        int order{ 13 };
        csc232::TwoDimArray twoDimArray;

        // When
        csc232::CreateMagicSquare( twoDimArray, order );


        // Then
        bool condition{ false };
        for (int row{ 0 }; row < order and not condition; ++row)
        {
            for (int col{ 0 }; col < order and not condition; ++col)
            {
                condition = (twoDimArray[ row ][ col ] == magicOrder13Table[ row ][ col ]);
            }

        }
        EXPECT_TRUE( condition );
    }

    TEST_F( CreateMagicSquareTestFixture, CantConstructEvenOrder )
    {
        // Given
        csc232::TwoDimArray twoDimArray;

        // Then
        EXPECT_DEATH( {
            csc232::CreateMagicSquare( twoDimArray, 2 );
        }, ".*failed.*" );
    }

    TEST_F( CreateMagicSquareTestFixture, CantConstructLargeOrder )
    {
        // Given
        csc232::TwoDimArray twoDimArray;

        // Expect
        EXPECT_DEATH( {
            csc232::CreateMagicSquare( twoDimArray, 15 );
        }, ".*failed.*" );
    }

} // end namespace

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest( &argc, argv );
    int result{ RUN_ALL_TESTS() };
    std::cout << std::fixed << std::setprecision( 2 );
    std::cout << "\n\n";
    std::cout << std::left << std::setw( 21 ) << "Earned Points:"
              << std::right << std::setw( 5 ) << static_cast<double>(earnedPoints) << std::endl;
    std::cout << std::left << std::setw( 21 ) << "Possible Points:"
              << std::right << std::setw( 5 ) << static_cast<double>(possiblePoints) << std::endl;
    double percentCorrect{ static_cast<double>(earnedPoints) / possiblePoints };
    double correctnessPoints{ possiblePoints != 0 ? percentCorrect * MAX_CORRECTNESS_PTS
                                                  : 0 };
    std::cout << std::left << std::setw( 21 ) << "Correctness Points:"
              << std::right << std::setw( 5 ) << correctnessPoints << std::endl;
    return result;
}
