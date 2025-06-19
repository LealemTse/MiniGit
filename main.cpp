#include "merge.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    string command = argv[1];
    if(command == "merge"){
        if(argc != 3){
            cout<<"Usage: merge <branch name>";
            return 1;
        }
        string targetBranch = argv[2];
        string currentBranch = getCurrentBranch();
        cout<<"current branch: "<< currentBranch;
        string base = getLeastCommonAnscestor(currentBranch, targetBranch);
        string commitA = getBranchCommit(currentBranch);
        string  commitB = getBranchCommit(targetBranch);
        merge(base, commitA, commitB);
        cout<<"Merge completed. Merged file: .minigit/merged.txt";
    }

    if(command=="diff"){
        if(argc!=4){
            cout<<"Usage: diff <commit1> <commit2>";
            return 1;
        }
        string commit1 = argv[2];
        string commit2 = argv[3];
        diff(commit1, commit2);
    }
    

}
