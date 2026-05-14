// File Name: Problem2_A.cpp
// Project: CS 170 Assignment 3 Problem 2A
// Author: Gogi Benny
// Date: Friday, May 8, 2026
//
// Purpose: Test the Tool class by allowing the user to enter and display hardware
// store tool records.
//
// Major Items:
// - Tool class testing through validated keyboard input
// - Formatted output using the overloaded Tool output operator
// - Input validation for tool number, name, quantity, and cost
// - Informational message explaining valid tool data to the user (EXTRA)
// - Rerun option to enter multiple tool records in one program run (EXTRA)
// - Inventory value calculation for each entered tool record (EXTRA)
// - Version control using Git & GitHub:
//   https://github.com/dozothebozo/CS170/blob/main/A3/Problem2_A (EXTRA)

#include "Tool.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// function prototypes
void ignoreLine();
bool recoverStream();
bool restOfLineIsBlank();

int getIntegerInRange(const string& prompt, int min, int max);
double getDoubleInRange(const string& prompt, double min, double max);
void getToolName(const string& prompt, char toolName[]);
bool getBoolean(const string& prompt);

void printInfo();
void printToolHeader();
Tool getToolFromKeyboard();

// global declarations of constants
const int IGNORE_SIZE = 1000;
const int TOOL_NAME_INPUT_SIZE = MAX_TOOL_NAME_LENGTH + 2;

int main()
{
    printInfo();

    do
    {
        Tool tool = getToolFromKeyboard();

        cout << "\nTool entered:\n";
        printToolHeader();
        cout << tool << '\n';

        cout << "Inventory value for this tool: $" << fixed << setprecision(2)
             << tool.getInventoryValue() << "\n\n";

    } while (getBoolean("Would you like to enter another tool? (y/n): "));

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
   Checks whether the rest of the current input line is blank.

   @return true if the rest of the line is blank, false otherwise
*/
bool restOfLineIsBlank()
{
    char value{};

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
   Prompts the user for an integer in a given inclusive range.

   @param prompt the message displayed to the user
   @param min the minimum valid integer
   @param max the maximum valid integer
   @return the validated integer
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
            cout << "Invalid input. Please enter an integer.\n";
            continue;
        }

        if (!restOfLineIsBlank())
        {
            cout << "Invalid input. Please enter only one integer value.\n";
            continue;
        }

        if (value < min || value > max)
        {
            cout << "Input must be between " << min << " and " << max << ". Please try again.\n";
            continue;
        }

        return value;
    }
}

/**
   Prompts the user for a double value in a given inclusive range.

   @param prompt the message displayed to the user
   @param min the minimum valid value
   @param max the maximum valid value
   @return the validated double value
*/
double getDoubleInRange(const string& prompt, double min, double max)
{
    while (true)
    {
        double value{};

        cout << prompt;
        cin >> value;

        if (recoverStream())
        {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (!restOfLineIsBlank())
        {
            cout << "Invalid input. Please enter only one numeric value.\n";
            continue;
        }

        if (value < min || value > max)
        {
            cout << fixed << setprecision(2);
            cout << "Input must be between " << min << " and " << max << ". Please try again.\n";
            continue;
        }

        return value;
    }
}

/**
   Prompts the user for a valid tool name.

   @param prompt the message displayed to the user
   @param toolName the C-string where the validated tool name is stored
*/
void getToolName(const string& prompt, char toolName[])
{
    while (true)
    {
        cout << prompt;
        cin.getline(toolName, TOOL_NAME_INPUT_SIZE);

        if (!cin)
        {
            if (cin.eof())
            {
                exit(1);
            }

            cin.clear();
            ignoreLine();
            cout << "Invalid input. Tool name may not be more than " << MAX_TOOL_NAME_LENGTH
                 << " characters.\n";
            continue;
        }

        Tool testTool;

        if (!testTool.setToolName(toolName))
        {
            cout << "Invalid input. Tool name cannot be blank and may not be more than "
                 << MAX_TOOL_NAME_LENGTH << " characters.\n";
            continue;
        }

        return;
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
   Displays information explaining the purpose of the program and the valid input
   ranges for tool records.
*/
void printInfo()
{
    cout << "Hardware Store Tool Record Test\n\n";
    cout << "This program tests the Tool class used for the hardware store inventory.\n";
    cout << "Each tool has a tool number, name, quantity, and cost per unit.\n";
    cout << "Tool number " << EMPTY_TOOL_NUMBER
         << " is reserved for empty records, so real tool numbers must be from " << MIN_TOOL_NUMBER
         << " to " << MAX_TOOL_NUMBER << ".\n";
    cout << "Tool names may contain spaces and may be up to " << MAX_TOOL_NAME_LENGTH
         << " characters long.\n";
    cout << "Quantity and cost must be zero or greater.\n\n";
}

/**
   Prints the heading for a formatted tool table.
*/
void printToolHeader()
{
    cout << right << setw(TOOL_NUMBER_WIDTH) << "Tool #" << "  " << left << setw(TOOL_NAME_WIDTH)
         << "Tool name" << right << setw(TOOL_QUANTITY_WIDTH) << "Quantity" << setw(TOOL_COST_WIDTH)
         << "Cost" << '\n';

    cout << right << setw(TOOL_NUMBER_WIDTH) << "------" << "  " << left << setw(TOOL_NAME_WIDTH)
         << "---------" << right << setw(TOOL_QUANTITY_WIDTH) << "--------" << setw(TOOL_COST_WIDTH)
         << "----" << '\n';
}

/**
   Prompts the user for all data needed to create a Tool object.

   @return a Tool object created from validated keyboard input
*/
Tool getToolFromKeyboard()
{
    int toolNumber = getIntegerInRange("Enter tool number (" + to_string(MIN_TOOL_NUMBER) + "-" +
                                           to_string(MAX_TOOL_NUMBER) + "): ",
                                       MIN_TOOL_NUMBER, MAX_TOOL_NUMBER);

    char toolName[TOOL_NAME_INPUT_SIZE]{};

    getToolName("Enter tool name, up to " + to_string(MAX_TOOL_NAME_LENGTH) + " characters: ",
                toolName);

    int quantity = getIntegerInRange("Enter quantity (" + to_string(MIN_TOOL_QUANTITY) + "-" +
                                         to_string(MAX_TOOL_QUANTITY) + "): ",
                                     MIN_TOOL_QUANTITY, MAX_TOOL_QUANTITY);

    double cost = getDoubleInRange("Enter cost per unit: ", MIN_TOOL_COST, MAX_TOOL_COST);

    return Tool(toolNumber, toolName, quantity, cost);
}
