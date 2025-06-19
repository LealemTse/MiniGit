#include "Repository.h"
#include <iostream>
#include <filesystem>

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
        cout << "Enter author name: ";
        getline(cin >> ws, madeby);
        repo.commit(message, madeby);
      } else {
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
=======
#include <filesystem>
#include<iostream>
#include"Repository.h"

using namespace std;
namespace fs= std::filesystem;


int main(int argc, char *argv[]) {
  if(argc<2) {
    cerr<<"Usage: minigit <command> [args] "<<endl;
    return  1;
  }
  string command = argv[1];
  Repository minigit;

  try {
    if(command=="init") {
      minigit.init();
    } else if (command=="add"){
      if(argc<3) {
        cerr<<"Usage: minigit add <filename>"<<endl;
        return 1;
      }
      string filepath =argv[2];
      minigit.addFile(filepath);
    }else if(command == "commit") {
      if(argc<4 || string (argv[2])!="-m") {
        cerr<<"Usage: minigit commit -m <message>" << endl;
        return 1;
      }
      string message = argv[3];
      string madeby;
      cout<<"Enter Who made this Commit";
      getline(cin>>ws, madeby);
      minigit.commit(message, madeby);
    }else {
      if(filesystem::exists(".minigit")){
         cout<<"MiniGit Repository Loaded Successfully"<<endl;
      }else {
        cerr<<"ERROE: No MiniGit Repository Found, Run '.minigit init' first"<<endl;
      }
    }
  }catch(const exception& e) {
    cerr<<"ERROR: "<<e.what()<<endl;
    return 1;
  }
  return 0;
}

