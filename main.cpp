#include<iostream>
#include"Repository.h"
using namespace std;

int main(int argc, char *argv[]) {
  if(argc<2) {
    cerr<<"Usage: minigit <command>"<<endl;
    return  1;
  }
  string command = argv[1];
  try {
    if(command=="init") {
      Repository repo(".", true);
      repo.init();
    }else {
      Repository repo(".");
      cout<<"MiniGit Repository Loaded Successfully"<<endl;
    }
  }catch(const exception& e) {
    cerr<<"ERROR: "<<e.what()<<endl;
    return 1;
  }
  return 0;
}

