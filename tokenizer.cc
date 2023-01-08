#include "tokenizer.h"

bool Tokenizer::member_is_valid(std::vector<std::string> unwanted)
{
  u_long temp = this->char_cursor; // restore the char_cursor
  this->char_cursor = 0;
  while (this->getToken().type != "EOF")
  {
    for (u_long i = 0; i < unwanted.size(); i++)
    {
      if (this->getToken().type == unwanted[i])
      {
        return false;
      }
    }
    this->advanceToken();
  }
  this->char_cursor = temp; // get back
  return true;
}

Tokenizer::Tokenizer(std::string ln)
{
  // complete the constructor
  this->line = ln;
}

bool Tokenizer::advanceToken()
{
  // your code starts here
  // advance to the next token; return false if no more token exist
  this->char_cursor += current_token_length;
  this->getToken(); // update the current_token_length and the token content
  if (char_cursor <= line.size())
    return true;
  return false;
}

bool Tokenizer::hasToken() const
{
  // your code starts here
  // check whether there is a current token
  if (char_cursor <= line.size())
    return true;
  return false;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken()
{
  Token resultToken;
  // your code starts there
  // returns the token being processed

  resultToken.type = "ERR"; // error when none of theses applied
  resultToken.content.clear();

  // judge the current tocken type, and input the content of the tocken
  if (line[this->char_cursor] == '*')
  {
    resultToken.type = "AND";
    resultToken.content += line[this->char_cursor];
    this->current_token_length = 1;
  }

  if (line[this->char_cursor] == '+')
  {
    resultToken.type = "OR";
    resultToken.content += line[this->char_cursor];
    this->current_token_length = 1;
  }

  if (line[this->char_cursor] == '-')
  {
    resultToken.type = "NOT";
    resultToken.content += line[this->char_cursor];
    this->current_token_length = 1;
  }

  if (line[this->char_cursor] == ',')
  {
    resultToken.type = "COMMA";
    resultToken.content += line[this->char_cursor];
    this->current_token_length = 1;
  }

  if (line[this->char_cursor] == '(')
  {
    resultToken.type = "LEFTPARENT";
    resultToken.content += line[this->char_cursor];
    this->current_token_length = 1;
  }

  if (line[this->char_cursor] == ')')
  {
    resultToken.type = "RIGHTPARENT";
    resultToken.content += line[this->char_cursor];
    this->current_token_length = 1;
  }

  if (line[this->char_cursor] == ':')
  {
    resultToken.type = "ASSIGNMENT";
    resultToken.content += line[this->char_cursor];
    this->current_token_length = 1;
  }

  if (line[this->char_cursor] == '1' || line[this->char_cursor] == '0')
  {
    resultToken.type = "CONSTANT";
    resultToken.content += line[this->char_cursor];
    this->current_token_length = 1;
  }

  if (char_cursor == line.size()) // if the tokenizer is ended it should contain the type "EOF"
  {
    resultToken.type = "EOF";
    resultToken.content = "";
    this->current_token_length = 1;
  }

  if (('a' <= line[this->char_cursor] && line[this->char_cursor] <= 'z') || ('A' <= line[this->char_cursor] && line[this->char_cursor] <= 'Z'))
  {
    int count = 0;
    resultToken.type = "VAR";
    while (('a' <= line[this->char_cursor] && line[this->char_cursor] <= 'z') || ('A' <= line[this->char_cursor] && line[this->char_cursor] <= 'Z') || ('0' <= line[this->char_cursor] && line[this->char_cursor] <= '9'))
    {
      count++;
      resultToken.content += line[this->char_cursor]; // add the char that satisfied the requirement
      this->char_cursor++;                            // move to the nest char
      if (count > 10)                                 // avoid deadlock and make sure the input is valid
      {
        resultToken.type = "ERR"; // total length cannot be longer than 10
        break;
      }
    }
    current_token_length = count;
    this->char_cursor -= current_token_length;
  }

  return resultToken;
}
