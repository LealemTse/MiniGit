#include "checkout.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs=std::filesystem;

Checkout::Checkout(const string& repoPath) : gitDir(repoPath){}
void Checkout::switchBranch(const string &branchName) {
  string branchRef = "refs/heads/"+branchName;
  string branchPath = gitDir + "/" + branchRef;

  if(!fs::exists(branchPath)) {
    cerr<<"ERROR: Branch "<<branchName<<" Does not Exist "<<endl;
    return;
  }
  ofstream headFile(gitDir+"/HEAD");
  if(!headFile) {
    cerr<<"ERROR: Could not Open HEAD from Writing"<<endl;
    return;
  }
  headFile<<"ref: "<<branchRef << "\n";
  headFile.close();

  cout<<"Switched to Branch "<< branchName << "\n";
}


