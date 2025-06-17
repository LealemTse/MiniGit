#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;



//gets the  current branch
string getCurrentBranch(){
    string path = ".minigit/HEAD";
    ifstream headFile(path);
    if(!headFile){
        throw runtime_error("Could not open HEAD file.");
    }

    string line;
    getline(headFile, line);

    if (line.substr(0, 5) == "ref: refs/heads/") {
        return line.substr(16);
    }else{
        return "";
    }
}

//gets commitid in a branch

string getBranchCommit(const string& branchName) {
    string path = ".minigit/refs/heads/" + branchName;
    ifstream branch(path);
    if (!branch) {
        throw runtime_error("branch not found");
    }
    string commit;
    getline(branch, commit);
    return commit;
}


//gets parentcommit

string getParentCommit(const string& commitId) {
    ifstream file(".minigit/objects/" + commitId);
    string line;
    while (getline(file, line)) {
        if (line.substr(0, 7) == "parent ") {
            return line.substr(7);
        }
    }
    return "";
}

// gets least common anscestr of  current branch and branch2

string getLeastCommonAnscestor(const string& branch1, const string& branch2){
    set<string> ancestors; //to store all anscestrs of branch1
    string curr = branch1;
    
    while (!curr.empty()) {
        ancestors.insert(curr); 
        curr = getParentCommit(curr); 
    }
    

    curr = branch2;
//searches if branch2 has a common anscestor with branch1 and if there is, returns the first one
    
    while (!curr.empty()) {
        if (ancestors.count(curr)){
            return curr;
        }else{
            curr = getParentCommit(curr);
        }
    }
}


vector<string> readFile(const string &path)
{
    ifstream file(path);
    vector<string> lines;
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

void merge(const string &base, const string &currentBranch, const string &targetBranch)
{
    string basePath = ".minigit/objects/" + base;
    string currentBranchPath = ".minigit/objects/" + currentBranch;
    string targetBranchPath = ".minigit/objects/" + targetBranch;

    vector<string> baseLines = readFile(basePath);
    vector<string> currentBranchLines = readFile(currentBranchPath);
    vector<string> targetBranchLines = readFile(targetBranchPath);

    size_t maxSize = max(baseLines.size(), max(currentBranchLines.size(), targetBranchLines.size())); // gets maximmum number of lines from the three

    vector<string> result;

    for (size_t i = 0; i < maxSize; i++){
        string baseLine = "", currentBranchLine = "", targetBranchLine = "";
        
        //check if the lines exist
        
        if(baseLines.size()>i) baseLine = baseLines[i];
        if(currentBranchLines.size()>i) currentBranchLine = currentBranchLines[i];
        if(targetBranchLines.size()>i) targetBranchLine = targetBranchLines[i];

        //detect conflict
        if(baseLine==currentBranchLine && baseLine==targetBranchLine){
            result.push_back(baseLine);
        }else if (currentBranchLine == targetBranchLine){
            result.push_back(currentBranchLine);
        }else if (baseLine == currentBranchLine){
            result.push_back(targetBranchLine);
        }else if (baseLine == targetBranchLine){
            result.push_back(currentBranchLine);
        }else{
            result.push_back("<<<<<<current branch");
            result.push_back(currentBranchLine);
            result.push_back("========");
            result.push_back(targetBranchLine);
            result.push_back("<<<<<<target branch");
        }


    }
    //create a file containing the merged lines
    string mergedFile = ".minigit/merged.txt";
    ofstream out(mergedFile);
    for (size_t i = 0; i<result.size(); i++){
        out << result[i] << endl;
    }
}


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
