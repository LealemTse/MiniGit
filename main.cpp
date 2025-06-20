#include "Repository.h"
#include "checkout.h"
#include "log.h"
#include "merge.h"
#include <iostream>
#include <filesystem>
#include "branch.h"
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: minigit <command> [args]" << endl;
    return 1;
  }

  string command = argv[1];

  try {
    if (command == "init") {
      Repository repo(".minigit", true);
      repo.init();
    } else {
      Repository repo;
      if (command == "add") {
        if (argc < 3) {
          cerr << "Usage: minigit add <file>" << endl;
          return 1;
        }
        repo.addFile(argv[2]);
      } else if (command == "commit") {
        if (argc < 4 || string(argv[2]) != "-m") {
          cerr << "Usage: minigit commit -m <message>" << endl;
          return 1;
        }
        string message = argv[3];
        string madeby;
        cout << "Enter Made By name: ";
        getline(cin >> ws, madeby);
        repo.commit(message, madeby);
      } else if(command == "log") {
      log::showLog();
    }else if(command =="branch") {
      Branch branch;
      if(argc ==2) {
        branch.listbranch();
      }else if(argc==3) {
        branch.creatBranch(argv[2]);
      }else {
        cerr<<"Usage: " <<endl;
        cerr<<" minigit branch";
        cerr<<" minigit branch <name>";
      }
    }else if(command=="checkout") {
      if(argc<3) {
        cerr<<"Usage: MiniGit checkout <branch> \n";
        return 1;
      }
      Checkout co;
      co.switchBranch(argv[2]);
    }else if(command=="merge") {
      if (argc !=3) {
          cerr <<"Usage: MiniGit merge <branch>"<<endl;
        return 1;
      }
      string targetBranch =argv[2];
      string currentBranch = getCurrentBranch();
      cout<<"Current Branch: " <<currentBranch <<endl;

      string base = getLeastCommonAnscestor(currentBranch, targetBranch);
      string commitA= getBranchCommit(currentBranch);
      string commitB= getBranchCommit(targetBranch);

      merge(base,commitA,commitB);
      cout<<"Usage: MiniGti diff <commit1><commit2>"<<endl;
    }
      else if(command == "diff") {
        if(argc !=4) {
          cerr<<"Usage: MiniGit diff <commit1> <commit2>" <<endl;
          return 1;
        }
        string commit1 =argv[2];
        string commit2 =argv[3];
        diff(commit1,commit2);
      }
      else {
        if (fs::exists(".minigit")) {
          cout << "MiniGit Repository Loaded Successfully" << endl;
        } else {
          cerr << "ERROR: No MiniGit repository found. Run 'minigit init' first." << endl;
        }
      }
    }
  } catch (const exception& e) {
    cerr << "ERROR: " << e.what() << endl;
    return 1;
  }

  return 0;
}
