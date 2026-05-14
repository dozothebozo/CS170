#ifndef TOOL_H
#define TOOL_H

#include <iostream>

const int EMPTY_TOOL_NUMBER = 0;
const int MIN_TOOL_NUMBER = 1;
const int MAX_TOOL_NUMBER = 100;

const int MAX_TOOL_NAME_LENGTH = 40;

const int MIN_TOOL_QUANTITY = 0;
const int MAX_TOOL_QUANTITY = 100000;

const double MIN_TOOL_COST = 0.0;
const double MAX_TOOL_COST = 100000.0;

const int TOOL_NUMBER_WIDTH = 8;
const int TOOL_NAME_WIDTH = 42;
const int TOOL_QUANTITY_WIDTH = 10;
const int TOOL_COST_WIDTH = 12;

class Tool
{
  public:
    /**
       Constructs an empty tool record.
    */
    Tool();

    /**
       Constructs a tool record with the given field values. If any value is invalid,
       the object is created as an empty record.

       @param toolNumber the tool identification number
       @param toolName the name of the tool
       @param quantity the number of units on hand
       @param cost the cost per unit
    */
    Tool(int toolNumber, const char toolName[], int quantity, double cost);

    /**
       Sets this object to an empty tool record.
    */
    void setEmpty();

    /**
       Sets the tool number if it is valid.

       @param toolNumber the new tool number
       @return true if the tool number was set, false otherwise
    */
    bool setToolNumber(int toolNumber);

    /**
       Sets the tool name if it is valid.

       @param toolName the new tool name
       @return true if the tool name was set, false otherwise
    */
    bool setToolName(const char toolName[]);

    /**
       Sets the quantity if it is valid.

       @param quantity the new quantity
       @return true if the quantity was set, false otherwise
    */
    bool setQuantity(int quantity);

    /**
       Sets the cost if it is valid.

       @param cost the new cost
       @return true if the cost was set, false otherwise
    */
    bool setCost(double cost);

    /**
       Gets the tool number.

       @return the tool number
    */
    int getToolNumber() const;

    /**
       Gets the tool name.

       @return the tool name as a C-string
    */
    const char* getToolName() const;

    /**
       Gets the quantity.

       @return the quantity on hand
    */
    int getQuantity() const;

    /**
       Gets the cost per unit.

       @return the cost per unit
    */
    double getCost() const;

    /**
       Calculates the total inventory value for this tool.

       @return quantity multiplied by cost
    */
    double getInventoryValue() const;

    /**
       Determines whether this object represents an empty record.

       @return true if this is an empty record, false otherwise
    */
    bool isEmpty() const;

    /**
       Writes a formatted Tool record to an output stream.

       @param out the output stream
       @param tool the Tool object to write
       @return the output stream
    */
    friend std::ostream& operator<<(std::ostream& out, const Tool& tool);

    /**
       Reads a Tool record from an input stream.

       @param in the input stream
       @param tool the Tool object to read into
       @return the input stream
    */
    friend std::istream& operator>>(std::istream& in, Tool& tool);

  private:
    int m_toolNumber;
    char m_toolName[MAX_TOOL_NAME_LENGTH + 1];
    int m_quantity;
    double m_cost;
};

#endif
