#ifndef COUTREDIRECT_INCLUDE_GUARD
#define COUTREDIRECT_INCLUDE_GUARD

#include <stdio.h>
#include <iostream>
#include <streambuf>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

// Modified from https://stackoverflow.com/a/44586088/126039

class CoutRedirect {
private:
  stringstream buffer;
  streambuf* old;
public:
  CoutRedirect() {
    // redirect cout to buffer stream
    // and keep the old buffer
    this->old = cout.rdbuf(buffer.rdbuf());
  }

  ~CoutRedirect(){}

  string getString() {
    return buffer.str(); // get string
  }

  
  void restoreCout() {
    cout.rdbuf(old); // revert redirect
  }

  
};

#endif
