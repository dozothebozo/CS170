// File Name: Problem3.cpp
// Project: CS 170 Assignment 1 Problem 3
// Author: Gogi Benny
// Date: Friday, March 13, 2026
//
// Purpose: Prompt the user for a valid positive integer range, generate a random integer in 
// that range, check whether its last digit satisfies the required checksum rule, and if not,
// try to repair the number by modifying each middle digit and showing all valid solutions found.
//
// Major Items:
// - Global constants for input cleanup size and valid integer bounds
// - Input validation for EOF/stream failure and integer range entry
// - Checksum validation using integer digit extraction only
// - Repair process that visits digits d2 through d(n-1) and shows all solutions found
// - Pass by reference in validateRange(int& lowerBound, int& upperBound) (EXTRA)
// - Pass by const reference in getInteger(const string& prompt) (EXTRA)
// - Version control using Git & GitHub: https://github.com/dozothebozo/CS170/blob/main/Problem3.cpp (EXTRA)

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// function prototypes
void ignoreLine();
bool recoverStream();
int getInteger(const string& prompt);
void validateRange(int& lowerBound, int& upperBound);
int generateRandomIntegerInRange(int lowerBound, int upperBound);
int getDecimalLength(int number);
int getLeftmostPlaceValue(int number);
bool isValidCheckSum(int number, int length);
void repairNumber(int number, int length);

// global declarations of constants
const int IGNORE_SIZE = 1000;
const int MIN_VALUE = 100;
const int MAX_VALUE = 999999999;

int main() {
    // explicit cast time to avoid implicit conversion
    srand(static_cast<unsigned int>(time(0)));

    int lowerBound;
    int upperBound;
    int randomNum;
    int randomNumLength;

    validateRange(lowerBound, upperBound);

    randomNum = generateRandomIntegerInRange(lowerBound, upperBound);
    randomNumLength = getDecimalLength(randomNum);

    cout << "The generated random integer in the range [" << lowerBound << ", "
         << upperBound << "] is " << randomNum << ".\n";

    if (isValidCheckSum(randomNum, randomNumLength)) {
        cout << "Success: " << randomNum << " is valid.\n";
    }
    else {
        cout << randomNum << " does not satisfy the checksum rule.\n";
        cout << "Trying to repair the number by modifying each middle digit:\n";
        repairNumber(randomNum, randomNumLength);
    }

    return 0;
}

/**
   Ignores the rest of the current input line.
*/
void ignoreLine() { 
    cin.ignore(IGNORE_SIZE, '\n');
}

/**
   Recovers the input stream after a failure.
   @return true if recovery was needed, false otherwise
*/
bool recoverStream() {
    if (!cin) {
        if (cin.eof()) {
            exit(1);
        }

        cin.clear();
        ignoreLine();
        return true;
    }

    return false;
}

/**
   Prompts the user for an integer and validates the input stream.
   @param prompt the message displayed to the user
   @return the validated integer entered by the user
*/
int getInteger(const string& prompt) {
    while (true) {
        int x{};

        cout << prompt;
        cin >> x;

        if (recoverStream()) {
            cout << "Invalid input. Please enter an integer.\n";
            continue;
        }

        ignoreLine();
        return x;
    }
}

/**
   Prompts the user for a range and does input validations
   @param lowerBound the validated lower bound
   @param upperBound the validated upper bound
*/
void validateRange(int& lowerBound, int& upperBound) {
    while (true) {
        lowerBound = getInteger("Enter a positive lower bound (3 to 9 digits): ");
        upperBound = getInteger("Enter a positive upper bound (3 to 9 digits): ");

        // bounds must be positive integers
        if (lowerBound <= 0 || upperBound <= 0) {
            cout << "Bounds must be positive integers. Please try again.\n";
        }
        // lower bound cannot exceed upper bound
        else if (lowerBound > upperBound) {
            cout << "The lower bound cannot be greater than the upper bound. "
                << "Please try again.\n";
        }
        // keep the integers within the required 3 digit to 9 digit range
        else if (lowerBound < MIN_VALUE || upperBound > MAX_VALUE) {
            cout << "The range must stay within [" << MIN_VALUE << ", " << MAX_VALUE
                << "] so generated integers have length 3 to 9. Please try again.\n";
        }
        // minimum interval limit based on RAND_MAX
        else if ((upperBound - lowerBound) > RAND_MAX) {
            cout << "The interval length cannot exceed " << RAND_MAX
                << ". Please try again.\n";
        }
        else {
            return;
        }
    }
}

/**
   Generates a random integer in a validated range.
   @param lowerBound the lower bound of the range
   @param upperBound the upper bound of the range
   @return a random integer in the interval [lowerBound, upperBound]
*/
int generateRandomIntegerInRange(int lowerBound, int upperBound) {
    return lowerBound + rand() % (upperBound - lowerBound + 1);
}

/**
   Determines the number of decimal digits in a positive integer.
   @param number the positive integer to examine
   @return the number of decimal digits in the integer
*/
int getDecimalLength(int number) {
    int length = 0;

    while (number > 0) {
        length++;
        number /= 10;
    }

    return length;
}

/**
   Determines the place value of the leftmost digit in a positive integer.
   @param number the positive integer to examine
   @return the place value of the leftmost digit
*/
int getLeftmostPlaceValue(int number) {
    int placeValue = 1;

    while (number >= 10) {
        number /= 10;
        placeValue *= 10;
    }

    return placeValue;
}

/**
   Determines whether the last digit of a number matches the required checksum.
   @param number the integer to test
   @param length the number of decimal digits in the integer
   @return true if the checksum is valid, false otherwise
*/
bool isValidCheckSum(int number, int length) {
    int placeValue = getLeftmostPlaceValue(number);
    int lastDigit = number % 10;
    int checkSum = 0;

    // process digits from left to right, excluding the last digit
    for (int i = 1; i < length; i++) {
        int currentDigit = number / placeValue;
        checkSum += currentDigit * i;
        number %= placeValue;
        placeValue /= 10;
    }

    checkSum %= (length + 1);

    return checkSum == lastDigit;
}

/**
   Tries to repair an invalid number by modifying each middle digit and
   shows all valid solutions found.
   @param number the invalid number to repair
   @param length the number of decimal digits in the integer
*/
void repairNumber(int number, int length) {
    bool hasSolution = false;
    int placeValue = getLeftmostPlaceValue(number);
    int temp = number;

    // visit digits d2 through d(n-1)
    for (int i = 0; i < length - 2; i++) {
        temp %= placeValue;
        placeValue /= 10;

        int currentDigit = temp / placeValue;

        for (int j = 0; j <= 9; j++) {
            if (j == currentDigit) {
                continue;
            }

            // replace the current middle digit and test the new number
            int newSolution = number - (currentDigit * placeValue) + (j * placeValue);

            if (isValidCheckSum(newSolution, length)) {
                cout << "Valid solution found: " << newSolution << '\n';
                hasSolution = true;
            }
        }
    }

    if (!hasSolution) {
        cout << "No valid repaired solutions were found.\n";
    }
}
