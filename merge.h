#ifndef MERGE_H
#define MERGE_H

#include <string>
#include <vector>
using namespace std;

string getCurrentBranch();
string getBranchCommit(const string& branchName);
string getParentCommit(const string& commitId);
string getLeastCommonAnscestor(const string& branch1, const string& branch2);
vector<string> readFile(const string &path);
void merge(const string &base, const string &currentBranch, const string &targetBranch);
void diff(const string &commit1, const string &commit2);

#endif
