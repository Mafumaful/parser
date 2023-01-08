#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln) : tknzr{new Tokenizer{ln}} {}

void FormulaParser::input_map(std::map<std::string, bool> map)
{
  this->m_map = map;
}

TreeNode *FormulaParser::parseConjTerm()
{
  // your code starts here
  // parse non-terminal ConjTerm in the grammar
  auto left = parseTerm();
  if (tknzr->getToken().type == "VAR" || tknzr->getToken().type == "CONSTANT" || tknzr->getToken().type == "NOT")
  {
    throw "Error: invalid input";
  }

  while (tknzr->getToken().type == "AND") // parse term detecting "AND" world
  {
    auto *Operator = new OperatorNode(tknzr->getToken().content);
    tknzr->advanceToken();
    Operator->updateChildren(left, parseConjTerm());
    return Operator;
  }
  return left;
}

TreeNode *FormulaParser::parseTerm()
{
  // your code starts here
  // parse non-terminal Term in the grammar
  Token token = tknzr->getToken();

  if (!tknzr->hasToken() || token.type == "ERR")
  {
    throw "Error: invalid input";
  }

  if (token.type == "LEFTPARENT")
  {
    this->lparent_c++;
    tknzr->advanceToken();
    auto *Varia = parseFormula();
    if (tknzr->getToken().type != "RIGHTPARENT")
    {
      throw "Error: invalid input";
    }
    this->lparent_c--;
    tknzr->advanceToken();
    return Varia;
  }
  else if (token.type == "VAR")
  {
    auto *Varia = new VariableNode(token.content);

    // if it's not find in the map
    auto it = this->m_map.find(token.content);
    if (it == this->m_map.end())
    {
      throw "Error: incomplete assignment";
    }

    tknzr->advanceToken();
    return Varia;
  }
  else if (token.type == "CONSTANT")
  {
    auto *Constant = new ConstantNode(token.content);
    tknzr->advanceToken();
    return Constant;
  }
  else if (token.type == "NOT")
  {
    auto *Operator = new OperatorNode(token.content);
    tknzr->advanceToken();
    Operator->updateLeftChild(parseTerm());
    return Operator;
  }
  else
  {
    throw "Error: invalid input";
  }
}

TreeNode *FormulaParser::parseFormula()
{
  // your code starts here
  // parse non-terminal Formula in the grammar

  auto left = parseConjTerm();
  if (tknzr->getToken().type == "VAR" || tknzr->getToken().type == "CONSTANT" || tknzr->getToken().type == "NOT")
  {
    throw "Error: invalid input";
  }
  while (tknzr->getToken().type == "OR")
  {
    auto *Operator = new OperatorNode(tknzr->getToken().content);
    tknzr->advanceToken();
    Operator->updateChildren(left, parseFormula());
    return Operator;
  }

  if (this->lparent_c < 1 && tknzr->getToken().type == "RIGHTPARENT")
  {
    throw "Error: invalid input";
  }

  return left;
}

TreeNode *FormulaParser::getTreeRoot()
{
  // your code starts here
  // parse the Boolean formula and return the root node of the formula syntax tree
  std::vector<std::string> unwanted_str = {"ERR", "ASSIGNMENT", "COMMA"};
  if (!tknzr->member_is_valid(unwanted_str)) // check if every thing is right
  {
    throw "Error: invalid input";
  }
  return this->parseFormula(); // return the root of the Formular

  // return nullptr;
}

FormulaParser::~FormulaParser()
{
  // your code starts here
  delete tknzr;
}

AssignmentParser::AssignmentParser(std::string ln) : tknzr{new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment()
{
  std::map<std::string, bool> results;
  // your code starts here
  // this function is to parse assiment and turn it into map that we can find correspond variable value
  while (tknzr->hasToken())
  {
    std::string var;
    std::string constant;

    if (tknzr->getToken().type == "EOF") // if there is no token or if it's end
      return results;

    if (tknzr->getToken().type == "VAR")
    {
      var = tknzr->getToken().content;
      tknzr->advanceToken();
    }
    else // the first token should be the variable
    {
      throw "Error: invalid input";
    }

    // when received the token name "ASSIGNMENT" that means the next type is the constant
    if (tknzr->getToken().type == "ASSIGNMENT")
    {
      tknzr->advanceToken();
    }
    else // the assignment should come after the token "VAR"
    {
      throw "Error: invalid input";
    }

    if (tknzr->getToken().type == "CONSTANT") // if the token has the constant value
    {
      bool b_constant = true;
      constant = tknzr->getToken().content;
      if (constant == "0")
        b_constant = false;

      auto it = results.find(var);
      if (it != results.end()) // if find
      {
        if (it->second != b_constant) // if not the same
        {
          throw "Error: contradicting assignment";
        }
      }

      results.insert(std::pair<std::string, bool>(var, b_constant));
      tknzr->advanceToken();
    }
    else
    {
      throw "Error: invalid input";
    }

    // COMMA means there is a next equation
    if (tknzr->getToken().type == "COMMA")
    {
      tknzr->advanceToken();
    }
    else if (tknzr->getToken().type == "EOF")
    {
      return results;
    }
    else // there shouldn't be other type except "COMMA" or "EOF"
    {
      throw "Error: invalid input";
    }
  }
  return results;
}

AssignmentParser::~AssignmentParser()
{
  // your code starts here
  delete tknzr;
}
