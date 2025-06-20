#ifndef BRANCH_H
#define BRANCH_H

#include<string>
using namespace  std;
class Branch {
  string gitDir;
public:
  Branch(const string & repoPath = ".minigit");

  void creatBranch(const string& name);
  void listbranch();


};


#endif
