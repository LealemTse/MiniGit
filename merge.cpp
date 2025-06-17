// does not handle conflict yet

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string branch2;
string currnetBranch;


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

void mergeFiles(const string &base, const string &currentBranch, const string &branch2)
{
    string basePath = ".minigit/objects/" + base;
    string currentBranchPath = ".minigit/objects/" + currentBranch;
    string branch2Path = ".minigit/objects/" + branch2;

    vector<string> baseLines = readFile(basePath);
    vector<string> currentBranchLines = readFile(currentBranchPath);
    vector<string> branch2Lines = readFile(branch2Path);

    size_t maxSize = max(base.size(), max(currentBranch.size(), branch2.size()));

    vector<string> result;

    for (size_t i = 0; i < maxSize; ++i)
    {
        if (base[i] == currentBranch[i] && base[i] == branch2[i])
        {
            result.push_back(currentBranch[i]);
        }

        else if (currentBranch[i] == branch2[i])
        {
            result.push_back(currentBranch[i]);
        }

        else if (base[i] == currentBranch[i])
        {
            result.push_back(branch2[i]);
        }

        else if (base[i] == branch2[i])
        {
            result.push_back(currentBranch[i]);
        }
    }


    string mergedFile = ".minigit/merged.txt";
    ofstream out(mergedFile);
    for (size_t i = 0; i<result.size(); i++)
    {
        out << result[i] << endl;
    }
}

int main(){
    Repository repo(".", false);
    currentBranch = repo.getCurrentBranch();
    cout << "Current branch: " << currentBranch << endl;
}
