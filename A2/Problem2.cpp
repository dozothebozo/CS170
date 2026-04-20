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

void ignoreLine()
{
    cin.ignore(IGNORE_SIZE, '\n');
}

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

double sumSequence2(int count)
{
    if (count <= 0)
    {
        return 0.0;
    }

    return sumSequence2(count - 1) + 1.0 / static_cast<double>(2 * count - 1);
}

void printStars(int starCount)
{
    if (starCount <= 0)
    {
        return;
    }

    cout << '*';
    printStars(starCount - 1);
}

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
