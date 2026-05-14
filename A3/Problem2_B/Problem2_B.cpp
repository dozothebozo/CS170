// File Name: Problem2_B.cpp
// Project: CS 170 Assignment 3 Problem 2B
// Author: Gogi Benny
// Date: Monday, May 11, 2026
//
// Purpose: Maintain a hardware store inventory using a binary random-access file.
//
// Major Items:
// - Binary random-access file hardware.dat with 100 fixed-size Tool records
// - Menu option to initialize hardware.dat with empty records
// - Menu option to populate hardware.dat from a text file
// - Menu option to export the contents of hardware.dat to a text file
// - Menu option to add, list, delete, and update tool records
// - Tool records stored in positions determined by their tool number
// - Input and output through overloaded Tool operators << and >>
// - Confirmation prompts before destructive actions (EXTRA)
// - Inventory value report showing total value of all listed tools (EXTRA)
// - Version control using Git & GitHub:
//   https://github.com/dozothebozo/CS170/blob/main/A3/Problem2_B (EXTRA)

#include "Tool.h"
#include <cstdlib>
#include <fstream>
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
bool getBoolean(const string& prompt);
void getToolName(const string& prompt, char toolName[]);
string getFileName(const string& prompt);

void printProgramInfo();
void printMenu();
void printToolHeader(ostream& out);
void printToolTableRow(ostream& out, const Tool& tool);
Tool getToolFromKeyboard();

streamoff getRecordPosition(int toolNumber);
bool readToolAtRecord(int toolNumber, Tool& tool);
bool writeToolAtRecord(const Tool& tool);
bool writeEmptyRecordAt(int toolNumber);

void initializeHardwareFile();
void populateHardwareFileFromText();
void exportHardwareFileToText();
void addToolsFromKeyboard();
void listAllTools();
void deleteToolRecord();
void updateToolRecord();
void printInventoryValueReport();

// global declarations of constants
const int IGNORE_SIZE = 1000;
const int TOOL_NAME_INPUT_SIZE = MAX_TOOL_NAME_LENGTH + 2;
const int RECORD_COUNT = 100;
const char HARDWARE_FILE_NAME[] = "hardware.dat";

int main()
{
    printProgramInfo();

    int choice = 0;

    do
    {
        printMenu();
        choice = getIntegerInRange("Enter menu choice: ", 1, 9);
        cout << '\n';

        if (choice == 1)
        {
            initializeHardwareFile();
        }
        else if (choice == 2)
        {
            populateHardwareFileFromText();
        }
        else if (choice == 3)
        {
            exportHardwareFileToText();
        }
        else if (choice == 4)
        {
            addToolsFromKeyboard();
        }
        else if (choice == 5)
        {
            listAllTools();
        }
        else if (choice == 6)
        {
            deleteToolRecord();
        }
        else if (choice == 7)
        {
            updateToolRecord();
        }

        else if (choice == 8)
        {
            printInventoryValueReport();
        }

        if (choice != 9)
        {
            cout << '\n';
        }

    } while (choice != 9);

    cout << "Program finished.\n";
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
        int value = 0;

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
        double value = 0.0;

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
   Prompts the user for a yes or no response.

   @param prompt the message displayed to the user
   @return true for y or Y, false for n or N
*/
bool getBoolean(const string& prompt)
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
   Prompts the user for a nonblank file name.

   @param prompt the message displayed to the user
   @return the validated file name
*/
string getFileName(const string& prompt)
{
    while (true)
    {
        string fileName;

        cout << prompt;
        getline(cin, fileName);

        if (fileName.length() == 0)
        {
            cout << "Invalid input. File name cannot be blank.\n";
            continue;
        }

        return fileName;
    }
}

/**
   Displays the program purpose and important file information.
*/
void printProgramInfo()
{
    cout << "Hardware Store Inventory Manager\n\n";
    cout << "This program maintains the binary random-access file " << HARDWARE_FILE_NAME << ".\n";
    cout << "The file stores " << RECORD_COUNT << " fixed-size Tool records.\n";
    cout << "Valid tool numbers are " << MIN_TOOL_NUMBER << " through " << MAX_TOOL_NUMBER << ".\n";
    cout << "Tool number " << EMPTY_TOOL_NUMBER << " is reserved for empty records.\n\n";
}

/**
   Displays the main menu.
*/
void printMenu()
{
    cout << "Hardware Store Menu\n";
    cout << "1. Initialize " << HARDWARE_FILE_NAME << " to empty records\n";
    cout << "2. Populate " << HARDWARE_FILE_NAME << " from a text file\n";
    cout << "3. Export " << HARDWARE_FILE_NAME << " to a text file\n";
    cout << "4. Add tool records from the keyboard\n";
    cout << "5. List all tools\n";
    cout << "6. Delete a tool record\n";
    cout << "7. Update a tool record\n";
    cout << "8. Print inventory value report\n";
    cout << "9. Quit\n";
}

/**
   Prints the heading for a formatted tool table.

   @param out the output stream receiving the heading
*/
void printToolHeader(ostream& out)
{
    out << right << setw(TOOL_NUMBER_WIDTH) << "Tool #" << "  " << left << setw(TOOL_NAME_WIDTH)
        << "Tool name" << right << setw(TOOL_QUANTITY_WIDTH) << "Quantity" << setw(TOOL_COST_WIDTH)
        << "Cost" << '\n';

    out << right << setw(TOOL_NUMBER_WIDTH) << "------" << "  " << left << setw(TOOL_NAME_WIDTH)
        << "---------" << right << setw(TOOL_QUANTITY_WIDTH) << "--------" << setw(TOOL_COST_WIDTH)
        << "----" << '\n';
}

/**
   Prints one non-empty Tool in a table row.

   @param out the output stream receiving the row
   @param tool the Tool object to print
*/
void printToolTableRow(ostream& out, const Tool& tool)
{
    if (!tool.isEmpty())
    {
        out << tool << '\n';
    }
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

    char toolName[TOOL_NAME_INPUT_SIZE] = "";

    getToolName("Enter tool name, up to " + to_string(MAX_TOOL_NAME_LENGTH) + " characters: ",
                toolName);

    int quantity = getIntegerInRange("Enter quantity (" + to_string(MIN_TOOL_QUANTITY) + "-" +
                                         to_string(MAX_TOOL_QUANTITY) + "): ",
                                     MIN_TOOL_QUANTITY, MAX_TOOL_QUANTITY);

    double cost = getDoubleInRange("Enter cost per unit: ", MIN_TOOL_COST, MAX_TOOL_COST);

    return Tool(toolNumber, toolName, quantity, cost);
}

/**
   Calculates the byte position of a tool record in hardware.dat.

   @param toolNumber the tool number used to locate the record
   @return the byte position of the record
*/
streamoff getRecordPosition(int toolNumber)
{
    return static_cast<streamoff>(toolNumber - MIN_TOOL_NUMBER) *
           static_cast<streamoff>(sizeof(Tool));
}

/**
   Reads one Tool record from hardware.dat.

   @param toolNumber the tool number to locate
   @param tool the Tool object receiving the record data
   @return true if the record was read, false otherwise
*/
bool readToolAtRecord(int toolNumber, Tool& tool)
{
    ifstream file(HARDWARE_FILE_NAME, ios::binary);

    if (!file)
    {
        cout << "Unable to open " << HARDWARE_FILE_NAME
             << ". Please initialize the file before using this option.\n";
        return false;
    }

    file.seekg(getRecordPosition(toolNumber));
    file.read(reinterpret_cast<char*>(&tool), sizeof(Tool));

    return file.good();
}

/**
   Writes one Tool record to hardware.dat.

   @param tool the Tool object to write
   @return true if the record was written, false otherwise
*/
bool writeToolAtRecord(const Tool& tool)
{
    fstream file(HARDWARE_FILE_NAME, ios::in | ios::out | ios::binary);

    if (!file)
    {
        cout << "Unable to open " << HARDWARE_FILE_NAME
             << ". Please initialize the file before using this option.\n";
        return false;
    }

    file.seekp(getRecordPosition(tool.getToolNumber()));
    file.write(reinterpret_cast<const char*>(&tool), sizeof(Tool));

    return file.good();
}

/**
   Writes an empty record to a selected tool position in hardware.dat.

   @param toolNumber the tool number position to clear
   @return true if the empty record was written, false otherwise
*/
bool writeEmptyRecordAt(int toolNumber)
{
    Tool emptyTool;
    fstream file(HARDWARE_FILE_NAME, ios::in | ios::out | ios::binary);

    if (!file)
    {
        cout << "Unable to open " << HARDWARE_FILE_NAME
             << ". Please initialize the file before using this option.\n";
        return false;
    }

    file.seekp(getRecordPosition(toolNumber));
    file.write(reinterpret_cast<const char*>(&emptyTool), sizeof(Tool));

    return file.good();
}

/**
   Initializes hardware.dat with 100 empty Tool records.
*/
void initializeHardwareFile()
{
    cout << "This will overwrite " << HARDWARE_FILE_NAME << " with " << RECORD_COUNT
         << " empty records.\n";

    if (!getBoolean("Continue? (y/n): "))
    {
        cout << "Initialization canceled.\n";
        return;
    }

    ofstream file(HARDWARE_FILE_NAME, ios::binary);

    if (!file)
    {
        cout << "Unable to create " << HARDWARE_FILE_NAME << ".\n";
        return;
    }

    Tool emptyTool;

    for (int count = 0; count < RECORD_COUNT; count++)
    {
        file.write(reinterpret_cast<const char*>(&emptyTool), sizeof(Tool));
    }

    if (!file)
    {
        cout << "An error occurred while initializing the file.\n";
    }
    else
    {
        cout << HARDWARE_FILE_NAME << " initialized successfully.\n";
    }
}

/**
   Populates hardware.dat by reading Tool records from a text file.
*/
void populateHardwareFileFromText()
{
    string fileName = getFileName("Enter input text file name (e.g. hardware_import.txt): ");
    ifstream inputFile(fileName.c_str());

    if (!inputFile)
    {
        cout << "Unable to open " << fileName << ".\n";
        return;
    }

    int importedCount = 0;
    Tool tool;

    while (inputFile >> tool)
    {
        if (writeToolAtRecord(tool))
        {
            importedCount++;
        }
    }

    if (!inputFile.eof())
    {
        cout << "Import stopped because invalid data was found in the text file.\n";
    }

    cout << importedCount << " record(s) imported into " << HARDWARE_FILE_NAME << ".\n";
}

/**
   Exports all non-empty hardware.dat records to a text report file.
*/
void exportHardwareFileToText()
{
    string fileName = getFileName("Enter output text file name (e.g. test.txt): ");
    ifstream inputFile(HARDWARE_FILE_NAME, ios::binary);

    if (!inputFile)
    {
        cout << "Unable to open " << HARDWARE_FILE_NAME
             << ". Please initialize the file before using this option.\n";
        return;
    }

    ofstream outputFile(fileName.c_str());

    if (!outputFile)
    {
        cout << "Unable to create " << fileName << ".\n";
        return;
    }

    outputFile << "Hardware Store Inventory Report\n\n";
    printToolHeader(outputFile);

    int exportedCount = 0;
    Tool tool;

    for (int record = 0; record < RECORD_COUNT; record++)
    {
        inputFile.read(reinterpret_cast<char*>(&tool), sizeof(Tool));

        if (inputFile && !tool.isEmpty())
        {
            printToolTableRow(outputFile, tool);
            exportedCount++;
        }
    }

    outputFile << "\nRecords exported: " << exportedCount << '\n';

    cout << exportedCount << " record(s) exported to " << fileName << ".\n";
}

/**
   Adds one or more Tool records from keyboard input.
*/
void addToolsFromKeyboard()
{
    bool addAnother = true;

    while (addAnother)
    {
        Tool newTool = getToolFromKeyboard();
        Tool existingTool;

        if (!readToolAtRecord(newTool.getToolNumber(), existingTool))
        {
            return;
        }

        if (!existingTool.isEmpty())
        {
            cout << "A record already exists for tool number " << newTool.getToolNumber() << ".\n";
            printToolHeader(cout);
            printToolTableRow(cout, existingTool);

            if (!getBoolean("Replace this record? (y/n): "))
            {
                cout << "Record was not changed.\n";
            }
            else if (writeToolAtRecord(newTool))
            {
                cout << "Record replaced.\n";
            }
        }
        else if (writeToolAtRecord(newTool))
        {
            cout << "Record added.\n";
        }

        addAnother = getBoolean("Add another tool? (y/n): ");
    }
}

/**
   Lists all non-empty Tool records in hardware.dat.
*/
void listAllTools()
{
    ifstream file(HARDWARE_FILE_NAME, ios::binary);

    if (!file)
    {
        cout << "Unable to open " << HARDWARE_FILE_NAME
             << ". Please initialize the file before using this option.\n";
        return;
    }

    int listedCount = 0;
    Tool tool;

    cout << "Hardware Store Inventory\n\n";
    printToolHeader(cout);

    for (int record = 0; record < RECORD_COUNT; record++)
    {
        file.read(reinterpret_cast<char*>(&tool), sizeof(Tool));

        if (file && !tool.isEmpty())
        {
            printToolTableRow(cout, tool);
            listedCount++;
        }
    }

    if (listedCount == 0)
    {
        cout << "No tool records found.\n";
    }

    cout << "\nRecords listed: " << listedCount << '\n';
}

/**
   Deletes a selected Tool record by writing an empty record in its place.
*/
void deleteToolRecord()
{
    int toolNumber =
        getIntegerInRange("Enter tool number to delete: ", MIN_TOOL_NUMBER, MAX_TOOL_NUMBER);
    Tool existingTool;

    if (!readToolAtRecord(toolNumber, existingTool))
    {
        return;
    }

    if (existingTool.isEmpty())
    {
        cout << "There is no record for tool number " << toolNumber << ".\n";
        return;
    }

    cout << "Record selected for deletion:\n";
    printToolHeader(cout);
    printToolTableRow(cout, existingTool);

    if (!getBoolean("Delete this record? (y/n): "))
    {
        cout << "Deletion canceled.\n";
        return;
    }

    if (writeEmptyRecordAt(toolNumber))
    {
        cout << "Record deleted.\n";
    }
}

/**
   Updates a selected Tool record.
*/
void updateToolRecord()
{
    int toolNumber =
        getIntegerInRange("Enter tool number to update: ", MIN_TOOL_NUMBER, MAX_TOOL_NUMBER);
    Tool tool;

    if (!readToolAtRecord(toolNumber, tool))
    {
        return;
    }

    if (tool.isEmpty())
    {
        cout << "There is no record for tool number " << toolNumber << ".\n";
        return;
    }

    cout << "Current record:\n";
    printToolHeader(cout);
    printToolTableRow(cout, tool);

    cout << "\nUpdate Options\n";
    cout << "1. Tool name\n";
    cout << "2. Quantity\n";
    cout << "3. Cost\n";
    cout << "4. Tool number\n";
    cout << "5. Cancel update\n";

    int choice = getIntegerInRange("Enter update choice: ", 1, 5);

    if (choice == 1)
    {
        char toolName[TOOL_NAME_INPUT_SIZE] = "";
        getToolName("Enter new tool name: ", toolName);
        tool.setToolName(toolName);
    }
    else if (choice == 2)
    {
        int quantity =
            getIntegerInRange("Enter new quantity: ", MIN_TOOL_QUANTITY, MAX_TOOL_QUANTITY);
        tool.setQuantity(quantity);
    }
    else if (choice == 3)
    {
        double cost = getDoubleInRange("Enter new cost per unit: ", MIN_TOOL_COST, MAX_TOOL_COST);
        tool.setCost(cost);
    }
    else if (choice == 4)
    {
        int newToolNumber =
            getIntegerInRange("Enter new tool number: ", MIN_TOOL_NUMBER, MAX_TOOL_NUMBER);

        if (newToolNumber == toolNumber)
        {
            cout << "The tool number was not changed.\n";
            return;
        }

        Tool destinationTool;

        if (!readToolAtRecord(newToolNumber, destinationTool))
        {
            return;
        }

        if (!destinationTool.isEmpty())
        {
            cout << "A record already exists at tool number " << newToolNumber << ".\n";
            printToolHeader(cout);
            printToolTableRow(cout, destinationTool);

            if (!getBoolean("Replace the destination record? (y/n): "))
            {
                cout << "Tool number update canceled.\n";
                return;
            }
        }

        tool.setToolNumber(newToolNumber);

        if (writeToolAtRecord(tool))
        {
            writeEmptyRecordAt(toolNumber);
            cout << "Tool number changed.\n";
        }

        return;
    }
    else
    {
        cout << "Update canceled.\n";
        return;
    }

    if (writeToolAtRecord(tool))
    {
        cout << "Record updated.\n";
    }
}

/**
   Prints the total inventory value from all non-empty records.
*/
void printInventoryValueReport()
{
    ifstream file(HARDWARE_FILE_NAME, ios::binary);

    if (!file)
    {
        cout << "Unable to open " << HARDWARE_FILE_NAME
             << ". Please initialize the file before using this option.\n";
        return;
    }

    int recordCount = 0;
    double totalValue = 0.0;
    Tool tool;

    for (int record = 0; record < RECORD_COUNT; record++)
    {
        file.read(reinterpret_cast<char*>(&tool), sizeof(Tool));

        if (file && !tool.isEmpty())
        {
            recordCount++;
            totalValue = totalValue + tool.getInventoryValue();
        }
    }

    cout << "Inventory value report\n";
    cout << "Non-empty records: " << recordCount << '\n';
    cout << "Total inventory value: $" << fixed << setprecision(2) << totalValue << '\n';
}
