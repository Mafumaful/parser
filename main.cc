#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr)
{
  // your code starts here
  // remove the space of the string
  std::string templine = line; // templine is a copy of line but it has no space
  int count = 0;
  for (int i = 0; line[i]; i++)
  {
    if (templine[i] != ' ')
      templine[count++] = templine[i];
  }
  templine = templine.substr(0, count);

  // devide the string, ";" is devider which devide the line into two parts
  formulaStr = templine.substr(0, templine.find(";"));                      // cut out the formularStr
  assignmentStr = templine.substr(templine.find(";") + 1, templine.size()); // cut out the assignmentStr
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main()
{
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line;          // store each input line
    std::string formulaStr;    // store the formula string
    std::string assignmentStr; // store the assignment string

    // your code starts here
    if (std::getline(std::cin, line)) // get input
    {
      // find space in variables
      try
      {
        if (line.find(";") == std::string::npos)
        {
          throw "Error: invalid input";
        }
        bool is_valid = true;
        bool before_is_var = false;
        bool before_is_space = false;
        for (int i = 0; line[i]; i++)
        {
          if (before_is_space && ((('0' <= line[i]) && (line[i] <= '9')) || (('a' <= line[i]) && (line[i] <= 'z')) || (('A' <= line[i]) && (line[i] <= 'Z'))))
          {
            before_is_space = false;
            is_valid = false;
            break;
          }
          else if ((('0' <= line[i]) && (line[i] <= '9')) || (('a' <= line[i]) && (line[i] <= 'z')) || (('A' <= line[i]) && (line[i] <= 'Z')))
          {
            before_is_var = true;
          }
          else if (line[i] == ' ' && before_is_var)
          {
            before_is_space = true;
          }
          else
          {
            before_is_space = false;
            before_is_var = false;
          }

          parseLine(line, formulaStr, assignmentStr); // parse the input into the formular string and assignment string
        }
        if (!is_valid || formulaStr.size() <= 0)
        {
          is_valid = true;
          // std::cout << "Error: invalid input" << std::endl;
          throw "Error: invalid input";
        }

        AssignmentParser *assignment_parser = new AssignmentParser(assignmentStr);  // parse the assignmentStr
        std::map<std::string, bool> asm_map = assignment_parser->parseAssignment(); // Store the result of map
        FormulaParser *formular_parser = new FormulaParser(formulaStr);             // parse the formularSt
        formular_parser->input_map(asm_map);                                        // input the assignment map

        auto *treeroot = formular_parser->getTreeRoot(); // get the node to recursive evaluate

        if (treeroot->evaluate(asm_map)) // evaluate the result via asm_map(assimant map), the result is true or false
          std::cout << "1" << std::endl;
        else
          std::cout << "0" << std::endl;
        delete formular_parser;
        delete assignment_parser;
        continue;
      }
      catch (const char *e)
      {
        std::cout << e << std::endl;
      }
    }
    else
      break;
  }
}
