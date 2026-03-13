// File Name: Problem2.cpp
// Project: CS 170 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: Wednesday, March 11, 2026
//
// Purpose: Read a Roman number from the user, validate the input, and convert it to its decimal equivalent.
//
// Major Items:
// - Global constant for stream cleanup size
// - Input validation for EOF/stream failure, empty input, and invalid characters
// - Roman number validation for repetition rules and subtractive pairs
// - Pass by const reference for romanToDecimal(const string &roman) (EXTRA)
// - Version control using Git & GitHub: https://github.com/dozothebozo/CS170/blob/main/Problem2.cpp (EXTRA)

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// function prototypes
void ignoreLine();
void recoverStream();
bool isRomanChar(char ch);
int getRomanCharValue(char ch);
bool isValidRomanPair(char first, char second);
bool isConsecutive(const string& roman);
bool isValidRomanNumber(const string& roman);
string getRomanNumber();
int romanToDecimal(const string& roman);

// global declarations of constants
const int IGNORE_SIZE = 1000;

int main() {
    string roman = getRomanNumber();
    cout << "Roman number " << roman << " is equal to " << romanToDecimal(roman) << '\n';
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
*/
void recoverStream() {
    if (cin.eof()) {
        exit(1);
    }
    cin.clear();
    ignoreLine();
}

/**
   Determines if a character is a valid Roman number letter.
   @param ch the character to check
   @return true if the character is a Roman number letter, false otherwise
*/
bool isRomanChar(char ch) {
    switch (toupper(ch)) {
    case 'I':
    case 'V':
    case 'X':
    case 'L':
    case 'C':
    case 'D':
    case 'M':
        return true;
    default:
        return false;
    }
}

/**
   Gets the decimal value of a single Roman number character.
   @param ch the Roman number character
   @return the decimal value of the Roman number character
*/
int getRomanCharValue(char ch) {
    switch (toupper(ch)) {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0;
    }
}

/**
   Checks if two consecutive Roman number characters form a valid subtractive
   pair.
   @param first the first character of the pair
   @param second the second character of the pair
   @return true if the pair is a valid subtractive pair, false otherwise
*/
bool isValidRomanPair(char first, char second) {
    if (first == 'I') {
        return second == 'V' || second == 'X';
    }
    else if (first == 'X') {
        return second == 'L' || second == 'C';
    }
    else if (first == 'C') {
        return second == 'D' || second == 'M';
    }

    return false;
}

/**
   Checks if a Roman number string has valid consecutive formatting.
   @param roman the Roman number string to check
   @return true if the string has valid repetition rules, false otherwise
*/
bool isConsecutive(const string& roman) {
    int repeat = 1;

    for (int i = 1; i < roman.length(); i++) {
        if (roman[i] == roman[i - 1]) {
            repeat++;
        }
        else {
            repeat = 1;
        }

        // no symbol may repeat more than three times
        if (repeat > 3) {
            return false;
        }

        // V, L, and D may not repeat
        if ((roman[i] == 'V' || roman[i] == 'L' || roman[i] == 'D') && repeat > 1) {
            return false;
        }
    }

    return true;
}

/**
   Determines if a Roman number string follows the Roman number rules.
   @param roman the Roman number string to check
   @return true if the Roman number format is valid, false otherwise
*/
bool isValidRomanNumber(const string& roman) {
    if (!isConsecutive(roman)) {
        return false;
    }

    for (int i = 1; i < roman.length(); i++) {
        int previousCharValue = getRomanCharValue(roman[i - 1]);
        int currentCharValue = getRomanCharValue(roman[i]);

        // if values increase, the two symbols must form a valid subtractive pair
        if (previousCharValue < currentCharValue) {
            if (!isValidRomanPair(roman[i - 1], roman[i])) {
                return false;
            }

            // repeated symbols may not be used before a subtractive pair
            if (i >= 2 && roman[i - 2] == roman[i - 1]) {
                return false;
            }

            // after a subtractive pair, the next value may not increase again
            if (i + 1 < roman.length()) {
                int nextCharValue = getRomanCharValue(roman[i + 1]);
                if (nextCharValue > previousCharValue) {
                    return false;
                }
            }
        }
    }

    return true;
}

/**
   Prompts the user for a Roman number and validates the input.
   @return the validated Roman number in uppercase form
*/
string getRomanNumber() {
    while (true) {
        string userInput;
        bool isValid = true;

        cout << "Enter a Roman number for decimal conversion: ";
        getline(cin, userInput);

        // check eof and stream state
        if (!cin) {
            recoverStream();
        }

        // check empty input
        if (userInput.length() == 0) {
            cout << "Input cannot be empty, please try again.\n";
            continue;
        }

        // convert all letters to uppercase
        for (int i = 0; i < userInput.length(); i++) {
            userInput[i] = toupper(userInput[i]);
        }

        // make sure every character is a Roman number letter
        for (int i = 0; i < userInput.length(); i++) {
            if (!isRomanChar(userInput[i])) {
                isValid = false;
                break;
            }
        }

        if (!isValid) {
            cout << "Enter valid Roman number letters only. Please try again.\n";
            continue;
        }

        if (userInput.length() > 1 && !isValidRomanNumber(userInput)) {
            cout << "Enter a valid Roman number. Please try again.\n";
            continue;
        }

        return userInput;
    }
}

/**
   Converts a Roman number string to its decimal equivalent.
   @param roman the Roman number to convert
   @return the decimal value of the Roman number
*/
int romanToDecimal(const string& roman) {
    int value = 0;

    for (int i = 0; i < roman.length(); i++) {
        // subtract if the current and next character form a valid subtractive pair
        if (i + 1 < roman.length() && isValidRomanPair(roman[i], roman[i + 1])) {
            value -= getRomanCharValue(roman[i]);
        }
        else {
            value += getRomanCharValue(roman[i]);
        }
    }

    return value;
}
