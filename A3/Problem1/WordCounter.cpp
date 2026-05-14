#include "WordCounter.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// function prototypes
bool isDelimiter(char value);
bool isBlankLine(const char line[]);
char toLowerCase(char value);
int compareCStrings(const char first[], const char second[]);
int compareWordsForQsort(const void* first, const void* second);
void copyWordLowercase(char destination[], const char source[], int length);
bool storeWord(char words[][MAX_WORD_STORAGE], int& wordCount, const char source[], int length);
bool tokenizeLine(char line[], char words[][MAX_WORD_STORAGE], int& wordCount);
void printWordCountTable(char words[][MAX_WORD_STORAGE], int wordCount);

/**
   Checks whether a character should separate words.

   @param value the character to check
   @return true if the character is a delimiter, false otherwise
*/
bool isDelimiter(char value)
{
    return value == ' ' || value == '\t';
}

/**
   Checks whether a C-string line is empty or contains only spaces and tabs.

   @param line the line to check
   @return true if the line is blank, false otherwise
*/
bool isBlankLine(const char line[])
{
    int index = 0;

    while (line[index] != '\0')
    {
        if (!isDelimiter(line[index]))
        {
            return false;
        }

        index++;
    }

    return true;
}

/**
   Converts an uppercase alphabetic character to lowercase.

   @param value the character to convert
   @return the lowercase version of the character when applicable
*/
char toLowerCase(char value)
{
    if (value >= 'A' && value <= 'Z')
    {
        return static_cast<char>(value + ('a' - 'A'));
    }

    return value;
}

/**
   Compares two C-strings alphabetically.

   @param first the first C-string
   @param second the second C-string
   @return negative if first comes first, 0 if equal, positive if second comes first
*/
int compareCStrings(const char first[], const char second[])
{
    int index = 0;

    while (first[index] != '\0' && second[index] != '\0')
    {
        if (first[index] < second[index])
        {
            return -1;
        }

        if (first[index] > second[index])
        {
            return 1;
        }

        index++;
    }

    if (first[index] == '\0' && second[index] == '\0')
    {
        return 0;
    }

    if (first[index] == '\0')
    {
        return -1;
    }

    return 1;
}

/**
   Comparison function used by qsort to sort C-strings.

   @param first pointer to the first array element
   @param second pointer to the second array element
   @return negative, zero, or positive according to alphabetical order
*/
int compareWordsForQsort(const void* first, const void* second)
{
    const char* firstWord = static_cast<const char*>(first);
    const char* secondWord = static_cast<const char*>(second);

    return compareCStrings(firstWord, secondWord);
}

/**
   Copies a word into a destination C-string while converting it to lowercase.

   @param destination the C-string receiving the word
   @param source the source characters
   @param length the number of characters to copy
*/
void copyWordLowercase(char destination[], const char source[], int length)
{
    int index = 0;

    while (index < length)
    {
        destination[index] = toLowerCase(source[index]);
        index++;
    }

    destination[index] = '\0';
}

/**
   Stores one word into the word array if there is enough room.

   @param words the two-dimensional C-string array of words
   @param wordCount the current number of stored words
   @param source the source characters of the word
   @param length the length of the word
   @return true if the word was stored, false otherwise
*/
bool storeWord(char words[][MAX_WORD_STORAGE], int& wordCount, const char source[], int length)
{
    if (length <= 0 || length > MAX_WORD_LENGTH || wordCount >= MAX_WORDS)
    {
        return false;
    }

    copyWordLowercase(words[wordCount], source, length);
    wordCount++;

    return true;
}

/**
   Breaks a line into words and stores them in lowercase.

   @param line the input line to tokenize
   @param words the two-dimensional C-string array of words
   @param wordCount the current number of stored words
   @return true if all words were stored, false otherwise
*/
bool tokenizeLine(char line[], char words[][MAX_WORD_STORAGE], int& wordCount)
{
    int index = 0;

    while (line[index] != '\0')
    {
        while (isDelimiter(line[index]))
        {
            index++;
        }

        if (line[index] == '\0')
        {
            return true;
        }

        int start = index;
        int length = 0;

        while (line[index] != '\0' && !isDelimiter(line[index]))
        {
            index++;
            length++;
        }

        if (!storeWord(words, wordCount, &line[start], length))
        {
            return false;
        }
    }

    return true;
}

void printProgramInfo()
{
    cout << "Alphabetical Word Count Program\n\n";
    cout << "This program reads lines of text from a text file as C-strings.\n";
    cout << "It ignores empty lines, converts words to lowercase, sorts the words,\n";
    cout << "and prints each different word with the number of times it occurred.\n\n";
    cout << "Assumptions and limits:\n";
    cout << "- No punctuation marks are expected in the input file.\n";
    cout << "- Exactly one space separates any two words in the input file.\n";
    cout << "- Maximum line length: " << MAX_LINE_LENGTH << " characters.\n";
    cout << "- Maximum non-empty input lines: " << MAX_INPUT_LINES << ".\n";
    cout << "- Maximum word length: " << MAX_WORD_LENGTH << " characters.\n\n";
}

bool readWordsFromFile(const char fileName[], char words[][MAX_WORD_STORAGE], int& wordCount,
                       int& lineCount)
{
    ifstream inputFile;
    inputFile.open(fileName);

    if (!inputFile)
    {
        return false;
    }

    wordCount = 0;
    lineCount = 0;

    char line[MAX_LINE_LENGTH + 1] = {};

    while (inputFile.getline(line, MAX_LINE_LENGTH + 1))
    {
        if (!isBlankLine(line))
        {
            if (lineCount >= MAX_INPUT_LINES)
            {
                inputFile.close();
                return false;
            }

            lineCount++;

            if (!tokenizeLine(line, words, wordCount))
            {
                inputFile.close();
                return false;
            }
        }
    }

    if (!inputFile.eof())
    {
        inputFile.close();
        return false;
    }

    inputFile.close();
    return true;
}

void sortWords(char words[][MAX_WORD_STORAGE], int wordCount)
{
    qsort(words, wordCount, MAX_WORD_STORAGE, compareWordsForQsort);
}

/**
   Prints the alphabetical word-count table.

   @param words the sorted two-dimensional C-string array of words
   @param wordCount the number of stored words
*/
void printWordCountTable(char words[][MAX_WORD_STORAGE], int wordCount)
{
    if (wordCount == 0)
    {
        cout << "No words were found in the input file.\n";
        return;
    }

    cout << left << setw(WORD_COLUMN_WIDTH) << "Word" << right << setw(COUNT_COLUMN_WIDTH)
         << "Count" << '\n';
    cout << left << setw(WORD_COLUMN_WIDTH) << "----" << right << setw(COUNT_COLUMN_WIDTH)
         << "-----" << '\n';

    int index = 0;

    while (index < wordCount)
    {
        int count = 1;

        while (index + count < wordCount &&
               compareCStrings(words[index], words[index + count]) == 0)
        {
            count++;
        }

        cout << left << setw(WORD_COLUMN_WIDTH) << words[index] << right << setw(COUNT_COLUMN_WIDTH)
             << count << '\n';

        index += count;
    }
}

void printReport(char words[][MAX_WORD_STORAGE], int wordCount, int lineCount)
{
    cout << "Alphabetical Word Count Report\n";
    cout << "==============================\n\n";
    cout << "Non-empty lines processed: " << lineCount << '\n';
    cout << "Total words processed:     " << wordCount << "\n\n";

    printWordCountTable(words, wordCount);
}
