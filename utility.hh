#include <iostream>
#include <map>
#include <string>

using namespace std;

enum comparator {
  LT,
  LE,
  GT,
  GE,
  EQ,
  NE,
  SUM,
  MUL,
  MIN,
  DIV,
  COLONS
};

map<string, comparator> options{
  {"<", LT},
  {"<=", LE},
  {">", GT},
  {">=", GE},
  {"==", EQ},
  {"!=", NE},
  {"+", SUM},
  {"*", MUL},
  {"-", MIN},
  {"/", DIV},
  {":", COLONS},
};

comparator resolveOption(string input) {
  return options[input];
}

