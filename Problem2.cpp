// File Name: Problem2.cpp
// Project: CS 170 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: Wednesday, March 11, 2026
//
// Purpose: Read a Roman numeral from the user, validate the input, and convert
// it to its decimal equivalent.
//
// Major Items:
// - Global constant for stream cleanup size
// - Input validation for EOF/stream failure, empty input, and invalid characters
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
string getRomanNumber();
int getRomanCharValue(char ch);
int romanToDecimal(const string& roman);

// global declarations of constants
const int IGNORE_SIZE = 1000;

int main() {
    string roman = getRomanNumber();
    cout << "Roman numeral " << roman << " is equal to " << romanToDecimal(roman) << '\n';
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
   Determines if a character is a valid Roman numeral letter.
   @param ch the character to check
   @return true if the character is a Roman numeral letter, false otherwise
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
   Prompts the user for a Roman numeral and validates the input.
   @return the validated Roman numeral in uppercase form
*/
string getRomanNumber() {
    while (true) {
        string userInput;
        bool valid = true;

        cout << "Enter a Roman numeral for decimal conversion: ";
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

        // make sure every character is a Roman numeral letter
        for (int i = 0; i < userInput.length(); i++) {
            if (!isRomanChar(userInput[i])) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Enter valid Roman number letters only. Please try again.\n";
            continue;
        }

        // convert all letters to uppercase
        for (int i = 0; i < userInput.length(); i++) {
            userInput[i] = toupper(userInput[i]);
        }
        return userInput;
    }
}

/**
   Gets the decimal value of a single Roman numeral character.
   @param ch the Roman numeral character
   @return the decimal value of the Roman numeral character
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
   Converts a Roman numeral string to its decimal equivalent.
   @param roman the Roman numeral to convert
   @return the decimal value of the Roman numeral
*/
int romanToDecimal(const string& roman) {
    int value = 0;

    for (int i = 0; i < roman.length(); i++) {
        // subtract if a smaller value comes before a larger value
        if (i + 1 < roman.length() &&
            (getRomanCharValue(roman[i]) < getRomanCharValue(roman[i + 1]))) {
            value -= getRomanCharValue(roman[i]);
        }
        else {
            value += getRomanCharValue(roman[i]);
        }
    }

    return value;
}
