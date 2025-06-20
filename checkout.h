#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <string>
using namespace std;

class Checkout {
  string gitDir;

public:
  Checkout(const string& repoPath = ".minigit");
  void switchBranch(const string& branchName);
};



#endif
