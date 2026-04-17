// File Name: Problem1.cpp
// Project: CS 170 Assignment 2 Problem 1
// Author: Gogi Benny
// Date: Friday, April 17, 2026
//
// Purpose: Test a function with variable number of arguments that determines
// whether a sequence of double values is in ascending order.
//
// Major Items:
// - Function ordered(int count, ...) using C-style variable arguments
// - Additional edge-case tests and summary count of passed tests
// - Version control using Git & GitHub:
//   https://github.com/dozothebozo/CS170/blob/main/A2/Problem1.cpp (EXTRA)

#include <cstdarg>
#include <iostream>
#include <string>

using namespace std;

// function prototypes
bool ordered(int count, ...);
void showTestResult(const string& testName, bool expected, bool actual, int& passedTests,
                    int& totalTests);
void runTests();

int main()
{
    runTests();
    return 0;
}

/**
   Determines whether the given double arguments form an ascending sequence.
   Equal adjacent values are accepted.

   @param count the number of double arguments to examine
   @return true if the sequence is ascending, false otherwise
*/
bool ordered(int count, ...)
{
    if (count < 0)
    {
        return false;
    }

    if (count <= 1)
    {
        return true;
    }

    va_list arguments;
    va_start(arguments, count);

    double previous = va_arg(arguments, double);

    for (int argIndex = 1; argIndex < count; argIndex++)
    {
        double current = va_arg(arguments, double);

        if (current < previous)
        {
            va_end(arguments);
            return false;
        }

        previous = current;
    }

    va_end(arguments);
    return true;
}

/**
   Displays one test case result and updates the test counters.

   @param testName the label for the test case
   @param expected the expected result for the test
   @param actual the actual result produced by the function
   @param passedTests the number of tests passed so far
   @param totalTests the total number of tests run so far
*/
void showTestResult(const string& testName, bool expected, bool actual, int& passedTests,
                    int& totalTests)
{
    totalTests++;

    cout << testName << '\n';
    cout << "Expected: " << expected << '\n';
    cout << "Actual:   " << actual << '\n';

    if (expected == actual)
    {
        cout << "Result:   PASS\n\n";
        passedTests++;
    }
    else
    {
        cout << "Result:   FAIL\n\n";
    }
}

/**
   Runs a set of tests for the ordered function and displays the results.
*/
void runTests()
{
    int passedTests = 0;
    int totalTests = 0;

    cout << boolalpha;
    cout << "Testing ordered(int count, ...)\n\n";

    showTestResult("ordered(3, 1.0, 2.5, 15.0)", true, ordered(3, 1.0, 2.5, 15.0), passedTests,
                   totalTests);

    showTestResult("ordered(2, 1.0, 1.0)", true, ordered(2, 1.0, 1.0), passedTests, totalTests);

    showTestResult("ordered(4, 2.0, 1.0, 15.0, 16.5)", false, ordered(4, 2.0, 1.0, 15.0, 16.5),
                   passedTests, totalTests);

    showTestResult("ordered(1, 7.5)", true, ordered(1, 7.5), passedTests, totalTests);

    showTestResult("ordered(5, 1.0, 2.0, 2.0, 3.0, 4.0)", true, ordered(5, 1.0, 2.0, 2.0, 3.0, 4.0),
                   passedTests, totalTests);

    showTestResult("ordered(0)", true, ordered(0), passedTests, totalTests);

    showTestResult("ordered(-1)", false, ordered(-1), passedTests, totalTests);

    cout << "\nPassed " << passedTests << " out of " << totalTests << " tests.\n";
}
