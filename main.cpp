#include "merge.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 3){
        cout<<"Usage: merge <branch name>";
        return 1;
    }

    string command = argv[1];
    string targetBranch = argv[2];

    if(command == "merge"){
        string currentBranch = getCurrentBranch();
        cout<<"current branch: "<< currentBranch;
        string base = getLeastCommonAnscestor(currentBranch, targetBranch);
        string commitA = getBranchCommit(currentBranch);
        string  commitB = getBranchCommit(targetBranch);
        merge(base, commitA, commitB);
        cout<<"Merge completed. Merged file: .minigit/merged.txt";
    }

}