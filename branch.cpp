#include "branch.h"
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs=std:: filesystem;
using namespace std;

Branch::Branch(const string &repoPath) : gitDir(repoPath){}

void Branch::creatBranch(const string &name) {
  string masterPath = gitDir + "/HEAD";
  ifstream headFile(masterPath);
  if(!headFile) {
    cerr<<"ERROR: MASTER not Found, IS THIS MiniGit repo?" <<endl;
    return;
  }
  string refLine;
  getline(headFile, refLine);
  headFile.close();
  if(refLine.rfind("ref:",0)!=0) {
    cerr<<"ERROR: MASTER format is incorrect." <<endl;
    return;
  }

  string currentBranchRef = gitDir + "/" + refLine.substr(5);
  ifstream branchRef(currentBranchRef);
  if(!branchRef) {
    cerr<<"ERROR: Current Branch Invalid." <<endl;
    return;
  }

  string lastCommitHash;
  getline(branchRef, lastCommitHash);
  branchRef.close();
  if(lastCommitHash.empty()) {
    cerr<<"ERROR:  Current Branch Has No Commits Yet. Cannot Branch From Nothing" <<endl;
    return;
  }

  string newBranchPath = gitDir+"/refs/heads/"+name;
  if(fs::exists(newBranchPath)){
    cerr<<"Branch Already Exists." <<endl;
    return;
  }

  ofstream newBranchFile(newBranchPath);
  if(!newBranchFile) {
    cerr<<"ERROR: Could not Creat Branch File" <<endl;
    return;
  }
  ofstream out(newBranchPath);
  if(!out) {
    cerr <<"ERROR: Could not create branch file." <<endl;
    return;
  }
   out << lastCommitHash << endl;
   out.close();
   cout << "Created branch: " << name << endl;

}
void Branch::listbranch() {
  string headerDir = gitDir + "/refs/heads";
  if(!fs::exists(headerDir)) {
    cerr<<"No Brancch Found \n";
    return;
  }

  string currentBranch;
  ifstream headFile(gitDir + "/HEAD");
  if(headFile) {
    string ref;
    getline(headFile, ref);
    if(ref.rfind("ref: ", 0)==0) {
      currentBranch = ref.substr(5);
    }
  }
  cout<<"Branches: \n";
  for(const auto& entry : fs::directory_iterator(headerDir)) {
    string branch = entry.path().filename().string();
    string path = "refs/heads/" + branch;
    if(path == currentBranch) {
      cout<<"* "<<branch<<endl;
    }
    else
      cout<<" "<< branch <<endl;
  }
}



