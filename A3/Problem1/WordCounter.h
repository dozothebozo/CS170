#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

const int MAX_LINE_LENGTH = 200;
const int MAX_INPUT_LINES = 50;
const int MAX_WORD_LENGTH = 50;
const int MAX_WORD_STORAGE = MAX_WORD_LENGTH + 1;
const int MAX_WORDS_PER_LINE = (MAX_LINE_LENGTH + 1) / 2;
const int MAX_WORDS = MAX_INPUT_LINES * MAX_WORDS_PER_LINE;

const int FILE_NAME_SIZE = 100;
const int WORD_COLUMN_WIDTH = 25;
const int COUNT_COLUMN_WIDTH = 8;

/**
   Prints the program description and the assumptions used by the program.
*/
void printProgramInfo();

/**
   Reads words from a text file into a two-dimensional C-string array.
   Empty lines are ignored. Words are stored in lowercase.

   @param fileName the name of the input text file
   @param words the two-dimensional C-string array that stores the words
   @param wordCount the number of words stored in the array
   @param lineCount the number of non-empty input lines processed
   @return true if the file was read successfully, false otherwise
*/
bool readWordsFromFile(const char fileName[], char words[][MAX_WORD_STORAGE], int& wordCount,
                       int& lineCount);

/**
   Sorts the stored words alphabetically using qsort.

   @param words the two-dimensional C-string array of words
   @param wordCount the number of stored words
*/
void sortWords(char words[][MAX_WORD_STORAGE], int wordCount);

/**
   Prints the complete alphabetical word-count report.

   @param words the sorted two-dimensional C-string array of words
   @param wordCount the number of stored words
   @param lineCount the number of non-empty input lines processed
*/
void printReport(char words[][MAX_WORD_STORAGE], int wordCount, int lineCount);

#endif
