#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct Commit {
  string hash;
  string message;
  string madeby;
  string timestamp;
  vector<string> files;
};

class Repository {
private:
  string gitdir = ".minigit";
  string objectDir= ".minigit/objects";
  unordered_map<string, string> blob;
  vector<Commit> commits;

  string getTime();
  string customHash(string& content);
  string creatBlob(string& content);

public:
  void init();
  void addFile(string& filepath);
  void commit(string& message, string madeby);
};
#endif
