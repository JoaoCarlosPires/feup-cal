#include <gtest/gtest.h>
#include <gmock/gmock.h>

/**
//#include "Defs.h"
#include "Factorial.h"
#include "Change.h"
#include "Sum.h"
#include "Partitioning.h"
*/

#include "Sudoku.h"
#include "Labirinth.h"

using namespace std;
using testing::Eq;


void compareSudokus(int in[9][9], int out[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int a = 0; a < 9; a++)
            ASSERT_EQ(in[i][a], out[i][a]);
    }
}


TEST(CAL_FP02, testSudokuAlreadySolved) {
    int in[9][9] =
            {{8, 6, 2, 3, 4, 1, 7, 9, 5},
             {1, 5, 4, 9, 7, 6, 3, 8, 2},
             {9, 3, 7, 8, 2, 5, 1, 4, 6},
             {5, 7, 6, 1, 3, 8, 9, 2, 4},
             {2, 1, 8, 5, 9, 4, 6, 3, 7},
             {3, 4, 9, 7, 6, 2, 8, 5, 1},
             {6, 2, 3, 4, 8, 7, 5, 1, 9},
             {7, 8, 5, 2, 1, 9, 4, 6, 3},
             {4, 9, 1, 6, 5, 3, 2, 7, 8}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int out[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
    for (int a = 0; a < 9; a++)
    out[i][a] = res[i][a];

    compareSudokus(in, out);

}


TEST(CAL_FP02, testSudokuNoneBackStepsRequired) {
    int in[9][9] =
            {{8, 6, 0, 0, 0, 0, 0, 9, 0},
             {0, 0, 4, 0, 7, 6, 3, 0, 0},
             {9, 0, 0, 0, 2, 5, 1, 0, 0},
             {0, 7, 6, 1, 3, 0, 0, 2, 0},
             {2, 1, 0, 0, 0, 0, 0, 3, 7},
             {0, 4, 0, 0, 6, 2, 8, 5, 0},
             {0, 0, 3, 4, 8, 0, 0, 0, 9},
             {0, 0, 5, 2, 1, 0, 4, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 7, 8}};

    int out[9][9] =
            {{8, 6, 2, 3, 4, 1, 7, 9, 5},
             {1, 5, 4, 9, 7, 6, 3, 8, 2},
             {9, 3, 7, 8, 2, 5, 1, 4, 6},
             {5, 7, 6, 1, 3, 8, 9, 2, 4},
             {2, 1, 8, 5, 9, 4, 6, 3, 7},
             {3, 4, 9, 7, 6, 2, 8, 5, 1},
             {6, 2, 3, 4, 8, 7, 5, 1, 9},
             {7, 8, 5, 2, 1, 9, 4, 6, 3},
             {4, 9, 1, 6, 5, 3, 2, 7, 8}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
    for (int a = 0; a < 9; a++)
    sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}


TEST(CAL_FP02, testSudokuSomeBackStepsRequired) {
    int in[9][9] =
            {{7, 0, 5, 2, 6, 3, 4, 0, 9},
             {0, 0, 0, 0, 0, 0, 0, 3, 0},
             {0, 0, 0, 0, 8, 0, 0, 0, 0},
             {0, 0, 9, 5, 0, 4, 0, 0, 2},
             {5, 0, 6, 0, 0, 0, 7, 0, 8},
             {2, 0, 0, 8, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 1, 0, 0, 0, 0},
             {0, 2, 0, 0, 0, 0, 0, 0, 0},
             {3, 0, 8, 7, 2, 9, 6, 0, 4}};

    int out[9][9] =
            {{7, 1, 5, 2, 6, 3, 4, 8, 9},
             {8, 6, 4, 9, 5, 7, 2, 3, 1},
             {9, 3, 2, 4, 8, 1, 5, 7, 6},
             {1, 8, 9, 5, 7, 4, 3, 6, 2},
             {5, 4, 6, 1, 3, 2, 7, 9, 8},
             {2, 7, 3, 8, 9, 6, 1, 4, 5},
             {4, 9, 7, 6, 1, 5, 8, 2, 3},
             {6, 2, 1, 3, 4, 8, 9, 5, 7},
             {3, 5, 8, 7, 2, 9, 6, 1, 4}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
    for (int a = 0; a < 9; a++)
    sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}


TEST(CAL_FP02, testSudokuManyBackStepsRequired) {
    int in[9][9] =
            {{1, 0, 0, 0, 0, 7, 0, 0, 0},
             {0, 7, 0, 0, 6, 0, 8, 0, 0},
             {2, 0, 0, 0, 4, 0, 6, 0, 0},
             {7, 6, 4, 0, 0, 0, 9, 0, 0},
             {0, 0, 0, 0, 2, 0, 5, 6, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 3, 0, 0, 0, 0},
             {4, 0, 0, 1, 0, 0, 0, 0, 5},
             {0, 5, 0, 0, 0, 4, 0, 9, 0}};

    int out[9][9] =
            {{1, 4, 6, 8, 5, 7, 2, 3, 9},
             {3, 7, 9, 2, 6, 1, 8, 5, 4},
             {2, 8, 5, 9, 4, 3, 6, 7, 1},
             {7, 6, 4, 3, 1, 5, 9, 2, 8},
             {8, 3, 1, 4, 2, 9, 5, 6, 7},
             {5, 9, 2, 6, 7, 8, 4, 1, 3},
             {9, 1, 8, 5, 3, 2, 7, 4, 6},
             {4, 2, 7, 1, 9, 6, 3, 8, 5},
             {6, 5, 3, 7, 8, 4, 1, 9, 2}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int **res = s.getNumbers();

    for (int i = 0; i < 9; i++)
    for (int a = 0; a < 9; a++)
    sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}


TEST(CAL_FP02, testSudokuWithMinimalClues) {
    int in[9][9] =
            {{7, 0, 0, 1, 0, 8, 0, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    int out[9][9] =
            {{7, 5, 2, 1, 3, 8, 6, 9, 4},
             {1, 9, 8, 7, 4, 6, 5, 3, 2},
             {4, 3, 6, 2, 9, 5, 7, 8, 1},
             {2, 8, 3, 4, 5, 9, 1, 6, 7},
             {9, 6, 1, 8, 2, 7, 3, 4, 5},
             {5, 7, 4, 6, 1, 3, 8, 2, 9},
             {6, 1, 9, 3, 7, 2, 4, 5, 8},
             {8, 4, 5, 9, 6, 1, 2, 7, 3},
             {3, 2, 7, 5, 8, 4, 9, 1, 6}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
    for (int a = 0; a < 9; a++)
    sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}


TEST(CAL_FP02, testSudokuWithMultipleSolutions) {
    int in[9][9] =
            {{0, 0, 0, 1, 0, 8, 0, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    Sudoku s(in);
    EXPECT_EQ(s.solve() && s.isComplete(), true);
    int** out = s.getNumbers();
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
            if (in[i][j] != 0)
                EXPECT_EQ(in[i][j], out[i][j]);
}


TEST(CAL_FP02, testSudokuEmpty) {
    int in[9][9] =
            {{0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);
    EXPECT_EQ(s.isComplete(), true);
}


TEST(CAL_FP02, testSudokuImpossible) {
    int in[9][9] =
            {{7, 0, 0, 1, 0, 8, 0, 0, 0},
             {4, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), false);

    int out[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            out[i][a] = res[i][a];

    compareSudokus(in, out);
}


TEST(CAL_FP02, testLabirinth) {
    int lab1[10][10] ={
            {0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,1,0,1,0,0},
            {0,1,0,0,0,1,0,1,0,0},
            {0,1,1,0,1,1,1,1,1,0},
            {0,1,0,0,0,1,0,0,0,0},
            {0,1,0,1,0,1,1,1,1,0},
            {0,1,1,1,0,0,1,0,1,0},
            {0,1,0,0,0,0,1,0,1,0},
            {0,1,1,1,0,0,1,2,0,0},
            {0,0,0,0,0,0,0,0,0,0}};

    int lab2[10][10] ={
            {0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,1,0,1,0,0},
            {0,1,0,0,0,1,0,1,0,0},
            {0,1,1,0,1,1,1,1,1,0},
            {0,1,0,0,0,1,0,0,0,0},
            {0,1,0,1,0,1,1,1,1,0},
            {0,1,1,1,0,0,1,0,1,0},
            {0,1,0,0,0,0,1,0,1,0},
            {0,1,1,1,0,0,0,2,0,0},
            {0,0,0,0,0,0,0,0,0,0}};

    Labirinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1, 1),true);


    Labirinth l2(lab2);
    EXPECT_EQ(l2.findGoal(1, 1),false);

    /*
    l1.printLabirinth();
    cout << endl;
    l1.printVisited();
    cout << endl << endl;

    l2.printLabirinth();
    cout << endl;
    l2.printVisited();
    cout << endl << endl;
     */

}


