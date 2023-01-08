#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>

#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser
{
  int lparent_c = 0;
  Tokenizer *tknzr;
  std::map<std::string, bool> m_map;
  TreeNode *parseFormula();  // parse non-terminal Formula in the grammar
  TreeNode *parseConjTerm(); // parse non-terminal ConjTerm in the grammar
  TreeNode *parseTerm();     // parse non-terminal Term in the grammar

public:
  void input_map(std::map<std::string, bool> map);
  FormulaParser(std::string ln);
  TreeNode *getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
  ~FormulaParser();
};

// Parser for the Assignment
class AssignmentParser
{

  Tokenizer *tknzr;

public:
  AssignmentParser(std::string ln);
  std::map<std::string, bool> parseAssignment();
  ~AssignmentParser();
};

#endif
