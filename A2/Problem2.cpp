// File Name: Problem2.cpp
// Project: CS 170 Assignment 2 Problem 2
// Author: Gogi Benny
// Date: Sunday, April 19, 2026
//
// Purpose: Plot the values of two sequence functions by passing them as
// arguments and displaying rows of asterisks.
//
// Major Items:
// - Function pointer plot of values returned by two different sequence functions
// - Iterative calculation of the sequence 1 - 1/3 + 1/5 - 1/7 + ...
// - Recursive calculation of the sequence 1 + 1/3 + 1/5 + 1/7 + ...
// - Input validation for the user-selected minimum and maximum number of terms (EXTRA)
// - Recursive helper function for printing rows of asterisks (EXTRA)
// - Version control using Git & GitHub:
// https://github.com/dozothebozo/CS170/blob/main/A2/Problem2.cpp (EXTRA)

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// function prototypes
void ignoreLine();
bool recoverStream();
int getIntegerInRange(const string& prompt, int min, int max);
double sumSequence1(int count);
double sumSequence2(int count);
void printStars(int starCount);
void plot(double sequenceFunction(int), int minCount, int maxCount);

// global declarations of constants
const int IGNORE_SIZE = 1000;
const int MIN_TERMS = 1;
const int MAX_TERMS = 20;
const double STAR_VALUE = 0.1;

int main()
{
    int minCount = getIntegerInRange("Enter the smallest number of terms to plot (" +
                                         to_string(MIN_TERMS) + "-" + to_string(MAX_TERMS) + "): ",
                                     MIN_TERMS, MAX_TERMS);

    int maxCount = getIntegerInRange("Enter the largest number of terms to plot (" +
                                         to_string(minCount) + "-" + to_string(MAX_TERMS) + "): ",
                                     minCount, MAX_TERMS);

    cout << "\nEach * represents " << STAR_VALUE << "\n\n";

    cout << "sumSequence1\n";
    plot(sumSequence1, minCount, maxCount);

    cout << "\nsumSequence2\n";
    plot(sumSequence2, minCount, maxCount);

    return 0;
}

/**
   Ignores all remaining characters in the current input line.
*/
void ignoreLine()
{
    cin.ignore(IGNORE_SIZE, '\n');
}

/**
   Checks the input stream and attempts to recover from stream failure.
   @return true if the stream required recovery, false otherwise
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
   Prompts the user for an integer value within a given inclusive range.
   @param prompt the message displayed to the user
   @param min the minimum valid integer value
   @param max the maximum valid integer value
   @return a validated integer in the range [min, max]
*/
int getIntegerInRange(const string& prompt, int min, int max)
{
    while (true)
    {
        int value{};

        cout << prompt;
        cin >> value;

        if (recoverStream())
        {
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        ignoreLine();

        if (value < min || value > max)
        {
            cout << "Please enter an integer from " << min << " to " << max << ".\n";
            continue;
        }

        return value;
    }
}

/**
   Calculates and returns the sum of the first count terms in the sequence
   1 - 1/3 + 1/5 - 1/7 + 1/9 ... using iteration.
   @param count the number of terms to sum
   @return the sum of the first count terms in the sequence
*/
double sumSequence1(int count)
{
    double sum = 0.0;

    for (int term = 1; term <= count; term++)
    {
        double denominator = static_cast<double>(2 * term - 1);

        if (term % 2 == 0)
        {
            sum -= 1.0 / denominator;
        }
        else
        {
            sum += 1.0 / denominator;
        }
    }

    return sum;
}

/**
   Calculates and returns the sum of the first count terms in the sequence
   1 + 1/3 + 1/5 + 1/7 + 1/9 ... using recursion.
   @param count the number of terms to sum
   @return the sum of the first count terms in the sequence
*/
double sumSequence2(int count)
{
    if (count <= 0)
    {
        return 0.0;
    }

    return sumSequence2(count - 1) + 1.0 / static_cast<double>(2 * count - 1);
}

/**
   Recursively prints the given number of asterisks.
   @param starCount the number of asterisks to print
*/
void printStars(int starCount)
{
    if (starCount <= 0)
    {
        return;
    }

    cout << '*';
    printStars(starCount - 1);
}

/**
   Plots the values returned by a sequence function for counts in a given range.
   @param sequenceFunction the function used to calculate each sequence value
   @param minCount the smallest count value to plot
   @param maxCount the largest count value to plot
*/
void plot(double sequenceFunction(int), int minCount, int maxCount)
{
    for (int count = minCount; count <= maxCount; count++)
    {
        double value = sequenceFunction(count);
        int starCount = static_cast<int>(value / STAR_VALUE + 0.5);

        cout << "count = " << setw(2) << count << "   value = " << fixed << setprecision(6) << value
             << "   ";

        printStars(starCount);
        cout << '\n';
    }
}
