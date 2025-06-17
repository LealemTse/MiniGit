#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>
#include <unordered_map>
using namespace std;
class Repository {
public:
  string worktree;
  string gitdir;
  unordered_map<string, string> config;

  Repository(const string& path, bool force=false);
  void init();
  string repoFile(const string& relativePath);
  void loadConfig(const string& configPath);
};
#endif
