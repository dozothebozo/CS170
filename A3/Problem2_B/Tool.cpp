#include "Tool.h"
#include <iomanip>

using namespace std;

// Helper function prototypes
bool isBlankCString(const char value[]);
bool isValidToolNumberValue(int toolNumber);
bool isValidToolNameValue(const char toolName[]);
bool isValidToolQuantityValue(int quantity);
bool isValidToolCostValue(double cost);
int getCStringLength(const char value[]);
void copyCString(char destination[], const char source[], int maxLength);

// global declarations of constants
const int STREAM_IGNORE_SIZE = 1000;

/**
   Checks whether a C-string contains only spaces or tabs.

   @param value the C-string to check
   @return true if the C-string is blank, false otherwise
*/
bool isBlankCString(const char value[])
{
    int index = 0;

    while (value[index] != '\0')
    {
        if (value[index] != ' ' && value[index] != '\t')
        {
            return false;
        }

        index++;
    }

    return true;
}

/**
   Checks whether a tool number is in the valid range.

   @param toolNumber the tool number to check
   @return true if the tool number is valid, false otherwise
*/
bool isValidToolNumberValue(int toolNumber)
{
    return toolNumber >= MIN_TOOL_NUMBER && toolNumber <= MAX_TOOL_NUMBER;
}

/**
   Checks whether a tool name is valid.

   @param toolName the tool name to check
   @return true if the tool name is valid, false otherwise
*/
bool isValidToolNameValue(const char toolName[])
{
    return toolName != nullptr && toolName[0] != '\0' && !isBlankCString(toolName) &&
           getCStringLength(toolName) <= MAX_TOOL_NAME_LENGTH;
}

/**
   Checks whether a quantity is in the valid range.

   @param quantity the quantity to check
   @return true if the quantity is valid, false otherwise
*/
bool isValidToolQuantityValue(int quantity)
{
    return quantity >= MIN_TOOL_QUANTITY && quantity <= MAX_TOOL_QUANTITY;
}

/**
   Checks whether a cost is in the valid range.

   @param cost the cost to check
   @return true if the cost is valid, false otherwise
*/
bool isValidToolCostValue(double cost)
{
    return cost >= MIN_TOOL_COST && cost <= MAX_TOOL_COST;
}

/**
   Gets the number of characters in a C-string.

   @param value the C-string to measure
   @return the number of characters before the null terminator
*/
int getCStringLength(const char value[])
{
    int length = 0;

    while (value[length] != '\0')
    {
        length++;
    }

    return length;
}

/**
   Copies one C-string into another C-string with a maximum length.
   This function always null-terminates the destination and avoids strncpy.

   @param destination the C-string receiving the copied text
   @param source the C-string being copied
   @param maxLength the maximum number of characters to copy
*/
void copyCString(char destination[], const char source[], int maxLength)
{
    int index = 0;

    if (destination == nullptr)
    {
        return;
    }

    if (source == nullptr || maxLength < 0)
    {
        destination[0] = '\0';
        return;
    }

    while (index < maxLength && source[index] != '\0')
    {
        destination[index] = source[index];
        index++;
    }

    destination[index] = '\0';
}

Tool::Tool() : m_toolNumber(EMPTY_TOOL_NUMBER), m_toolName{}, m_quantity(0), m_cost(0.0)
{
}

Tool::Tool(int toolNumber, const char toolName[], int quantity, double cost)
    : m_toolNumber(EMPTY_TOOL_NUMBER)
    , m_toolName{} // '\0'
    , m_quantity(0)
    , m_cost(0.0)
{
    if (isValidToolNumberValue(toolNumber) && isValidToolNameValue(toolName) &&
        isValidToolQuantityValue(quantity) && isValidToolCostValue(cost))
    {
        m_toolNumber = toolNumber;
        copyCString(m_toolName, toolName, MAX_TOOL_NAME_LENGTH);
        m_quantity = quantity;
        m_cost = cost;
    }
}

void Tool::setEmpty()
{
    m_toolNumber = EMPTY_TOOL_NUMBER;
    m_toolName[0] = '\0';
    m_quantity = 0;
    m_cost = 0.0;
}

bool Tool::setToolNumber(int toolNumber)
{
    if (!isValidToolNumberValue(toolNumber))
    {
        return false;
    }

    m_toolNumber = toolNumber;
    return true;
}

bool Tool::setToolName(const char toolName[])
{
    if (!isValidToolNameValue(toolName))
    {
        return false;
    }

    copyCString(m_toolName, toolName, MAX_TOOL_NAME_LENGTH);
    return true;
}

bool Tool::setQuantity(int quantity)
{
    if (!isValidToolQuantityValue(quantity))
    {
        return false;
    }

    m_quantity = quantity;
    return true;
}

bool Tool::setCost(double cost)
{
    if (!isValidToolCostValue(cost))
    {
        return false;
    }

    m_cost = cost;
    return true;
}

int Tool::getToolNumber() const
{
    return m_toolNumber;
}

const char* Tool::getToolName() const
{
    return m_toolName;
}

int Tool::getQuantity() const
{
    return m_quantity;
}

double Tool::getCost() const
{
    return m_cost;
}

double Tool::getInventoryValue() const
{
    return m_quantity * m_cost;
}

bool Tool::isEmpty() const
{
    return m_toolNumber == EMPTY_TOOL_NUMBER;
}

ostream& operator<<(ostream& out, const Tool& tool)
{
    if (tool.isEmpty())
    {
        out << right << setw(TOOL_NUMBER_WIDTH) << EMPTY_TOOL_NUMBER << "  " << left
            << setw(TOOL_NAME_WIDTH) << "(empty record)" << right << setw(TOOL_QUANTITY_WIDTH) << 0
            << setw(TOOL_COST_WIDTH) << fixed << setprecision(2) << 0.0;
    }
    else
    {
        out << right << setw(TOOL_NUMBER_WIDTH) << tool.m_toolNumber << "  " << left
            << setw(TOOL_NAME_WIDTH) << tool.m_toolName << right << setw(TOOL_QUANTITY_WIDTH)
            << tool.m_quantity << setw(TOOL_COST_WIDTH) << fixed << setprecision(2) << tool.m_cost;
    }

    return out;
}

istream& operator>>(istream& in, Tool& tool)
{
    int toolNumber{};
    char toolName[MAX_TOOL_NAME_LENGTH + 2]{};
    int quantity{};
    double cost{};

    if (!(in >> toolNumber))
    {
        return in;
    }

    in.ignore(STREAM_IGNORE_SIZE, '\n');

    if (!in.getline(toolName, MAX_TOOL_NAME_LENGTH + 2))
    {
        return in;
    }

    if (!(in >> quantity))
    {
        return in;
    }

    if (!(in >> cost))
    {
        return in;
    }

    in.ignore(STREAM_IGNORE_SIZE, '\n');

    if (toolNumber == EMPTY_TOOL_NUMBER && toolName[0] == '\0' && quantity == 0 && cost == 0.0)
    {
        tool.setEmpty();
        return in;
    }

    Tool temporaryTool(toolNumber, toolName, quantity, cost);

    if (temporaryTool.isEmpty())
    {
        in.setstate(ios::failbit);
    }
    else
    {
        tool = temporaryTool;
    }

    return in;
}
