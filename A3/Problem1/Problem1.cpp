// File Name: Problem1.cpp
// Project: CS 170 Assignment 3 Problem 1
// Author: Gogi Benny
// Date: Wednesday, May 13, 2026
//
// Purpose: Read words from a text file as C-strings and print an alphabetical
// word-count report without regard for character case.
//
// Major Items:
// - Text file input using C++ file streams
// - C-string processing using character arrays
// - Two-dimensional C-string array for storing words
// - qsort library function used to alphabetize the words
// - Case-insensitive counting by converting words to lowercase
// - User-selected input file name (EXTRA)
// - Rerun option to process multiple files in one run (EXTRA)
// - Version control using Git & GitHub:
//   https://github.com/dozothebozo/CS170/blob/main/A3/Problem1 (EXTRA)

#include "WordCounter.h"

#include <cstdlib>
#include <iostream>

using namespace std;

const int IGNORE_SIZE = 1000;

void ignoreLine();
bool recoverStream();
bool restOfLineIsBlank();
bool getBoolean(const char prompt[]);
void getInputFileName(char fileName[]);
void processOneFile();

int main()
{
    printProgramInfo();

    do
    {
        processOneFile();

    } while (getBoolean("\nWould you like to process another file? (y/n): "));

    cout << "\nProgram finished.\n";
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
   Recovers the input stream after a failed input operation.

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
   Checks whether the rest of the current input line is blank.

   @return true if the rest of the line is blank, false otherwise
*/
bool restOfLineIsBlank()
{
    char value = '\0';

    while (cin.get(value))
    {
        if (value == '\n')
        {
            return true;
        }

        if (value != ' ' && value != '\t')
        {
            ignoreLine();
            return false;
        }
    }

    if (cin.eof())
    {
        exit(1);
    }

    return true;
}

/**
   Prompts the user for a yes or no answer.

   @param prompt the prompt displayed to the user
   @return true for y or Y, false for n or N
*/
bool getBoolean(const char prompt[])
{
    while (true)
    {
        char value = '\0';

        cout << prompt;
        cin >> value;

        if (recoverStream())
        {
            cout << "Invalid input. Please enter y or n.\n";
            continue;
        }

        if (!restOfLineIsBlank())
        {
            cout << "Invalid input. Please enter only y or n.\n";
            continue;
        }

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
   Prompts the user for the input file name.

   @param fileName the C-string where the entered file name is stored
*/
void getInputFileName(char fileName[])
{
    while (true)
    {
        cout << "Enter the input text file name: ";
        cin.getline(fileName, FILE_NAME_SIZE);

        if (!cin)
        {
            if (cin.eof())
            {
                exit(1);
            }

            cin.clear();
            ignoreLine();
            cout << "File name is too long. Please enter a shorter file name.\n";
            continue;
        }

        if (fileName[0] == '\0')
        {
            cout << "File name cannot be blank.\n";
            continue;
        }

        return;
    }
}

/**
   Processes one input file by reading, sorting, counting, and displaying the
   word-count report.
*/
void processOneFile()
{
    char words[MAX_WORDS][MAX_WORD_STORAGE] = {};
    int wordCount = 0;
    int lineCount = 0;
    char inputFileName[FILE_NAME_SIZE] = {};

    getInputFileName(inputFileName);

    if (!readWordsFromFile(inputFileName, words, wordCount, lineCount))
    {
        cout << "\nThe file could not be processed.\n";
        cout
            << "Please check that the file exists and that it does not exceed the stated limits.\n";
        return;
    }

    sortWords(words, wordCount);

    cout << '\n';
    printReport(words, wordCount, lineCount);
}
