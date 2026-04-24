// File Name: Problem3.cpp
// Project: CS 170 Assignment 2 Problem 3
// Author: Gogi Benny
// Date: Thursday, April 24, 2026
//
// Purpose: Prompt the user for a valid odd order and construct and display
// a magic square of that order using the given algorithm.
//
// Major Items:
// - Construction of an odd-order magic square using a vector of vectors
// - Input validation for EOF/stream failure, range validation, and odd order selection
// - Wrapped movement and collision handling for placement of values 1 through n^2
// - Improved aligned square output based on the width of the largest value (EXTRA)
// - Version control using Git & GitHub:
// https://github.com/dozothebozo/CS170/blob/main/A2/Problem3.cpp (EXTRA)

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// function prototypes
void ignoreLine();
bool recoverStream();
int getIntegerInRange(int min, int max, const string& prompt);
bool getBoolean(const string& prompt);
int getOddOrder();
vector<vector<int>> buildMagicSquare(int order);
void printMagicSquare(const vector<vector<int>>& square);
int getNumberWidth(int number);

// global declarations of constants
const int IGNORE_SIZE = 1000;
const int MIN_ORDER = 1;
const int MAX_ORDER = 15;

int main()
{
    do
    {
        int order = getOddOrder();
        vector<vector<int>> magicSquare = buildMagicSquare(order);

        cout << "\nMagic square of order " << order << ":\n\n";
        printMagicSquare(magicSquare);
        cout << '\n';
    } while (getBoolean("Would you like to generate another magic square? (y/n): "));

    return 0;
}

/**
   Ignores the rest of the current input line.
*/
void ignoreLine()
{
    cin.ignore(IGNORE_SIZE, '\n');
}

/**
   Recovers the input stream after a failure.
   @return true if recovery was needed, false otherwise
*/
bool recoverStream()
{
    if (!cin)
    {
        if (cin.eof())
        {
            exit(1);
        }

        cin.clear();
        ignoreLine();
        return true;
    }

    return false;
}

/**
   Prompts the user for an integer within a given inclusive range.
   @param min the minimum valid integer
   @param max the maximum valid integer
   @param prompt the message displayed to the user
   @return the validated integer value
*/
int getIntegerInRange(int min, int max, const string& prompt)
{
    while (true)
    {
        int value{};

        cout << prompt;
        cin >> value;

        if (recoverStream())
        {
            cout << "Invalid input. Please enter an integer.\n";
            continue;
        }

        ignoreLine();

        if (value < min || value > max)
        {
            cout << "Input must be between " << min << " and " << max << ". Please try again.\n";
            continue;
        }

        return value;
    }
}

/**
   Prompts the user for a yes or no response.
   @param prompt the message displayed to the user
   @return true for y or Y, false for n or N
*/
bool getBoolean(const string& prompt)
{
    while (true)
    {
        char value{};

        cout << prompt;
        cin >> value;

        if (recoverStream())
        {
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        ignoreLine();

        if (value == 'y' || value == 'Y')
        {
            return true;
        }

        if (value == 'n' || value == 'N')
        {
            return false;
        }

        cout << "Please enter y or n.\n";
    }
}

/**
   Prompts the user for a valid odd order for the magic square.
   @return a validated odd integer order
*/
int getOddOrder()
{
    while (true)
    {
        int order =
            getIntegerInRange(MIN_ORDER, MAX_ORDER,
                              "Enter an odd order for the magic square (" + to_string(MIN_ORDER) +
                                  "-" + to_string(MAX_ORDER) + "): ");

        if (order % 2 == 0)
        {
            cout << "This construction method works only for odd orders. Please try again.\n";
            continue;
        }

        return order;
    }
}

/**
   Constructs and returns a magic square of the given odd order using the algorithm:
   place 1 in the middle of the bottom row, then move right and down with wrapping,
   or move one square up when the target square is already filled.
   @param order the odd order of the magic square
   @return the completed magic square
*/
vector<vector<int>> buildMagicSquare(int order)
{
    vector<vector<int>> square(order, vector<int>(order, 0));

    int row = order - 1;
    int col = order / 2;

    square[row][col] = 1;

    for (int value = 2; value <= order * order; value++)
    {
        int nextRow = (row + 1) % order;
        int nextCol = (col + 1) % order;

        if (square[nextRow][nextCol] == 0)
        {
            row = nextRow;
            col = nextCol;
        }
        else
        {
            row = (row - 1 + order) % order;
        }

        square[row][col] = value;
    }

    return square;
}

/**
   Prints a magic square with aligned columns based on the width of the largest
   value in the square.
   @param square the magic square to print
*/
void printMagicSquare(const vector<vector<int>>& square)
{
    int order = static_cast<int>(square.size());
    int fieldWidth = getNumberWidth(order * order) + 1;

    for (int row = 0; row < order; row++)
    {
        for (int col = 0; col < order; col++)
        {
            cout << setw(fieldWidth) << square[row][col];
        }

        cout << '\n';
    }
}

/**
   Determines the number of decimal digits in a positive integer.
   @param number the positive integer to examine
   @return the number of decimal digits in the integer
*/
int getNumberWidth(int number)
{
    int width = 0;

    while (number > 0)
    {
        width++;
        number /= 10;
    }

    return width;
}
