#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <vector>

struct Token
{
  std::string content;
  std::string type;
};

// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
  // your code starts here
private:
  std::string line;       // input line
  u_long char_cursor = 0; // mark the current position
  u_long current_token_length = 0;

public:
  Tokenizer(std::string ln);
  bool member_is_valid(std::vector<std::string>); // ensure current member is valid
  bool advanceToken();                            // advance to the next token; return false if no more token exist
  bool hasToken() const;                          // check whether there is a current token
  Token getToken();                               // returns the token being processed
};

#endif
